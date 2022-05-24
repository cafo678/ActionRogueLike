// Fill out your copyright notice in the Description page of Project Settings.

#include "SAttributeComponent.h"

#include "SGameMode.h"
#include "Blueprint/UserWidget.h"
#include "UI/SHealthChangeWidget.h"

USAttributeComponent::USAttributeComponent()
{
}

bool USAttributeComponent::IsAlive() const
{
	return Health > 0.f;
}

bool USAttributeComponent::ApplyHealthChange(AActor* InstigatorActor, float Delta)
{
	if (!GetOwner()->CanBeDamaged() && Delta < 0.f)
	{
		return false;
	}
	
	float PreviousHealth = Health;
	
	Health = FMath::Clamp(Health + Delta, 0.f, MaxHealth);

	float ActualDelta = Health - PreviousHealth;

	OnHealthChanged.Broadcast(InstigatorActor, this, Health, Delta);

	USHealthChangeWidget* HealthChangeWidget = CreateWidget<USHealthChangeWidget>(GetWorld(), HealthChangeWidgetClass);
	HealthChangeWidget->SetActorToAttach(GetOwner());
	HealthChangeWidget->SetHealthChange(ActualDelta);
	HealthChangeWidget->AddToViewport();

	if (ActualDelta < 0.f && Health == 0.f)
	{
		ASGameMode* GameMode = GetWorld()->GetAuthGameMode<ASGameMode>();
		if (GameMode)
		{
			GameMode->OnActorKilled(GetOwner(), InstigatorActor);
		}
	}

	return ActualDelta != 0.f;
}

USAttributeComponent* USAttributeComponent::GetAttributeComponent(AActor* Actor)
{
	if(Actor)
	{
		return Cast<USAttributeComponent>(Actor->GetComponentByClass(USAttributeComponent::StaticClass()));
	}

	return nullptr;
}

bool USAttributeComponent::IsActorAlive(AActor* Actor)
{
	USAttributeComponent* AttributeComponent = GetAttributeComponent(Actor);
	
	if (AttributeComponent)
	{
		return AttributeComponent->IsAlive();
	}
	
	return false;
}

bool USAttributeComponent::Kill(AActor* InstigatorActor)
{
	return ApplyHealthChange(InstigatorActor, -GetMaxHealth());
}

