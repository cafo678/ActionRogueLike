// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SGameplayInterface.h"
#include "GameFramework/Actor.h"
#include "SItemChest.generated.h"

class UStaticMeshComponent;

UCLASS()
class ACTIONROGUELIKE_API ASItemChest : public AActor, public ISGameplayInterface
{
	GENERATED_BODY()
	
public:	
	ASItemChest();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float TargetPitch;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Interaction)
	bool bIsInteractable = true;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* BaseMesh = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* LidMesh = nullptr;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void Interact_Implementation(bool bCanInteract, APawn* InstigatorPawn) override;
};
