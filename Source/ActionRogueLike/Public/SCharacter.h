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
	TSubclassOf<AActor> ProjectileClass;

	UPROPERTY(EditAnywhere, Category = Attack)
	UAnimMontage* AttackMontage;

	UPROPERTY(EditAnywhere, Category = Attack)
	float AttackTimerDelay = 0.2f;

	UPROPERTY(EditAnywhere, Category = Attack)
	float ProjectileTraceMultiplier = 1000.f;

	FTimerHandle PrimaryAttackTimerHandle;
	
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
	
	void PrimaryAttack();
	void PrimaryInteract();
	
	void OnPrimaryAttackTimerElapsed();

public:	
	virtual void Tick(float DeltaTime) override;
	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};


