// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/SHealthChangeWidget.h"

#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/SizeBox.h"
#include "Kismet/GameplayStatics.h"

void USHealthChangeWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (!ActorToAttach)
	{
		UE_LOG(LogTemp, Warning, TEXT("ActorToAttach not set! Removing widget"));

		RemoveFromParent();

		return;
	}
	
	FVector2d ScreenPosition;
	if (UGameplayStatics::ProjectWorldToScreen(GetOwningPlayer(), ActorToAttach->GetActorLocation(), ScreenPosition))
	{
		float Scale = UWidgetLayoutLibrary::GetViewportScale(this);

		ScreenPosition /= Scale;

		if (ParentSizeBox)
		{
			ParentSizeBox->SetRenderTranslation(ScreenPosition);
		}
	}
}
