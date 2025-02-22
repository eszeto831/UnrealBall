// Copyright Epic Games, Inc. All Rights Reserved.

#include "MyProject2CppGameMode.h"
#include "MyProject2CppPlayerController.h"
#include "MyProject2CppCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "UI/GameHUD.h"
#include "Blueprint/UserWidget.h"
#include "GameFramework/HUD.h"

AMyProject2CppGameMode::AMyProject2CppGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = AMyProject2CppPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDown/Blueprints/BP_TopDownCharacter"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("edmond :: set player pawn class!!!"));
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	// set default controller to our Blueprinted controller
	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerBPClass(TEXT("/Game/TopDown/Blueprints/BP_TopDownPlayerController"));
	if(PlayerControllerBPClass.Class != NULL)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("edmond :: set player comntroller class!!!"));
		PlayerControllerClass = PlayerControllerBPClass.Class;
	}

	// set default controller to our Blueprinted controller
	static ConstructorHelpers::FClassFinder<AHUD> GameHUDBPClass(TEXT("/Game/TopDown/Blueprints/BP_GameHUD"));
	if (GameHUDBPClass.Class != NULL)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("edmond :: set HUD class!!!"));
		HUDClass = GameHUDBPClass.Class;
	}
	//static ConstructorHelpers::FClassFinder<APlayerController> GameHUDBPClass(TEXT("/Game/TopDown/Blueprints/BP_GameHUD"));
	//HUDClass = BP_GameHUD::StaticClass();

	//GameHUDClass = nullptr;
	//GameHUDInst = nullptr;
	TimeLeft = 99;
}

void AMyProject2CppGameMode::GameModeTick(float delta, UGameHUD* hud)
{
	if (hud != nullptr)
	{
		TimeLeft -= delta;
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("game mode tick %f -> %f"), delta, TimeLeft));
		hud->SetTime(TimeLeft);
	}
}