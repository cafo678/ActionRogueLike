// Fill out your copyright notice in the Description page of Project Settings.


#include "SAction_ProjectileAttack.h"

#include "SCharacter.h"
#include "SGameplayFunctionLibrary.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

USAction_ProjectileAttack::USAction_ProjectileAttack()
{
	SpawnBone = "Muzzle_01";
	AttackTimerDelay = 0.2f;
}

void USAction_ProjectileAttack::StartAction_Implementation(AActor* Instigator)
{
	Super::StartAction_Implementation(Instigator);

	ACharacter* Character = Cast<ACharacter>(Instigator);
	if (Character)
	{
		Character->PlayAnimMontage(AttackMontage);

		UGameplayStatics::SpawnEmitterAttached(CastingFX, Character->GetMesh(), SpawnBone, FVector::ZeroVector,
			FRotator::ZeroRotator, EAttachLocation::SnapToTarget);

		FTimerHandle AttackTimerHandle;
		FTimerDelegate TimerDelegate;
		
		TimerDelegate.BindUFunction(this, "OnAttackTimerElapsed", Character);
		
		GetWorld()->GetTimerManager().SetTimer(AttackTimerHandle, TimerDelegate, AttackTimerDelay, false);
	}
}

void USAction_ProjectileAttack::OnAttackTimerElapsed(ACharacter* InstigatorCharacter)
{
	const FVector HandLocation = InstigatorCharacter->GetMesh()->GetSocketLocation("Muzzle_01");

	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnParameters.Instigator = InstigatorCharacter;

	FCollisionObjectQueryParams CollisionObjectQueryParams;
	CollisionObjectQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);
	CollisionObjectQueryParams.AddObjectTypesToQuery(ECC_WorldStatic);

	FCollisionQueryParams CollisionQueryParams;
	CollisionQueryParams.AddIgnoredActor(InstigatorCharacter);

	FCollisionShape CollisionShape;
	CollisionShape.SetSphere(20.f);

	FVector TraceStart = InstigatorCharacter->GetPawnViewLocation();
	FVector TraceEnd = TraceStart + (InstigatorCharacter->GetControlRotation().Vector() * 5000);
	
	FHitResult Hit;

	if (CVarDrawDebug.GetValueOnGameThread())
	{
		DrawDebugLine(GetWorld(), HandLocation, TraceEnd, FColor::Red, false, 5.f, 0, 2.f);

		if (GetWorld()->SweepSingleByObjectType(Hit, TraceStart, TraceEnd, FQuat::Identity, CollisionObjectQueryParams, CollisionShape))
		{
			TraceEnd = Hit.ImpactPoint;
		}
	}

	const FRotator SpawnRotation = FRotationMatrix::MakeFromX(TraceEnd - HandLocation).Rotator();	

	if (ensureAlways(ProjectileClass))
	{
		GetWorld()->SpawnActor<AActor>(ProjectileClass, FTransform(SpawnRotation, HandLocation), SpawnParameters);
	}

	StopAction(InstigatorCharacter);
}
