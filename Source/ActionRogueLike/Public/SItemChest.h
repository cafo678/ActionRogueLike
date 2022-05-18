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

	UPROPERTY(EditAnywhere)
	float TargetPitch;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* BaseMesh = nullptr;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* LidMesh = nullptr;

public:	
	virtual void Tick(float DeltaTime) override;

	void Interact_Implementation(APawn* InstigatorPawn);
};
