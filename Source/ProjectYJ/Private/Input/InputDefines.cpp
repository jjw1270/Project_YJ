#include "Input/InputDefines.h"
#include "CommonLibrary.h"
#include "InputAction.h"

const UInputAction* UInputActionData::FindNativeInputAction(ENativeInputActionID _input_id) const
{
	auto input_action_ptr = NativeInputActionMap.Find(_input_id);
	if (IsValid(input_action_ptr))
	{
		return *input_action_ptr;
	}

	return nullptr;
};

const UInputAction* UInputActionData::FindAbilityInputAction(EAbilityInputActionID _input_id) const
{
	auto input_action_ptr = AbilityInputActionMap.Find(_input_id);
	if (IsValid(input_action_ptr))
	{
		return *input_action_ptr;
	}

	return nullptr;
};
