#pragma once
#include "CoreMinimal.h"
#include "CommonLibrary.h"
#include "EnhancedInputComponent.h"
#include "Input/InputDefines.h"
#include "ShrimpoInputComponent.generated.h"

UCLASS()
class UShrimpoInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()

public:
	template<typename UserClass, typename FuncType>
	void BindNativeAction(UInputActionData* _data, ENativeInputActionID _native_input_id, ETriggerEvent _trigger_event, UserClass* _obj, FuncType _func)
	{
		if (IsAnyInvalid(_data, _obj))
			return;

		auto input_action = _data->FindNativeInputAction(_native_input_id);
		if (IsInvalid(input_action))
			return;

		if (_func)
		{
			BindAction(input_action, _trigger_event, _obj, _func);
		}
	}

	template<typename UserClass, typename FuncType>
	void BindAbilityAction(UInputActionData* _data, EAbilityInputActionID _ability_input_id, UserClass* _obj, FuncType _func)
	{
		if (IsAnyInvalid(_data, _obj))
			return;

		auto input_action = _data->FindAbilityInputAction(_ability_input_id);
		if (IsInvalid(input_action))
			return;

		if (_func)
		{
			BindAction(input_action, ETriggerEvent::Started, _obj, _func, true, _ability_input_id);
			BindAction(input_action, ETriggerEvent::Completed, _obj, _func, false, _ability_input_id);
		}
	}
};
