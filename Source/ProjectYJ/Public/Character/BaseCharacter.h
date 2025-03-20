// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"

UCLASS()
class PROJECTYJ_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere)
	TObjectPtr<class USpringArmComponent> _SpringArmComp = nullptr;

	UPROPERTY(EditAnywhere)
	TObjectPtr<class UCameraComponent> _CameraComp = nullptr;

	UPROPERTY()
	TObjectPtr<class UAbilitySystemComponent> _AbilitySystemComp = nullptr;

public:
	ABaseCharacter(const FObjectInitializer& _object_initializer = FObjectInitializer::Get());

protected:
	virtual void BeginPlay() override;

public:	
	virtual void PossessedBy(AController* _new_controller) override;
	virtual void OnRep_PlayerState() override;

	virtual void Tick(float _delta) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* _player_input_comp) override;

};
