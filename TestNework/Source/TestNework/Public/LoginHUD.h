// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "LoginHUD.generated.h"

/**
 * 
 */
UCLASS()
class TESTNEWORK_API ALoginHUD : public AHUD
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> LoginWidgetClass;


protected:
		virtual void BeginPlay() override;
};
