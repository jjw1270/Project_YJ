// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/YJAttributeSet.h"
#include "Net/UnrealNetwork.h"

UYJAttributeSet::UYJAttributeSet()
{
	Init_Health(100.0f);

}

void UYJAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UYJAttributeSet, _Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UYJAttributeSet, _MaxHealth, COND_None, REPNOTIFY_Always);
}

void UYJAttributeSet::OnRep_Health(const FGameplayAttributeData& _old_val)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UYJAttributeSet, _Health, _old_val);
}

void UYJAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& _old_val)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UYJAttributeSet, _MaxHealth, _old_val);
}
