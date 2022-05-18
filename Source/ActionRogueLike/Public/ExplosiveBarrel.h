// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ExplosiveBarrel.generated.h"

class UStaticMeshComponent;
class URadialForceComponent;

UCLASS()
class ACTIONROGUELIKE_API AExplosiveBarrel : public AActor
{
	GENERATED_BODY()
	
public:	
	AExplosiveBarrel();

protected:
	virtual void BeginPlay() override;

	virtual void PostInitializeComponents() override;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* StaticMeshComponent = nullptr;

	UPROPERTY(VisibleAnywhere)
	URadialForceComponent* RadialForceComponent = nullptr;

	UFUNCTION()
	void OnHitCallback(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

public:	
	virtual void Tick(float DeltaTime) override;
};
