// Fill out your copyright notice in the Description page of Project Settings.


#include "SAction.h"

#include "SActionComponent.h"

void USAction::StartAction_Implementation(AActor* Instigator)
{
	UE_LOG(LogTemp, Warning, TEXT("Running %s"), *ActionName.ToString());
	
	USActionComponent* ActionComponent = GetOwningComponent();
	ActionComponent->ActiveGameplayTags.AppendTags(GrantsTags);

	bIsRunning = true;
}

void USAction::StopAction_Implementation(AActor* Instigator)
{
	UE_LOG(LogTemp, Warning, TEXT("Stopping %s"), *ActionName.ToString());

	ensureAlways(bIsRunning);
	
	USActionComponent* ActionComponent = GetOwningComponent();
	ActionComponent->ActiveGameplayTags.RemoveTags(GrantsTags);

	bIsRunning = false;
}

bool USAction::CanStart_Implementation(AActor* Instigator)
{
	USActionComponent* ActionComponent = GetOwningComponent();

	if (ActionComponent->ActiveGameplayTags.HasAny(BlockedTags) || IsRunning())
	{
		return false;
	}

	return true;
}

USActionComponent* USAction::GetOwningComponent() const
{
	return Cast<USActionComponent>(GetOuter());
}

UWorld* USAction::GetWorld() const
{
	UActorComponent* ActorComponent = Cast<UActorComponent>(GetOuter());
	if (ActorComponent)
	{
		return ActorComponent->GetWorld();
	}

	return nullptr;
}
