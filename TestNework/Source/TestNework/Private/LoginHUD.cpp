// Fill out your copyright notice in the Description page of Project Settings.


#include "LoginHUD.h"

#include "Blueprint/UserWidget.h"

void ALoginHUD::BeginPlay()
{
	Super::BeginPlay();

	if(LoginWidgetClass)
	{
		const auto LoginWidget = CreateWidget<UUserWidget> (GetWorld(), LoginWidgetClass);
		if(LoginWidget)
		{
			LoginWidget->AddToViewport();
		}
	}
	
}
