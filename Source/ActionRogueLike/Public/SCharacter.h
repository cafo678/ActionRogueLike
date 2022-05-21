// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class USInteractionComponent;
class USAttributeComponent;

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
	float PrimaryAttackTimerDelay;

	UPROPERTY(EditAnywhere, Category = Attack)
	float SecondaryAttackTimerDelay;

	UPROPERTY(EditAnywhere, Category = Attack)
	float ProjectileTraceMultiplier;

	FTimerHandle AttackTimerHandle;
public:
	ASCharacter();

protected:
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;
	
	UPROPERTY()
	UCharacterMovementComponent* CharacterMovementComponent = nullptr;
	
	UPROPERTY(VisibleAnywhere, Category = "Components")
	USpringArmComponent* SpringArmComponent = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UCameraComponent* CameraComponent = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	USInteractionComponent* InteractionComponent = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USAttributeComponent* AttributeComponent = nullptr;

	void MoveForward(float Value);
	void MoveRight(float Value);
	
	void SpawnProjectile(UAnimMontage* AnimMontageToPlay, float AttackTimerDelay, TSubclassOf<AActor> ProjectileClass);
	void PrimaryInteract();
	
	void OnAttackTimerElapsed(TSubclassOf<AActor> ProjectileClass);

	UFUNCTION()
	void OnHealthChanged(AActor* ActorInstigator, USAttributeComponent* OwningComponent, float NewHealth, float Delta);

public:	
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};


