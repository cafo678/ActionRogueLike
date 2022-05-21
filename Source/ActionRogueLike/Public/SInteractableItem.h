// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SGameplayInterface.h"
#include "GameFramework/Actor.h"
#include "SInteractableItem.generated.h"

class UStaticMeshComponent;

UCLASS()
class ACTIONROGUELIKE_API ASInteractableItem : public AActor, public ISGameplayInterface
{
	GENERATED_BODY()
	
public:	
	ASInteractableItem();

protected:
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* MeshComponent = nullptr;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Cooldown)
	float CooldownTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Interaction)
	bool bIsInteractable = true;

	UFUNCTION()
	void OnCooldownElapsed();
	
public:
	virtual void Interact_Implementation(bool bCanInteract, APawn* InstigatorPawn) override;

private:
	FTimerHandle CooldownTimerHandle;

	virtual bool GetIsInteractable() override;
};
