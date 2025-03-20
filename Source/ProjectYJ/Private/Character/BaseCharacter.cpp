// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/BaseCharacter.h"
#include "Player/BasePlayerState.h"
#include "GameplayAbilities/Public/AbilitySystemComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

ABaseCharacter::ABaseCharacter(const FObjectInitializer& _object_initializer)
	: Super(_object_initializer)
{
	PrimaryActorTick.bCanEverTick = true;

	_SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
	if (IsValid(_SpringArmComp))
	{
		_SpringArmComp->SetupAttachment(RootComponent);

		_CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
		if (IsValid(_CameraComp))
		{
			_CameraComp->SetupAttachment(_SpringArmComp);
		}
	}
}

void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABaseCharacter::PossessedBy(AController* _new_controller)
{
	Super::PossessedBy(_new_controller);

	// 서버에서 ASC 설정
	auto ps = GetPlayerState<ABasePlayerState>();
	if (IsValid(ps))
	{
		_AbilitySystemComp = ps->GetAbilitySystemComponent();

		if(IsValid(_AbilitySystemComp))
		{
			ps->GetAbilitySystemComponent()->InitAbilityActorInfo(ps, this);
		}
	}
}

void ABaseCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	// 클라에서 ASC 설정
	auto ps = GetPlayerState<ABasePlayerState>();
	if (IsValid(ps))
	{
		_AbilitySystemComp = ps->GetAbilitySystemComponent();

		if (IsValid(_AbilitySystemComp))
		{
			ps->GetAbilitySystemComponent()->InitAbilityActorInfo(ps, this);
		}
	}
}

void ABaseCharacter::Tick(float _delta)
{
	Super::Tick(_delta);

}

void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* _player_input_comp)
{
	Super::SetupPlayerInputComponent(_player_input_comp);

}

