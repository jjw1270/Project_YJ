// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/BasePlayerController.h"

void ABasePlayerController::BeginPlay()
{
	Super::BeginPlay();
	ConsoleCommand(TEXT("showdebug abilitysystem"));
}
