// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimatableWidget.h"

void UAnimatableWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	OnNativeVisibilityChanged.AddUObject(this, &UAnimatableWidget::OnVisibilityChanged);
	TRACE(TEXT("Hello"));
}

void UAnimatableWidget::NativeConstruct()
{
	Super::NativeConstruct();


}

void UAnimatableWidget::NativeTick(const FGeometry& _geo, float _delta)
{
	Super::NativeTick(_geo, _delta);

	DriveAnimState(_delta);
}

void UAnimatableWidget::OnVisibilityChanged(ESlateVisibility _visibility)
{

}

void UAnimatableWidget::DriveAnimState(float _delta)
{
	// TRACE(CustomUI, _delta, TEXT("HLL"));
}
