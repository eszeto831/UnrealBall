// Fill out your copyright notice in the Description page of Project Settings.

#include "GameHUD.h"
#include "Components/TextBlock.h"

void UGameHUD::SetTime(int i)
{
	if (TimerText)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("hud tick %i"), i));
		FText TextToSet = FText::FromString(FString::FromInt(i));
		TimerText->SetText(TextToSet);
	}
}
