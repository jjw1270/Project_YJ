// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CustomUI.h"
#include "Blueprint/UserWidget.h"
#include "WidgetBase.generated.h"

UENUM()
enum class EWidgetAnimState : uint8
{
	Hide = 0,
	OnShow,			// Start Anim 재생중
	Idle,
	OnHide,			// Hide Anim 재생중
};

/**
 Start - Idle - Hide 애니메이션 관리
 */
UCLASS()
class CUSTOMUI_API UWidgetBase : public UUserWidget
{
	GENERATED_BODY()
	
private:
	EWidgetAnimState _State = EWidgetAnimState::Hide;
	
	UPROPERTY(Transient, meta = (BindWidgetAnim))
	TObjectPtr<UWidgetAnimation> _OnShowAnim = nullptr;

	UPROPERTY(Transient, meta = (BindWidgetAnim))
	TObjectPtr<UWidgetAnimation> _IdleAnim = nullptr;

	UPROPERTY(Transient, meta = (BindWidgetAnim))
	TObjectPtr<UWidgetAnimation> _OnHideAnim = nullptr;

protected:
	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& _geo, float _delta) override;

private:
	void DriveState(float _delta);
	void SetState(EWidgetAnimState _new_state);

protected:
	UFUNCTION()
	virtual void OnVisibilityChanged(ESlateVisibility _visibility);

public:
	EWidgetAnimState GetWidgetAnimState() const { return _State; }
};
