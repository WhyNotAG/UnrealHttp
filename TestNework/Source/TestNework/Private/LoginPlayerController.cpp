// Fill out your copyright notice in the Description page of Project Settings.


#include "LoginPlayerController.h"

void ALoginPlayerController::BeginPlay()
{
	Super::BeginPlay();

	SetInputMode(FInputModeUIOnly());
	bShowMouseCursor = true;
}
