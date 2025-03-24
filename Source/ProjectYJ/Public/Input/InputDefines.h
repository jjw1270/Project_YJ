#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "InputDefines.generated.h"

UENUM(BlueprintType)
enum class ENativeInputActionID : uint8
{
	NA = 0,
	Look,
	Move,
};

UENUM(BlueprintType)
enum class EAbilityInputActionID : uint8
{
	NA = 0,
	Jump,
};

UCLASS(BlueprintType, Const)
class UInputActionData : public UDataAsset
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	const UInputAction* FindNativeInputAction(ENativeInputActionID _input_id) const;

	UFUNCTION(BlueprintCallable)
	const UInputAction* FindAbilityInputAction(EAbilityInputActionID _input_id) const;

public:
	// 바인딩 하는 대상에서 입력 이벤트에 호출받는 함수 구현
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TMap<ENativeInputActionID, TObjectPtr<UInputAction>> NativeInputActionMap;

	// 연결된 GA 실행
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TMap<EAbilityInputActionID, TObjectPtr<UInputAction>> AbilityInputActionMap;
};
