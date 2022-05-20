// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SDummyTarget.generated.h"

class USAttributeComponent;

UCLASS()
class ACTIONROGUELIKE_API ASDummyTarget : public AActor
{
	GENERATED_BODY()
	
public:	
	ASDummyTarget();

protected:
	virtual void PostInitializeComponents() override;
	
	UPROPERTY(VisibleAnywhere)
	USAttributeComponent* AttributeComponent = nullptr;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* MeshComponent = nullptr;

	UFUNCTION()
	void OnHealthChanged(AActor* ActorInstigator, USAttributeComponent* OwningComponent, float NewHealth, float Delta);
};
