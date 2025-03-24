// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Playable/PlayableCharacter.h"
#include "Player/BasePlayerState.h"
#include "AbilitySystemComponent.h"
#include "Input/ShrimpoInputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

APlayableCharacter::APlayableCharacter(const FObjectInitializer& _object_initializer)
	:Super(_object_initializer)
{
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	_SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
	if (IsValid(_SpringArmComp))
	{
		_SpringArmComp->SetupAttachment(RootComponent);
		_SpringArmComp->bUsePawnControlRotation = true;

		_CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
		if (IsValid(_CameraComp))
		{
			_CameraComp->SetupAttachment(_SpringArmComp, USpringArmComponent::SocketName);
			_CameraComp->bUsePawnControlRotation = false;
		}
	}

	auto movement_comp = GetCharacterMovement();
	if (IsValid(movement_comp))
	{
		movement_comp->bOrientRotationToMovement = true;
	}

	auto mesh_comp = GetMesh();
	if (IsValid(mesh_comp))
	{
		mesh_comp->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
	}

	OverrideInputComponentClass = UShrimpoInputComponent::StaticClass();
}

void APlayableCharacter::SetupPlayerInputComponent(UInputComponent* _player_input_comp)
{
	Super::SetupPlayerInputComponent(_player_input_comp);

	auto input_comp = Cast<UShrimpoInputComponent>(_player_input_comp);
	if (IsAllValid(input_comp, _InputActionData))
	{
		input_comp->BindNativeAction(_InputActionData, ENativeInputActionID::Move, ETriggerEvent::Triggered, this, &APlayableCharacter::Move);
		input_comp->BindNativeAction(_InputActionData, ENativeInputActionID::Look, ETriggerEvent::Triggered, this, &APlayableCharacter::Look);
		
		input_comp->BindAbilityAction(_InputActionData, EAbilityInputActionID::Jump, this, &APlayableCharacter::SendAbilityLocalInput);
	}
}

void APlayableCharacter::NotifyControllerChanged()
{
	Super::NotifyControllerChanged();

	// Add Input Mapping Context
	auto pc = Cast<APlayerController>(Controller);
	if (IsValid(pc))
	{
		if (auto enhanced_input_subsys = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(pc->GetLocalPlayer()))
		{
			if (IsValid(enhanced_input_subsys))
			{
				enhanced_input_subsys->AddMappingContext(_DefaultMappingContext, 0);
			}
		}
	}
}

void APlayableCharacter::PossessedBy(AController* _new_controller)
{
	Super::PossessedBy(_new_controller);

	// 서버에서 ASC 설정
	auto ps = GetPlayerState<ABasePlayerState>();
	if (IsValid(ps))
	{
		_AbilitySystemComp = ps->GetAbilitySystemComponent();

		if (IsValid(_AbilitySystemComp))
		{
			_AbilitySystemComp->InitAbilityActorInfo(ps, this);
		}
	}
}

void APlayableCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	// 클라에서 ASC 설정
	auto ps = GetPlayerState<ABasePlayerState>();
	if (IsValid(ps))
	{
		_AbilitySystemComp = ps->GetAbilitySystemComponent();

		if (IsValid(_AbilitySystemComp))
		{
			_AbilitySystemComp->InitAbilityActorInfo(ps, this);
		}
	}
}

void APlayableCharacter::SendAbilityLocalInput(bool _is_pressed, EAbilityInputActionID _ability_input_id)
{
	if (IsInvalid(_AbilitySystemComp))
		return;

	if (_is_pressed)
	{
		_AbilitySystemComp->AbilityLocalInputPressed((int32)_ability_input_id);
	}
	else
	{
		_AbilitySystemComp->AbilityLocalInputReleased((int32)_ability_input_id);
	}
}

void APlayableCharacter::Move(const FInputActionValue& _value)
{
	// input is a Vector2D
	FVector2D movement_vector = _value.Get<FVector2D>();

	if (IsValid(Controller))
	{
		const FRotator rotation(0, Controller->GetControlRotation().Yaw, 0);

		const FVector forward_direction = FRotationMatrix(rotation).GetUnitAxis(EAxis::X);
		const FVector right_direction = FRotationMatrix(rotation).GetUnitAxis(EAxis::Y);

		AddMovementInput(forward_direction, movement_vector.Y);
		AddMovementInput(right_direction, movement_vector.X);
	}
}

void APlayableCharacter::Look(const FInputActionValue& _value)
{
	FVector2D _look_axis_vector = _value.Get<FVector2D>();

	if (IsValid(Controller))
	{
		AddControllerYawInput(_look_axis_vector.X);
		AddControllerPitchInput(_look_axis_vector.Y);
	}
}
