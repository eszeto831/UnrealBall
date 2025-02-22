// Fill out your copyright notice in the Description page of Project Settings.

#include "GameHUD.h"
#include "Components/TextBlock.h"

void UGameHUD::SetTime(int i)
{
	if (TimerText)
	{
		FString MyString = FString::Printf(TEXT("edmond :: game mode tick %d"), i);
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("%s"));
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT(*MyString));
		//UE_LOG(LogTemp, Warning, TEXT("hello world"));
		//UE_LOG(LogTemp, Warning, TEXT("%s"), *MyString);
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("hud tick %i"), i));
		FText TextToSet = FText::FromString(FString::FromInt(i)); //FText::FromString(NewText);
		TimerText->SetText(TextToSet);
	}
}
