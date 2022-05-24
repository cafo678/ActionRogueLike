// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/SAICharacter.h"

#include "AIController.h"
#include "BrainComponent.h"
#include "SAttributeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Perception/PawnSensingComponent.h"

ASAICharacter::ASAICharacter()
{
	PawnSensingComponent = CreateDefaultSubobject<UPawnSensingComponent>("PawnSensingComponent");
	
	AttributeComponent = CreateDefaultSubobject<USAttributeComponent>("AttributeComponent");

	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Ignore);
	GetMesh()->SetGenerateOverlapEvents(true);
}

void ASAICharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	AttributeComponent->OnHealthChanged.AddDynamic(this, &ASAICharacter::OnHealthChanged);
	PawnSensingComponent->OnSeePawn.AddDynamic(this, &ASAICharacter::OnPawnSeen);
}

void ASAICharacter::OnHealthChanged(AActor* ActorInstigator, USAttributeComponent* OwningComponent, float NewHealth,
	float Delta)
{
	if (Delta < 0.f)
	{
		AAIController* AIController = Cast<AAIController>(GetController());
		
		if (ActorInstigator != this)
		{
			SetTargetActor(ActorInstigator);
		}
		
		if (NewHealth <= 0.f)
		{
			if (AIController)
			{
				AIController->GetBrainComponent()->StopLogic("Dead");
			}

			GetMesh()->SetCollisionProfileName("Ragdoll");
			GetMesh()->SetAllBodiesSimulatePhysics(true);
			GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			GetCharacterMovement()->DisableMovement();
			
			SetLifeSpan(10.f);
		}
	}
}

void ASAICharacter::OnPawnSeen(APawn* Pawn)
{
	SetTargetActor(Pawn);
}

void ASAICharacter::SetTargetActor(AActor* EnemyActor)
{
	AAIController* AIController = Cast<AAIController>(GetController());
	
	if (AIController)
	{
		UBlackboardComponent* BlackboardComponent = AIController->GetBlackboardComponent();
		
		BlackboardComponent->SetValueAsObject("TargetActor", EnemyActor);

		DrawDebugString(GetWorld(), EnemyActor->GetActorLocation(), "PLAYER SPOTTED", nullptr, FColor::White, 4.f, true);
	}
}

