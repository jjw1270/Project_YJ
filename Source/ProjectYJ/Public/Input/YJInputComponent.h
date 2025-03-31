#pragma once
#include "CoreMinimal.h"
#include "CommonLibrary.h"
#include "EnhancedInputComponent.h"
#include "Input/InputDefines.h"
#include "YJInputComponent.generated.h"

UCLASS()
class UYJInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()

public:
	template<typename UserClass, typename FuncType>
	void BindNativeAction(UInputActionData* _data, const FGameplayTag& _tag, ETriggerEvent _trigger_event, UserClass* _obj, FuncType _func)
	{
		if (IsAnyInvalid(_data, _obj))
			return;

		auto input_action = _data->FindNativeInputAction(_tag);
		if (IsInvalid(input_action))
			return;

		if (_func)
		{
			BindAction(input_action, _trigger_event, _obj, _func);
		}
	}

	template<typename UserClass, typename FuncType>
	void BindAbilityAction(UInputActionData* _data, const FGameplayTag& _tag, UserClass* _obj, FuncType _func)
	{
		if (IsAnyInvalid(_data, _obj))
			return;

		auto input_action = _data->FindAbilityInputAction(_tag);
		if (IsInvalid(input_action))
			return;

		if (_func)
		{
			BindActionValueLambda(input_action, ETriggerEvent::Started, 
				[Obj(_obj), Func(_func), Tag(_tag)](const FInputActionValue& Value)
				{
					if (IsValid(Obj) && Func != nullptr && Tag.IsValid())
					{
						(Obj->*Func)(true, Tag);
					}
				}
			);

			BindActionValueLambda(input_action, ETriggerEvent::Completed,
				[Obj(_obj), Func(_func), Tag(_tag)](const FInputActionValue& Value)
				{
					if (IsValid(Obj) && Func != nullptr && Tag.IsValid())
					{
						(Obj->*Func)(false, Tag);
					}
				}
			);
		}
	}
};
