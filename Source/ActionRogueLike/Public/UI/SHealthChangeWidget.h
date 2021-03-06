// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SHealthChangeWidget.generated.h"

class USizeBox;

UCLASS()
class ACTIONROGUELIKE_API USHealthChangeWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetActorToAttach(AActor* Actor) { ActorToAttach = Actor; }

	void SetHealthChange(float Delta) { HealthChange = Delta; }
	
protected:
	UPROPERTY(meta = (BindWidget))
	USizeBox* ParentSizeBox = nullptr;
	
	UPROPERTY(BlueprintReadOnly, Category = "UI")
	AActor* ActorToAttach = nullptr;

	UPROPERTY(BlueprintReadOnly, Category = "UI")
	float HealthChange;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
};
