// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "NativeGameplayTags.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "ShrimpoGameplayTags.generated.h"

namespace ShrimpoGameplayTags
{
	PROJECTYJ_API	UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Move);
	PROJECTYJ_API	UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Look);
	PROJECTYJ_API	UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Jump);

}

UCLASS()
class PROJECTYJ_API UTagManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()

protected:
	TArray<FName> _GameplayTagNames;

public:
	virtual void Initialize(FSubsystemCollectionBase& _collection) override;

	UFUNCTION(BlueprintPure)
	int32 FindInputID(const FGameplayTag& _tag) const;
	
protected:
	void ValidateGameplayTags();
};
