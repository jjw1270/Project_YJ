// Fill out your copyright notice in the Description page of Project Settings.


#include "WidgetBase.h"
#include "Animation/WidgetAnimation.h"
#include "Blueprint/WidgetTree.h"
#include "MovieScene.h"

void UWidgetBase::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	OnNativeVisibilityChanged.AddUObject(this, &UWidgetBase::OnVisibilityChanged);
}

void UWidgetBase::NativeConstruct()
{
	Super::NativeConstruct();

	SetRenderOpacity(0.0f);
}

void UWidgetBase::NativeTick(const FGeometry& _geo, float _delta)
{
	Super::NativeTick(_geo, _delta);

	if (_State == EWidgetAnimState::Hide)
	{
		SetState(EWidgetAnimState::OnShow);
	}
}

void UWidgetBase::OnAnimationFinished_Implementation(const UWidgetAnimation* _anim)
{
	Super::OnAnimationFinished_Implementation(_anim);

	if (IsValid(_anim) && _CurrentStateAnim == _anim)
	{
		switch (_State)
		{
		case EWidgetAnimState::OnShow:
			if (_CurrentStateAnim == OnShowAnim)
			{
				SetState(EWidgetAnimState::Idle);
			}
			break;
		case EWidgetAnimState::OnHide:
			if (_CurrentStateAnim == OnHideAnim)
			{
				SetState(EWidgetAnimState::Hide);
			}
			break;
		default:
			break;
		}
	}
}

void UWidgetBase::SetState(EWidgetAnimState _new_state)
{
	if (_State == _new_state)
		return;

	EWidgetAnimState _old_state = _State;
	_State = _new_state;

	OnStateChanged(_old_state);
}

void UWidgetBase::OnVisibilityChanged(ESlateVisibility _visibility)
{
	if (_visibility == ESlateVisibility::Collapsed || _visibility == ESlateVisibility::Hidden)
	{
		SetRenderOpacity(0.0f);
		_CurrentStateAnim = nullptr;
		_State = EWidgetAnimState::Hide;
	}
}

void UWidgetBase::OnStateChanged_Implementation(EWidgetAnimState _old_state)
{
	if (_State == EWidgetAnimState::Hide)
	{
		HideWidget();
		return;
	}

	UWidgetAnimation* anim_to_play = nullptr;
	bool is_idle = false;

	switch (_State)
	{
	case EWidgetAnimState::OnShow:
		SetRenderOpacity(1.0f);
		anim_to_play = OnShowAnim;
		break;
	case EWidgetAnimState::Idle:
		anim_to_play = IdleAnim;
		is_idle = true;
		break;
	case EWidgetAnimState::OnHide:
		anim_to_play = OnHideAnim;
		break;
	default:
		break;
	}

	StopAnimation(_CurrentStateAnim); // Event는 호출되지 않는다.

	if (IsValid(anim_to_play))
	{
		_CurrentStateAnim = MoveTemp(anim_to_play);
		PlayAnimation(_CurrentStateAnim, 0.0f, is_idle ? 0 : 1);
	}
	else
	{
		if (_State == EWidgetAnimState::OnShow)
		{
			SetState(EWidgetAnimState::Idle);
		}
		else if (_State == EWidgetAnimState::OnHide)
		{
			SetState(EWidgetAnimState::Hide);
		}
	}
}

void UWidgetBase::Hide(EWidgetHideType _type, bool _force_immediately)
{
	if (_type == EWidgetHideType::NA)
	{
		TRACE_ERROR(TEXT("_type이 NA 일 수 없습니다."));
		return;
	}

	if (_HideType == _type)
		return;
	_HideType = _type;

	if (_force_immediately)
	{
		HideWidget();
	}
	else
	{
		SetState(EWidgetAnimState::OnHide);
	}
}

void UWidgetBase::HideWidget()
{
	switch (_HideType)
	{
	case EWidgetHideType::NA:
		TRACE_ERROR(TEXT("_HideType이 NA 일 수 없습니다."));
		break;
	case EWidgetHideType::RemoveFromParent:
		RemoveFromParent();
		break;
	case EWidgetHideType::Collapsed:
		Super::SetVisibility(ESlateVisibility::Collapsed);
		break;
	case EWidgetHideType::Hidden:
		Super::SetVisibility(ESlateVisibility::Hidden);
		break;
	}

	_HideType = EWidgetHideType::NA;
}
