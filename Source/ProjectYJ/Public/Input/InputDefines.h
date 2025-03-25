#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "GameplayTagContainer.h"
#include "InputDefines.generated.h"


UCLASS(BlueprintType, Const)
class UInputActionData : public UDataAsset
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	const UInputAction* FindNativeInputAction(const FGameplayTag& _tag) const;

	UFUNCTION(BlueprintCallable)
	const UInputAction* FindAbilityInputAction(const FGameplayTag& _tag) const;

public:
	// 바인딩 하는 대상에서 입력 이벤트에 호출받는 함수 구현
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TMap<FGameplayTag, TObjectPtr<UInputAction>> NativeInputActionMap;

	// 연결된 GA 실행
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TMap<FGameplayTag, TObjectPtr<UInputAction>> AbilityInputActionMap;
};
