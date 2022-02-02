// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "HttpModule.h"
#include "GameFramework/Actor.h"
#include "JsonUtilities/Public/JsonObjectConverter.h"
#include "HttpService.generated.h"

USTRUCT()
struct FEnterDataRequest 
{

	GENERATED_BODY()
	
	UPROPERTY()
	FString username;

	UPROPERTY()
	FString password;
};

USTRUCT()
struct FLoginData
{
	GENERATED_BODY()
	
	UPROPERTY()
	FString accessToken;

	UPROPERTY()
	FString refreshToken;

	UPROPERTY()
	FString expiredIn;
};

USTRUCT()
struct FEnterResponse
{
	GENERATED_BODY()
	
	UPROPERTY()
	FLoginData LoginResult;
};

UCLASS()
class TESTNEWORK_API AHttpService : public AActor
{
	GENERATED_BODY()

protected:
	FHttpModule* Http;
	FString APIBaseURL;

public:	
	AHttpService();

protected:
	virtual void BeginPlay() override;

public:
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> RequestWithRoute(FString Subroute, FString AccessToken = "");
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> GetRequest(FString Subroute, FString AccessToken = "");
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> DeleteRequest(FString Subroute, FString AccessToken = "");
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> PostRequest(FString Subroute, FString ContentJsonString, FString AccessToken = "");
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> PutRequest(FString Subroute, FString ContentJsonString, FString AccessToken = "");

	void Send(TSharedRef<IHttpRequest, ESPMode::ThreadSafe>& Request);
	bool ResponseIsValid(FHttpResponsePtr Response, bool bWasSuccessful);
	
};
