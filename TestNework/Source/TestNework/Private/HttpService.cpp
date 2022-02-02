// Fill out your copyright notice in the Description page of Project Settings.


#include "TestNework/Public/HttpService.h"
#include "Blueprint/UserWidget.h"
#include "Interfaces/IHttpResponse.h"

AHttpService::AHttpService()
{
	PrimaryActorTick.bCanEverTick = false;
	APIBaseURL = TEXT("http://localhost:8443/api/v1");
}

void AHttpService::BeginPlay()
{
	Super::BeginPlay();
}

TSharedRef<IHttpRequest, ESPMode::ThreadSafe> AHttpService::RequestWithRoute(FString Subroute, FString AccessToken)
{
	Http = &FHttpModule::Get();
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = Http->CreateRequest();
	Request->SetURL(APIBaseURL + Subroute);
	Request->SetHeader(TEXT("User-Agent"), TEXT("X-UnrealEngine-Agent"));
	Request->SetHeader(TEXT("Content-Type"), TEXT("application/json"));
	Request->SetHeader(TEXT("Accepts"), TEXT("application/json"));

	if(!AccessToken.Equals(""))
	{
		Request->SetHeader(TEXT("Authorization"), "Bearer_" + AccessToken);
	}
	return Request;
}

TSharedRef<IHttpRequest, ESPMode::ThreadSafe> AHttpService::GetRequest(FString Subroute, FString AccessToken)
{
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = RequestWithRoute(Subroute, AccessToken);
	Request->SetVerb("GET");
	return Request;
}

TSharedRef<IHttpRequest, ESPMode::ThreadSafe> AHttpService::DeleteRequest(FString Subroute, FString AccessToken)
{
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = RequestWithRoute(Subroute, AccessToken);
	Request->SetVerb("DELETE");
	return Request;
}

TSharedRef<IHttpRequest, ESPMode::ThreadSafe> AHttpService::PostRequest(FString Subroute, FString ContentJsonString, FString AccessToken)
{
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = RequestWithRoute(Subroute, AccessToken);
	Request->SetVerb("POST");
	Request->SetContentAsString(ContentJsonString);
	return Request;
}

TSharedRef<IHttpRequest, ESPMode::ThreadSafe> AHttpService::PutRequest(FString Subroute, FString ContentJsonString, FString AccessToken)
{
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = RequestWithRoute(Subroute, AccessToken);
	Request->SetVerb("PUT");
	Request->SetContentAsString(ContentJsonString);
	return Request;
}

void AHttpService::Send(TSharedRef<IHttpRequest, ESPMode::ThreadSafe>& Request)
{
	Request->ProcessRequest();
}

bool AHttpService::ResponseIsValid(FHttpResponsePtr Response, bool bWasSuccessful)
{
	if(!bWasSuccessful || !Response.IsValid())
	{
		return false;
	}

	if(EHttpResponseCodes::IsOk(Response->GetResponseCode()))
	{
		return true;
	}
	
	UE_LOG(LogTemp, Warning, TEXT("Http response returned error code: %d"), Response->GetResponseCode())
	return false;
}


