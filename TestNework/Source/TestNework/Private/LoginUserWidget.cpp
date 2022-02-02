// Fill out your copyright notice in the Description page of Project Settings.


#include "LoginUserWidget.h"

#include "HttpService.h"
#include "LoginGameModeBase.h"
#include "Interfaces/IHttpResponse.h"

void ULoginUserWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if(LoginButton)
	{
		LoginButton->OnClicked.AddDynamic(this, &ULoginUserWidget::Login);
	}

	if(SendRequestButton)
	{
		SendRequestButton->OnClicked.AddDynamic(this, &ULoginUserWidget::SendRequest);
	}
	
}

void ULoginUserWidget::Login()
{    
	if (!GetWorld()) return;
	if (!GetWorld()->GetAuthGameMode()) return;
	
	const auto username = UsernameTextBox->GetText();
	const auto password = PasswordTextBox->GetText();

	FEnterDataRequest requestData;
	requestData.password = password.ToString();
	requestData.username = username.ToString();

	FString contentJsonString;
	FJsonObjectConverter::UStructToJsonObjectString(
		requestData.StaticStruct(), &requestData, contentJsonString, 0, 0);

	UE_LOG(LogTemp, Display, TEXT("%s"), *contentJsonString)
	const auto httpService = Cast<ALoginGameModeBase>(GetWorld()->GetAuthGameMode())->GetService();
	
	auto Request = httpService->PostRequest("/auth/login", contentJsonString);
	Request->OnProcessRequestComplete().BindUObject(this, &ULoginUserWidget::LoginResponse);
	httpService->Send(Request);
}

void ULoginUserWidget::SendRequest()
{
	if (!GetWorld()) return;
	if (!GetWorld()->GetAuthGameMode()) return;

	const auto gameMode = Cast<ALoginGameModeBase>(GetWorld()->GetAuthGameMode());
	const auto httpService = gameMode->GetService();

	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = httpService->RequestWithRoute("");
	
	if(RequestType.Equals("GET"))
	{
		Request = httpService->GetRequest(RequestTextBox->GetText().ToString(), gameMode->GetAccessToken());
	}
	if(RequestType.Equals("DELETE"))
	{
		Request = httpService->DeleteRequest(RequestTextBox->GetText().ToString(), gameMode->GetAccessToken());
	}
	if(RequestType.Equals("PUT"))
	{
		Request = httpService->PutRequest(RequestTextBox->GetText().ToString(), RequestBodyBox->GetText().ToString(), gameMode->GetAccessToken());
	}
	if(RequestType.Equals("POST"))
	{
		Request = httpService->PostRequest(RequestTextBox->GetText().ToString(), RequestBodyBox->GetText().ToString(), gameMode->GetAccessToken());
	}

	Request->OnProcessRequestComplete().BindUObject(this, &ULoginUserWidget::TestResponse);
	httpService->Send(Request);
}

void ULoginUserWidget::LoginResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
	const auto httpService = Cast<ALoginGameModeBase>(GetWorld()->GetAuthGameMode())->GetService();
	if(!httpService->ResponseIsValid(Response, bWasSuccessful))
	{
		AccessTextBlock->SetText(FText::FromString(TEXT("Error")));
		return;
	};

	FLoginData EnterResponse;
	FString JsonString = Response->GetContentAsString();
	FJsonObjectConverter::JsonObjectStringToUStruct<FLoginData>(JsonString, &EnterResponse, 0, 0);

	const auto gameMode = Cast<ALoginGameModeBase>(GetWorld()->GetAuthGameMode());

	gameMode->SetAccessToken(EnterResponse.accessToken);
	gameMode->SetRefreshToken(EnterResponse.refreshToken);
	
	UE_LOG(LogTemp, Display, TEXT("%s"), *EnterResponse.accessToken)
	AccessTextBlock->SetText(FText::FromString(EnterResponse.accessToken));
}

void ULoginUserWidget::TestResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
	UE_LOG(LogTemp, Display, TEXT("%s"), *Response->GetContentAsString());
}
