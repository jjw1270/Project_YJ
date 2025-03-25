#include "Input/InputDefines.h"
#include "CommonLibrary.h"
#include "InputAction.h"

const UInputAction* UInputActionData::FindNativeInputAction(const FGameplayTag& _tag) const
{
	auto input_action_ptr = NativeInputActionMap.Find(_tag);
	if (IsValid(input_action_ptr))
	{
		return *input_action_ptr;
	}

	return nullptr;
};

const UInputAction* UInputActionData::FindAbilityInputAction(const FGameplayTag& _tag) const
{
	auto input_action_ptr = AbilityInputActionMap.Find(_tag);
	if (IsValid(input_action_ptr))
	{
		return *input_action_ptr;
	}

	return nullptr;
};
