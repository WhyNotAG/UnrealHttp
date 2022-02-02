// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HttpService.h"
#include "GameFramework/GameModeBase.h"
#include "LoginGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class TESTNEWORK_API ALoginGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

private:
	UPROPERTY()
	AHttpService* HttpService;

	FString AccessToken;
	FString RefreshToken;
	
public:
	ALoginGameModeBase();

	AHttpService* GetService() const { return HttpService; }

	void SetAccessToken(FString newToken) { AccessToken = newToken; }
	void SetRefreshToken(FString newToken) { RefreshToken = newToken; }

	FString GetAccessToken() const { return AccessToken; }
	FString GetRefreshToken() const { return RefreshToken; }
};
