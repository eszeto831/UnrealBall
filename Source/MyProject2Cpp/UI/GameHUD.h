// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameHUD.generated.h"

UCLASS(Abstract)
class MYPROJECT2CPP_API UGameHUD : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetTime(int i);

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* TimerText;
	
};