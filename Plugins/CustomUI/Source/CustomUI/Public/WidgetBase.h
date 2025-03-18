// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CustomUI.h"
#include "Blueprint/UserWidget.h"
#include "WidgetBase.generated.h"

UENUM()
enum class EWidgetAnimState : uint8
{
	Hide,
	OnShow,			// Start Anim 재생중
	Idle,
	OnHide,			// Hide Anim 재생중
};

UENUM(BlueprintType)
enum class EWidgetHideType : uint8
{
	NA					UMETA(Hidden),
	RemoveFromParent,
	Collapsed,
	Hidden
};

/**
 Start - Idle - Hide 애니메이션 관리
 */
UCLASS()
class CUSTOMUI_API UWidgetBase : public UUserWidget
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleAnywhere, Category = "Anim")
	FString OnShowAnimStr = FString(TEXT("OnShowAnim"));

	UPROPERTY(Transient, meta = (BindWidgetAnimOptional))
	TObjectPtr<UWidgetAnimation> OnShowAnim = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Anim")
	FString IdleAnimStr = FString(TEXT("IdleAnim"));

	UPROPERTY(Transient, meta = (BindWidgetAnimOptional))
	TObjectPtr<UWidgetAnimation> IdleAnim = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Anim")
	FString OnHideAnimStr = FString(TEXT("OnHideAnim"));

	UPROPERTY(Transient, meta = (BindWidgetAnimOptional))
	TObjectPtr<UWidgetAnimation> OnHideAnim = nullptr;
	
private:
	EWidgetAnimState _State = EWidgetAnimState::Hide;

	UPROPERTY()
	TObjectPtr<UWidgetAnimation> _CurrentStateAnim = nullptr;

	EWidgetHideType _HideType = EWidgetHideType::NA;

protected:
	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& _geo, float _delta) override;
	virtual void OnAnimationFinished_Implementation(const UWidgetAnimation* _anim) override;

private:
	void SetState(EWidgetAnimState _new_state);
	void HideWidget();

protected:
	UFUNCTION()
	virtual void OnVisibilityChanged(ESlateVisibility _visibility);

	UFUNCTION(BlueprintNativeEvent)
	void OnStateChanged(EWidgetAnimState _old_state);
	virtual void OnStateChanged_Implementation(EWidgetAnimState _old_state);
	
public:
	UFUNCTION(BlueprintCallable)
	void Hide(EWidgetHideType _type, bool _force_immediately);

	EWidgetAnimState GetWidgetAnimState() const { return _State; }
};
