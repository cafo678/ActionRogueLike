// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SAction.h"
#include "SAction_ProjectileAttack.generated.h"

UCLASS()
class ACTIONROGUELIKE_API USAction_ProjectileAttack : public USAction
{
	GENERATED_BODY()

public:
	USAction_ProjectileAttack();
	
protected:
	UPROPERTY(EditAnywhere, Category = Attack)
	TSubclassOf<AActor> ProjectileClass;

	UPROPERTY(EditAnywhere, Category = Attack)
	UAnimMontage* AttackMontage;

	UPROPERTY(EditAnywhere, Category = Attack)
	UParticleSystem* CastingFX;

	UPROPERTY(EditAnywhere, Category = Attack)
	float AttackTimerDelay;

	UPROPERTY(VisibleAnywhere, Category = Attack)
	FName SpawnBone;

public:
	virtual void StartAction_Implementation(AActor* Instigator) override;

protected:
	UFUNCTION()
	void OnAttackTimerElapsed(ACharacter* InstigatorCharacter);
	
};
