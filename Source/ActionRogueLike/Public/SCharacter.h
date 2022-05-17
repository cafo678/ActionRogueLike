// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;

UCLASS()
class ACTIONROGUELIKE_API ASCharacter : public ACharacter
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, Category = Projectile)
	TSubclassOf<AActor> ProjectileClass;
	
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

	void MoveForward(float Value);
	void MoveRight(float Value);
	
	void PrimaryAttack();
	

public:	
	virtual void Tick(float DeltaTime) override;
	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};


