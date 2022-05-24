// Fill out your copyright notice in the Description page of Project Settings.


#include "SGameMode.h"

#include "EngineUtils.h"
#include "SAttributeComponent.h"
#include "SCharacter.h"
#include "AI/SAICharacter.h"
#include "EnvironmentQuery/EnvQueryManager.h"

static TAutoConsoleVariable<bool> CVarSpawnBots(TEXT("su.SpawnBots"), true, TEXT("Enable spawning bots via timer"), ECVF_Cheat);

void ASGameMode::StartPlay()
{
	Super::StartPlay();

	GetWorldTimerManager().SetTimer(SpawnBotsTimerHandle, this, &ASGameMode::OnSpawnBotTimerElapsed, BotSpawnTimerInterval, true);
}

void ASGameMode::OnSpawnBotTimerElapsed()
{
	if (!CVarSpawnBots.GetValueOnGameThread())
	{
		UE_LOG(LogTemp, Warning, TEXT("Bot Spawning Disabled by CVar"));
		return;
	}
	
	int32 NumOfAliveBots = 0;
	for (TActorIterator<ASAICharacter> It(GetWorld()); It; ++It)
	{
		ASAICharacter* Bot = *It;

		USAttributeComponent* AttributeComponent = USAttributeComponent::GetAttributeComponent(Bot);
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

void ASGameMode::OnActorKilled(AActor* KilledActor, AActor* Killer)
{
	ASCharacter* Player = Cast<ASCharacter>(KilledActor);
	if (Player)
	{
		FTimerHandle RespawnTimerHandle;
		FTimerDelegate TimerDelegate;
		
		TimerDelegate.BindUFunction(this, "RespawnPlayerElapsed", Player->GetController());
		
		GetWorldTimerManager().SetTimer(RespawnTimerHandle, TimerDelegate, PlayerRespawnTime, false);
	}
}

void ASGameMode::RespawnPlayerElapsed(AController* Controller)
{
	if (ensure(Controller))
	{
		Controller->UnPossess();
		
		RestartPlayer(Controller);
	}
}
