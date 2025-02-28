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
	
	UE_LOG(LogTemp, Warning, TEXT("Hello World!"));
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("edmond :: spawn actor 2!!!"));

	//FActorSpawnParameters SpawnInfo;
	//FRotator myRot(0, 0, 0);
	//FVector myLoc(1000.0, 1810.0, 92.012604);
	//AMyProject2CppCharacter* mySphere = GetWorld()->SpawnActor<AMyProject2CppCharacter>(AMyProject2CppCharacter::StaticClass(), myLoc, myRot, SpawnInfo);
	
	//LoadPlayers();
}

void AMyProject2CppGameMode::BeginPlay()
{
	Super::BeginPlay();

	LoadPlayers();
}

void AMyProject2CppGameMode::LoadPlayers()
{
	UE_LOG(LogTemp, Warning, TEXT("game mode max players: %d"), GetMaxPlayerCount());
	
	if (GetMaxPlayerCount())
	{
		UE_LOG(LogTemp, Warning, TEXT("in if"));
		UWorld* currentWorld = GetWorld();

		UGameInstance* gameInstance = currentWorld->GetGameInstance();
		UGameViewportClient* gameViewport = currentWorld->GetGameViewport();

		// Remove split screen because I want a 2D game
		gameViewport->SetForceDisableSplitscreen(true);

		for (int32 a = 1; a <= GetMaxPlayerCount(); a++)
		{
			UE_LOG(LogTemp, Warning, TEXT("game mode load player for loop: %d"), a);

			FString error;
			ULocalPlayer* localPlayer = gameInstance->CreateLocalPlayer(a, error, true);
		}
		
	}
	
}

int AMyProject2CppGameMode::GetMaxPlayerCount()
{
	return 4;
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