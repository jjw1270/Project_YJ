// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "AbilitySystemInterface.h"
#include "BasePlayerState.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTYJ_API ABasePlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere)
	TObjectPtr<class UAbilitySystemComponent> _AbilitySystemComp = nullptr;
	
public:
	ABasePlayerState(const FObjectInitializer& _object_initializer = FObjectInitializer::Get());


public:
	UAbilitySystemComponent* GetAbilitySystemComponent() const { return _AbilitySystemComp; }
};
