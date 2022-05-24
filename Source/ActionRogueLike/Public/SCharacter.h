// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class USInteractionComponent;
class USAttributeComponent;
class USActionComponent;

UCLASS()
class ACTIONROGUELIKE_API ASCharacter : public ACharacter
{
	GENERATED_BODY()
	
public:
	ASCharacter();

protected:
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;

public:	
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
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

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USActionComponent* ActionComponent = nullptr;

	void MoveForward(float Value);
	void MoveRight(float Value);

	void SprintStart();
	void SprintStop();
	
	void PrimaryAttack();
	void SecondaryAttack();
	
	void PrimaryInteract();
	
	UFUNCTION()
	void OnHealthChanged(AActor* ActorInstigator, USAttributeComponent* OwningComponent, float NewHealth, float Delta);

public:
	virtual FVector GetPawnViewLocation() const override;
};


