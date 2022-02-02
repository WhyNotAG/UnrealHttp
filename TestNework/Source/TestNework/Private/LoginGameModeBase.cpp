// Fill out your copyright notice in the Description page of Project Settings.


#include "LoginGameModeBase.h"

#include "LoginHUD.h"
#include "LoginPlayerController.h"

ALoginGameModeBase::ALoginGameModeBase()
{
	PlayerControllerClass = ALoginPlayerController::StaticClass();
	HUDClass = ALoginHUD::StaticClass();
	HttpService = CreateDefaultSubobject<AHttpService>("HttpService");
}
