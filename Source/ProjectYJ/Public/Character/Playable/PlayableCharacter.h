// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/BaseCharacter.h"
#include "PlayableCharacter.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTYJ_API APlayableCharacter : public ABaseCharacter
{
	GENERATED_BODY()
	
// Input
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	TObjectPtr<class UInputMappingContext> _DefaultMappingContext = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	TObjectPtr<UInputAction> _MoveAction = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	TObjectPtr<UInputAction> _LookAction = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	TObjectPtr<UInputAction> _JumpAction = nullptr;

public:
	APlayableCharacter(const FObjectInitializer& _object_initializer);

	virtual void SetupPlayerInputComponent(class UInputComponent* _player_input_comp) override;
	virtual void NotifyControllerChanged() override;
	virtual void PossessedBy(AController* _new_controller) override;
	virtual void OnRep_PlayerState() override;

protected:
	void SendAbilityLocalInput(bool _is_pressed, EAbilityInputID _input_type);

	void Move(const FInputActionValue& _value);
	void Look(const FInputActionValue& _value);
};
