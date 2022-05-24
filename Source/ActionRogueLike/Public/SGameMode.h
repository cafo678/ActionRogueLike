// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnvironmentQuery/EnvQueryTypes.h"
#include "GameFramework/GameModeBase.h"
#include "SGameMode.generated.h"

class UEnvQuery;
class UEnvQueryInstanceBlueprintWrapper;
class UCurveFloat;

UCLASS()
class ACTIONROGUELIKE_API ASGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	virtual void StartPlay() override;

private:
	FTimerHandle SpawnBotsTimerHandle;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
	float BotSpawnTimerInterval = 2.f;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
	UEnvQuery* SpawnBotQuery = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
	TSubclassOf<AActor> BotClass = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
	UCurveFloat* DifficultyCurve = nullptr;

	UFUNCTION()
	void OnSpawnBotTimerElapsed();

	UFUNCTION()
	void OnSpawnBotQueryCompleted(UEnvQueryInstanceBlueprintWrapper* QueryInstance, EEnvQueryStatus::Type QueryStatus);

public:
	virtual void OnActorKilled(AActor* KilledActor, AActor* Killer);
	
protected:
	UFUNCTION()
	void RespawnPlayerElapsed(AController* Controller);

	UPROPERTY(EditDefaultsOnly, Category = "Player")
	float PlayerRespawnTime = 2.f;
	
};
