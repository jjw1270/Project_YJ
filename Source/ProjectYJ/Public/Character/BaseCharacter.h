// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonLibrary.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "Input/InputDefines.h"
#include "BaseCharacter.generated.h"

class UInputAction;

UCLASS()
class PROJECTYJ_API ABaseCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere)
	TObjectPtr<class USpringArmComponent> _SpringArmComp = nullptr;

	UPROPERTY(EditAnywhere)
	TObjectPtr<class UCameraComponent> _CameraComp = nullptr;

protected:
	TWeakObjectPtr<class UAbilitySystemComponent> _AbilitySystemComp = nullptr;

protected:
	UPROPERTY(EditAnywhere, Category = GAS)
	TMap<EAbilityInputID, TSubclassOf<class UGameplayAbility>> _DefaultInputAbilityMap;

public:
	ABaseCharacter(const FObjectInitializer& _object_initializer);

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float _delta) override;

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const final;

};
