// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/BasePlayerState.h"
#include "GameplayAbilities/Public/AbilitySystemComponent.h"

ABasePlayerState::ABasePlayerState(const FObjectInitializer& _object_initializer)
	:Super(_object_initializer)
{
	_AbilitySystemComp = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("ASComp"));
	if (IsValid(_AbilitySystemComp))
	{
		_AbilitySystemComp->SetIsReplicated(true);

		// GameplayEffect는 소유 클라이언트, GameplayTag와 GameplayCue만 모든 사람에게 Replicate
		_AbilitySystemComp->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

		// Set PlayerState's NetUpdateFrequency to the same as the Character.
		// Default is very low for PlayerStates ansd introduces perceived lag in the ability system.
		// 100 is probably way too high for a shipping game, you can adjust to fit your needs.
		SetNetUpdateFrequency(100.0f);
	}
}
