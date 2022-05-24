// Fill out your copyright notice in the Description page of Project Settings.


#include "SGameplayFunctionLibrary.h"

#include "SAttributeComponent.h"

bool USGameplayFunctionLibrary::ChangeHealth(AActor* DamageCauser, AActor* TargetActor, float DeltaDamage)
{
	USAttributeComponent* AttributeComponent = USAttributeComponent::GetAttributeComponent(TargetActor);
	if (AttributeComponent)
	{
		return AttributeComponent->ApplyHealthChange(DamageCauser, DeltaDamage);
	}
	
	return false;
}

bool USGameplayFunctionLibrary::ApplyDirectionalDamage(AActor* DamageCauser, AActor* TargetActor, float DeltaDamage,
                                                       const FHitResult& HitResult)
{
	if (ChangeHealth(DamageCauser, TargetActor, DeltaDamage))
	{
		UPrimitiveComponent* HittedPrimitiveComponent = HitResult.GetComponent();
		if (HittedPrimitiveComponent && HittedPrimitiveComponent->IsSimulatingPhysics(HitResult.BoneName))
		{
			HittedPrimitiveComponent->AddImpulseAtLocation(-HitResult.ImpactNormal * 300000.f, HitResult.ImpactPoint, HitResult.BoneName);
		}

		return true;
	}

	return false;
}
