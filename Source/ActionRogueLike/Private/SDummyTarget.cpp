// Fill out your copyright notice in the Description page of Project Settings.


#include "SDummyTarget.h"

#include "SAttributeComponent.h"

ASDummyTarget::ASDummyTarget()
{
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshComponent");
	RootComponent = MeshComponent;

	AttributeComponent = CreateDefaultSubobject<USAttributeComponent>("AttributeComponent");
}

void ASDummyTarget::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	AttributeComponent->OnHealthChanged.AddDynamic(this, &ASDummyTarget::OnHealthChanged);
}

void ASDummyTarget::OnHealthChanged(AActor* ActorInstigator, USAttributeComponent* OwningComponent, float NewHealth, float Delta)
{
	if (Delta < 0.f)
	{
		MeshComponent->SetScalarParameterValueOnMaterials("TimeToHit", GetWorld()->TimeSeconds);
	}
}


