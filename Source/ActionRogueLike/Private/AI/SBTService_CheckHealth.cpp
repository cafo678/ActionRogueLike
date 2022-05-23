// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/SBTService_CheckHealth.h"

#include "AIController.h"
#include "SAttributeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

void USBTService_CheckHealth::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	
	UBlackboardComponent* BlackboardComponent = OwnerComp.GetBlackboardComponent();
	if (ensure(BlackboardComponent))
	{
		AAIController* AIController = OwnerComp.GetAIOwner();
		if(!ensure(AIController))
		{
			return;
		}

		APawn* AIPawn = AIController->GetPawn();
		if(!ensure(AIPawn))
		{
			return;
		}

		USAttributeComponent* AIAttributeComponent = Cast<USAttributeComponent>(AIPawn->GetComponentByClass(USAttributeComponent::StaticClass()));
		if(!ensure(AIAttributeComponent))
		{
			return;
		}

		const float Health = AIAttributeComponent->GetCurrentHealth();
		const float MaxHealth = AIAttributeComponent->GetMaxHealth();
		const float PercentageHealth = Health / MaxHealth * 100;

		BlackboardComponent->SetValueAsBool(IsFullHealthKey.SelectedKeyName, Health == MaxHealth);
		BlackboardComponent->SetValueAsBool(IsDeadKey.SelectedKeyName, Health == 0.f);
		BlackboardComponent->SetValueAsBool(IsLowHealthKey.SelectedKeyName, PercentageHealth < 30.f);
	}
}
