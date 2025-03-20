// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CustomUI.h"
#include "Blueprint/UserWidget.h"
#include "WidgetBase.generated.h"

UENUM()
enum class EWidgetState : uint8
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

DECLARE_DELEGATE_OneParam(FD_OnWidgetStateChanged, EWidgetState);
DECLARE_MULTICAST_DELEGATE_OneParam(FMD_OnWidgetStateChanged, EWidgetState);
DECLARE_DYNAMIC_DELEGATE_OneParam(FDD_OnWidgetStateChanged, EWidgetState, _old_state);

/**
 Start - Idle - Hide 애니메이션 관리
 */
UCLASS()
class CUSTOMUI_API UWidgetBase : public UUserWidget
{
	GENERATED_BODY()

#pragma region AnimState
private:
	// BindWidgetAnim Names
	UPROPERTY(VisibleAnywhere, Category = "Anim", meta = (Tooltip = "바인딩 애니메이션 이름"))
	FName OnShowAnimName = FName(TEXT("OnShowAnim"));

	UPROPERTY(VisibleAnywhere, Category = "Anim", meta = (Tooltip = "바인딩 애니메이션 이름"))
	FName IdleAnimName = FName(TEXT("IdleAnim"));

	UPROPERTY(VisibleAnywhere, Category = "Anim", meta = (Tooltip = "바인딩 애니메이션 이름"))
	FName OnHideAnimName = FName(TEXT("OnHideAnim"));

	// Widget Anims
	UPROPERTY(Transient, meta = (BindWidgetAnimOptional))
	TObjectPtr<UWidgetAnimation> OnShowAnim = nullptr;

	UPROPERTY(Transient, meta = (BindWidgetAnimOptional))
	TObjectPtr<UWidgetAnimation> IdleAnim = nullptr;

	UPROPERTY(Transient, meta = (BindWidgetAnimOptional))
	TObjectPtr<UWidgetAnimation> OnHideAnim = nullptr;

	UPROPERTY()
	TObjectPtr<UWidgetAnimation> _CurrentStateAnim = nullptr;

	UPROPERTY(EditAnywhere, Category = "Sound")
	TObjectPtr<USoundBase> OnShowSound = nullptr;

	UPROPERTY(EditAnywhere, Category = "Sound")
	TObjectPtr<USoundBase> OnHideSound = nullptr;

private:
	EWidgetState _WidgetState = EWidgetState::Hide;

	EWidgetHideType _WidgetHideType = EWidgetHideType::NA;

	FMD_OnWidgetStateChanged Event_OnWidgetStateChanged;

private:
	void SetState(EWidgetState _new_state);

public:
	UFUNCTION(BlueprintCallable)
	void Hide(EWidgetHideType _type, bool _force_immediately);

private:
	void HideWidget();

// Event
public:
	UFUNCTION(BlueprintCallable)
	void BindOnWidgetStateChanged(FDD_OnWidgetStateChanged _proc);
	void BindOnWidgetStateChanged(FD_OnWidgetStateChanged& _proc);

	UFUNCTION(BlueprintNativeEvent)
	void OnStateChanged(EWidgetState _old_state);
	virtual void OnStateChanged_Implementation(EWidgetState _old_state);

// Getters
public:
	UFUNCTION(BlueprintPure)
	EWidgetState GetWidgetState() const { return _WidgetState; }

#pragma endregion

protected:
	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& _geo, float _delta) override;
	virtual void OnAnimationFinished_Implementation(const UWidgetAnimation* _anim) override;
	virtual void SynchronizeProperties() override;

protected:
	UFUNCTION()
	virtual void OnVisibilityChanged(ESlateVisibility _visibility);

	// "BP"에서 변수에 변경이 있을 때 호출됩니다.
	UFUNCTION(BlueprintNativeEvent, meta = (ForceAsFunction))
	void OnSynchronizeProperties();
	void OnSynchronizeProperties_Implementation() {};

};
