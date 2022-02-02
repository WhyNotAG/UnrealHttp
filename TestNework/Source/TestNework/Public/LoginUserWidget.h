// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/ComboBox.h"
#include "Components/ComboBoxString.h"
#include "Components/EditableTextBox.h"
#include "Components/MultiLineEditableTextBox.h"
#include "Components/TextBlock.h"
#include "Interfaces/IHttpRequest.h"
#include "LoginUserWidget.generated.h"


UCLASS()
class TESTNEWORK_API ULoginUserWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta = (BindWidget))
	UButton* LoginButton;

	UPROPERTY(meta = (BindWidget))
	UEditableTextBox* UsernameTextBox;

	UPROPERTY(meta = (BindWidget))
	UEditableTextBox* PasswordTextBox;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* AccessTextBlock;

	UPROPERTY(meta = (BindWidget))
	UEditableTextBox* RequestTextBox;

	UPROPERTY(meta = (BindWidget))
	UComboBoxString* RequestComboBox;

	UPROPERTY(meta = (BindWidget))
	UMultiLineEditableTextBox* RequestBodyBox;
	
	UPROPERTY(meta = (BindWidget))
	UButton* SendRequestButton;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	FString RequestType;
	
protected:
	virtual void NativeOnInitialized() override;
	
private:
	UFUNCTION()
	void Login();

	UFUNCTION()
	void SendRequest();
	
	void LoginResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);

	void TestResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);
};
