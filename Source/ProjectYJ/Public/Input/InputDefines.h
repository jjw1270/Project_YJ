#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "InputDefines.generated.h"

UENUM(BlueprintType)
enum class EAbilityInputID : uint8
{
	NA = 0,
	Move,
	Jump,
};
