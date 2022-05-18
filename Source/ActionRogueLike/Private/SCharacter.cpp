// Fill out your copyright notice in the Description page of Project Settings.


#include "SCharacter.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "DrawDebugHelpers.h"
#include "SInteractionComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/GameUserSettings.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

ASCharacter::ASCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	CharacterMovementComponent = GetCharacterMovement();
	CharacterMovementComponent->bOrientRotationToMovement = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
	SpringArmComponent->SetupAttachment(RootComponent);
	SpringArmComponent->bUsePawnControlRotation = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComponent->SetupAttachment(SpringArmComponent);

	InteractionComponent = CreateDefaultSubobject<USInteractionComponent>("InteractionComponent");

	bUseControllerRotationYaw = false;
}

void ASCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	// This is entirely optional, it draws two arrows to visualize rotations of the player

	// -- Rotation Visualization -- //
	const float DrawScale = 100.0f;
	const float Thickness = 5.0f;

	FVector LineStart = GetActorLocation();
	// Offset to the right of pawn
	LineStart += GetActorRightVector() * 100.0f;
	// Set line end in direction of the actor's forward
	FVector ActorDirection_LineEnd = LineStart + (GetActorForwardVector() * 100.0f);
	// Draw Actor's Direction
	DrawDebugDirectionalArrow(GetWorld(), LineStart, ActorDirection_LineEnd, DrawScale, FColor::Yellow, false, 0.0f, 0, Thickness);

	FVector ControllerDirection_LineEnd = LineStart + (GetControlRotation().Vector() * 100.0f);
	// Draw 'Controller' Rotation ('PlayerController' that 'possessed' this character)
	DrawDebugDirectionalArrow(GetWorld(), LineStart, ControllerDirection_LineEnd, DrawScale, FColor::Green, false, 0.0f, 0, Thickness);
}

void ASCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ASCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ASCharacter::MoveRight);

	PlayerInputComponent->BindAxis("Turn", this, &ASCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &ASCharacter::AddControllerPitchInput);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ASCharacter::Jump);

	DECLARE_DELEGATE_ThreeParams(FAttackDelegate, UAnimMontage*, float, TSubclassOf<AActor>);
	
	PlayerInputComponent->BindAction<FAttackDelegate>("PrimaryAttack", IE_Pressed, this, &ASCharacter::SpawnProjectile,
		AttackMontage, PrimaryAttackTimerDelay, PrimaryProjectileClass);
	
	PlayerInputComponent->BindAction<FAttackDelegate>("SecondaryAttack", IE_Pressed, this, &ASCharacter::SpawnProjectile,
		AttackMontage, SecondaryAttackTimerDelay, SecondaryProjectileClass);
	
	PlayerInputComponent->BindAction("PrimaryInteract", IE_Pressed, this, &ASCharacter::PrimaryInteract);
}

void ASCharacter::MoveForward(float Value)
{
	FRotator ControlRot = GetControlRotation();
	ControlRot.Pitch = 0.f;
	ControlRot.Roll = 0.f;
	
	AddMovementInput(ControlRot.Vector(), Value);
}

void ASCharacter::MoveRight(float Value)
{
	FRotator ControlRot = GetControlRotation();
	ControlRot.Pitch = 0.f;
	ControlRot.Roll = 0.f;

	FVector ControlRightVector = FRotationMatrix(ControlRot).GetScaledAxis(EAxis::Y);
	
	AddMovementInput(ControlRightVector, Value);
}

void ASCharacter::SpawnProjectile(UAnimMontage* AnimMontageToPlay, float AttackTimerDelay, TSubclassOf<AActor> ProjectileClass)
{
	PlayAnimMontage(AnimMontageToPlay);
	
	FTimerDelegate AttackTimerDelegate = FTimerDelegate::CreateUObject( this, &ASCharacter::OnAttackTimerElapsed, ProjectileClass);
	GetWorldTimerManager().SetTimer( AttackTimerHandle, AttackTimerDelegate, AttackTimerDelay, false );
}

void ASCharacter::OnAttackTimerElapsed(TSubclassOf<AActor> ProjectileClass)
{
	FVector ScreenCenterInWorldSpace, WorldDirection;
	FVector2D ViewportSize;
	
	UGameViewportClient* GameViewportClient = GetWorld()->GetGameViewport();
	GameViewportClient->GetViewportSize(ViewportSize);

	APlayerController* PlayerController	= Cast<APlayerController>(GetController());
	PlayerController->DeprojectScreenPositionToWorld(ViewportSize.X * 0.5, ViewportSize.Y * 0.5, ScreenCenterInWorldSpace, WorldDirection);
	
	const FVector HandLocation = GetMesh()->GetSocketLocation("Muzzle_01");
	const FVector LineTraceEndLocation = ScreenCenterInWorldSpace + (GetControlRotation().Vector() * ProjectileTraceMultiplier);

	FHitResult Hit;
	
	FCollisionObjectQueryParams CollisionObjectQueryParams;
	CollisionObjectQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);
	CollisionObjectQueryParams.AddObjectTypesToQuery(ECC_WorldStatic);

	const bool bHasLineTraceHittedSomething = GetWorld()->LineTraceSingleByObjectType(Hit, HandLocation, LineTraceEndLocation, CollisionObjectQueryParams);
	//DrawDebugLine(GetWorld(), HandLocation, LineTraceEndLocation, FColor::Red, false, 5.f, 0, 2.f);

	FVector HitLocation = LineTraceEndLocation;

	if (bHasLineTraceHittedSomething)
	{
		HitLocation = Hit.ImpactPoint;
	}
	
	const FRotator SpawnRotation = FRotationMatrix::MakeFromX(HitLocation - HandLocation).Rotator();

	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnParameters.Instigator = this;
	
	GetWorld()->SpawnActor<AActor>(ProjectileClass, FTransform(SpawnRotation, HandLocation), SpawnParameters);
}

void ASCharacter::PrimaryInteract()
{
	InteractionComponent->PrimaryInteract();
}
