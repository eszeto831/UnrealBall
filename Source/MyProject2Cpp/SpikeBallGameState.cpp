// Fill out your copyright notice in the Description page of Project Settings.


#include "SpikeBallGameState.h"

ASpikeBallGameState::ASpikeBallGameState()
{
	/*
	static ConstructorHelpers::FClassFinder<UUserWidget> GameHUDWidgetClass(TEXT("/Game/TopDown/UI/GameHUD"));
	if (GameHUDWidgetClass.Class != NULL)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("edmond :: set HUD class!!!"));
		GameHUDClass = GameHUDWidgetClass.Class;
	}
	*/
	TimeLeft = 99;
}

void ASpikeBallGameState::BeginPlay()
{
	Super::BeginPlay();

	CreateHUDWidget();
}

void ASpikeBallGameState::CreateHUDWidget()
{
	/*
	UE_LOG(LogTemp, Warning, TEXT("edmond :: hud name: %s"), *GameHUDClass->GetName());
	//NEED GAME INSTANCE
	UUserWidget* NewWidgetInst = CreateWidget<UUserWidget>(GetWorld(), GameHUDClass);
	GameHUDWidgetInst = Cast<UGameHUD>(NewWidgetInst);
	GameHUDWidgetInst->AddToViewport();
	UE_LOG(LogTemp, Warning, TEXT("edmond :: hud inst name: %s"), *GameHUDWidgetInst->GetName());
	*/
}

void ASpikeBallGameState::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (GameHUDWidgetInst != nullptr)
	{
		TimeLeft -= DeltaTime;
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("game mode tick %f -> %f"), delta, TimeLeft));
		GameHUDWidgetInst->SetTime(TimeLeft);
	}
	//UE_LOG(LogTemp, Warning, TEXT("game mode tick: %f"), DeltaTime);
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("game mode tick %f -> %f"), DeltaTime, 0));
}

