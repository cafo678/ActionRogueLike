// Fill out your copyright notice in the Description page of Project Settings.


#include "SAttributeComponent.h"

USAttributeComponent::USAttributeComponent()
{
}

bool USAttributeComponent::IsAlive() const
{
	return Health > 0.f;
}

bool USAttributeComponent::ApplyHealthChange(float Delta)
{
	Health = FMath::Clamp(Health += Delta, 0.f, MaxHealth);

	OnHealthChanged.Broadcast(GetOwner(), this, Health, Delta);

	return true;
}

