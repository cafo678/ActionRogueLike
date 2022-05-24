// Fill out your copyright notice in the Description page of Project Settings.


#include "SInteractionComponent.h"

#include "SGameplayInterface.h"

USInteractionComponent::USInteractionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void USInteractionComponent::BeginPlay()
{
	Super::BeginPlay();
}

void USInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void USInteractionComponent::PrimaryInteract()
{
	FHitResult Hit;

	FCollisionObjectQueryParams CollisionObjectQueryParams;
	CollisionObjectQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);

	FVector OwnerEyeLocation;
	FRotator OwnerEyeRotation;
	
	AActor* Owner = GetOwner();
	Owner->GetActorEyesViewPoint(OwnerEyeLocation, OwnerEyeRotation);

	FVector LineTraceEndLocation = OwnerEyeLocation + (OwnerEyeRotation.Vector() * 1000);
	
	bool bHasLineTraceHittedSomething = GetWorld()->LineTraceSingleByObjectType(Hit, OwnerEyeLocation, LineTraceEndLocation, CollisionObjectQueryParams);

	AActor* HitActor = Hit.GetActor();
	if (HitActor)
	{
		if (HitActor->Implements<USGameplayInterface>())
		{
			ISGameplayInterface::Execute_Interact(HitActor, ISGameplayInterface::Execute_GetIsInteractable(HitActor), Cast<APawn>(Owner));
		}
	}

	FColor DebugLineColor = bHasLineTraceHittedSomething ? FColor::Green : FColor::Red;
	DrawDebugLine(GetWorld(), OwnerEyeLocation, LineTraceEndLocation, DebugLineColor, false, 2.f, 0, 2.f);
}

