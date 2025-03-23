// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/BaseCharacter.h"
#include "AbilitySystemComponent.h"

ABaseCharacter::ABaseCharacter(const FObjectInitializer& _object_initializer)
	:Super(_object_initializer)
{
	PrimaryActorTick.bCanEverTick = true;
}

void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABaseCharacter::Tick(float _delta)
{
	Super::Tick(_delta);

}

UAbilitySystemComponent* ABaseCharacter::GetAbilitySystemComponent() const
{
	return _AbilitySystemComp.Get();
}
