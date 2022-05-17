// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SMagicProjectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;
class UParticleSystemComponent;

UCLASS()
class ACTIONROGUELIKE_API ASMagicProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	ASMagicProjectile();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	USphereComponent* SphereComponent = nullptr;

	UPROPERTY(VisibleAnywhere)
	UProjectileMovementComponent* ProjectileMovementComponent = nullptr;

	UPROPERTY(VisibleAnywhere)
	UParticleSystemComponent* ParticleSystemComponent = nullptr;

public:	
	virtual void Tick(float DeltaTime) override;

};
