// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class USInteractionComponent;


UCLASS()
class ACTIONROGUELIKE_API ASCharacter : public ACharacter
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditAnywhere, Category = Attack)
	TSubclassOf<AActor> PrimaryProjectileClass;

	UPROPERTY(EditAnywhere, Category = Attack)
	TSubclassOf<AActor> SecondaryProjectileClass;

	UPROPERTY(EditAnywhere, Category = Attack)
	UAnimMontage* AttackMontage;

	UPROPERTY(EditAnywhere, Category = Attack)
	float PrimaryAttackTimerDelay = 0.2f;

	UPROPERTY(EditAnywhere, Category = Attack)
	float SecondaryAttackTimerDelay = 0.5f;

	UPROPERTY(EditAnywhere, Category = Attack)
	float ProjectileTraceMultiplier = 1000.f;

	FTimerHandle AttackTimerHandle;
public:
	ASCharacter();

protected:
	virtual void BeginPlay() override;
	
	UPROPERTY()
	UCharacterMovementComponent* CharacterMovementComponent = nullptr;
	
	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArmComponent = nullptr;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* CameraComponent = nullptr;

	UPROPERTY(VisibleAnywhere)
	USInteractionComponent* InteractionComponent = nullptr;

	void MoveForward(float Value);
	void MoveRight(float Value);
	
	void SpawnProjectile(UAnimMontage* AnimMontageToPlay, float AttackTimerDelay, TSubclassOf<AActor> ProjectileClass);
	void PrimaryInteract();
	
	void OnAttackTimerElapsed(TSubclassOf<AActor> ProjectileClass);

public:	
	virtual void Tick(float DeltaTime) override;
	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};


