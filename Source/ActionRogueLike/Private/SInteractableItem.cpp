// Fill out your copyright notice in the Description page of Project Settings.


#include "SInteractableItem.h"

ASInteractableItem::ASInteractableItem()
{
	PrimaryActorTick.bCanEverTick = true;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("MeshComponent");
	RootComponent = MeshComponent;
}

void ASInteractableItem::OnCooldownElapsed()
{
	bIsInteractable = true;
	MeshComponent->SetVisibility(true);
}

void ASInteractableItem::Interact_Implementation(bool bCanInteract, APawn* InstigatorPawn)
{
	if (bCanInteract)
	{
		bIsInteractable = false;
		MeshComponent->SetVisibility(false);
	
		GetWorldTimerManager().ClearTimer(CooldownTimerHandle);
		GetWorldTimerManager().SetTimer(CooldownTimerHandle, this, &ASInteractableItem::OnCooldownElapsed, CooldownTime, false);
	}
}

