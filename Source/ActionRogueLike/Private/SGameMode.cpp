// Fill out your copyright notice in the Description page of Project Settings.


#include "SGameMode.h"

#include "EngineUtils.h"
#include "SAttributeComponent.h"
#include "AI/SAICharacter.h"
#include "EnvironmentQuery/EnvQueryManager.h"

void ASGameMode::StartPlay()
{
	Super::StartPlay();

	GetWorldTimerManager().SetTimer(SpawnBotsTimerHandle, this, &ASGameMode::OnSpawnBotTimerElapsed, BotSpawnTimerInterval, true);
}

void ASGameMode::OnSpawnBotTimerElapsed()
{
	int32 NumOfAliveBots = 0;
	for (TActorIterator<ASAICharacter> It(GetWorld()); It; ++It)
	{
		ASAICharacter* Bot = *It;

		USAttributeComponent* AttributeComponent = Cast<USAttributeComponent>(Bot->GetComponentByClass(USAttributeComponent::StaticClass()));
		if (AttributeComponent->IsAlive())
		{
			NumOfAliveBots++;
		}
	}

	int32 MaxBotAlivePermitted = 10;

	if (ensure(DifficultyCurve))
	{
		MaxBotAlivePermitted = DifficultyCurve->GetFloatValue(GetWorld()->TimeSeconds);
	}
	
	if (NumOfAliveBots >= MaxBotAlivePermitted)
	{
		return;
	}
	
	UEnvQueryInstanceBlueprintWrapper* SpawnBotQueryInstance = UEnvQueryManager::RunEQSQuery(this, SpawnBotQuery,
		this, EEnvQueryRunMode::RandomBest5Pct, nullptr);

	if (ensure(SpawnBotQueryInstance))
	{
		SpawnBotQueryInstance->GetOnQueryFinishedEvent().AddDynamic(this, &ASGameMode::OnSpawnBotQueryCompleted);
	}
}

void ASGameMode::OnSpawnBotQueryCompleted(UEnvQueryInstanceBlueprintWrapper* QueryInstance, EEnvQueryStatus::Type QueryStatus)
{
	if (QueryStatus != EEnvQueryStatus::Success)
	{
		UE_LOG(LogTemp, Warning, TEXT("Spawn query Failed!"));
		return;
	}

	TArray<FVector> SpawnLocations = QueryInstance->GetResultsAsLocations();

	FActorSpawnParameters Params;
	Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	
	if (SpawnLocations.Num() > 0)
	{
		GetWorld()->SpawnActor<AActor>(BotClass, SpawnLocations[0], FRotator::ZeroRotator, Params);
	}
}
