// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CustomUI.h"
#include "Blueprint/UserWidget.h"
#include "AnimatableWidget.generated.h"

UENUM()
enum class EWidgetAnimState : uint8
{
	Hide = 0,
	OnShow,
	Idle,
	OnHide,
};

/**
 Start - Idle - Hide 애니메이션 관리
 */
UCLASS()
class CUSTOMUI_API UAnimatableWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	EWidgetAnimState _AnimState = EWidgetAnimState::Hide;
	
protected:
	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& _geo, float _delta) override;

	void DriveAnimState(float _delta);

	UFUNCTION()
	void OnVisibilityChanged(ESlateVisibility _visibility);


};
