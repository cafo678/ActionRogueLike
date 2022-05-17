// Fill out your copyright notice in the Description page of Project Settings.


#include "ExplosiveBarrel.h"

#include "Components/StaticMeshComponent.h"
#include "PhysicsEngine/RadialForceComponent.h"

AExplosiveBarrel::AExplosiveBarrel()
{
	PrimaryActorTick.bCanEverTick = true;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshComponent");
	StaticMeshComponent->SetSimulatePhysics(true);
	StaticMeshComponent->SetCollisionProfileName("PhysicsActor");
	
	RootComponent = StaticMeshComponent;

	RadialForceComponent = CreateDefaultSubobject<URadialForceComponent>("RadialForceComponent");
	RadialForceComponent->SetupAttachment(StaticMeshComponent);
	RadialForceComponent->ImpulseStrength = 5000.f;
	RadialForceComponent->bImpulseVelChange = true;
	RadialForceComponent->Radius = 700.f;
	RadialForceComponent->SetAutoActivate(false);
	RadialForceComponent->bIgnoreOwningActor = true;
}

void AExplosiveBarrel::BeginPlay()
{
	Super::BeginPlay();
}

void AExplosiveBarrel::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	
	StaticMeshComponent->OnComponentHit.AddDynamic(this, &AExplosiveBarrel::OnHitCallback);
}

void AExplosiveBarrel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AExplosiveBarrel::OnHitCallback(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	RadialForceComponent->FireImpulse();
}

