// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/SBTTaskNode_Heal.h"

#include "AIController.h"
#include "SAttributeComponent.h"

EBTNodeResult::Type USBTTaskNode_Heal::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBlackboardComponent* BlackboardComponent = OwnerComp.GetBlackboardComponent();
	if (ensure(BlackboardComponent))
	{
		AAIController* AIController = OwnerComp.GetAIOwner();
		if(!ensure(AIController))
		{
			return EBTNodeResult::Failed;
		}

		APawn* AIPawn = AIController->GetPawn();
		if(!ensure(AIPawn))
		{
			return EBTNodeResult::Failed;
		}

		USAttributeComponent* AIAttributeComponent = Cast<USAttributeComponent>(AIPawn->GetComponentByClass(USAttributeComponent::StaticClass()));
		if(!ensure(AIAttributeComponent))
		{
			return EBTNodeResult::Failed;
		}

		AIAttributeComponent->ApplyHealthChange(HealDelta);
		
		return EBTNodeResult::Succeeded;
	}
	
	return EBTNodeResult::Failed;
}
