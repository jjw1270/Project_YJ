// Fill out your copyright notice in the Description page of Project Settings.


#include "WidgetBase.h"

void UWidgetBase::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	OnNativeVisibilityChanged.AddUObject(this, &UWidgetBase::OnVisibilityChanged);
}

void UWidgetBase::NativeConstruct()
{
	Super::NativeConstruct();
}

void UWidgetBase::NativeTick(const FGeometry& _geo, float _delta)
{
	Super::NativeTick(_geo, _delta);

	DriveState(_delta);
}

void UWidgetBase::OnVisibilityChanged(ESlateVisibility _visibility)
{
	switch (_visibility)
	{
	case ESlateVisibility::Collapsed:
	case ESlateVisibility::Hidden:
		_State = EWidgetAnimState::Hide;
		break;
	default:
		break;
	}
}

void UWidgetBase::DriveState(float _delta)
{
	switch (_State)
	{
	case EWidgetAnimState::Hide:
		SetState(EWidgetAnimState::OnShow);
		break;
	case EWidgetAnimState::OnShow:
		break;
	case EWidgetAnimState::Idle:
		break;
	case EWidgetAnimState::OnHide:
		break;
	default:
		break;
	}
}

void UWidgetBase::SetState(EWidgetAnimState _new_state)
{
	if (_State == _new_state)
		return;
	_State = _new_state;

}
