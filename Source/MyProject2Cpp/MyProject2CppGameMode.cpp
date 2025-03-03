// Copyright Epic Games, Inc. All Rights Reserved.

#include "MyProject2CppGameMode.h"
#include "MyProject2CppPlayerController.h"
#include "MyProject2CppCharacter.h"
#include "SpikeBallGameState.h"
#include "UObject/ConstructorHelpers.h"
#include "UI/GameHUD.h"
#include "Blueprint/UserWidget.h"
#include "GameFramework/HUD.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerStart.h"
#include "EngineUtils.h"

AMyProject2CppGameMode::AMyProject2CppGameMode()
{
	PrimaryActorTick.bStartWithTickEnabled = true;
	PrimaryActorTick.bCanEverTick = true;

	GameStateClass = ASpikeBallGameState::StaticClass();

	// use our custom PlayerController class
	PlayerControllerClass = AMyProject2CppPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDown/Blueprints/BP_TopDownCharacter"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
	// set default controller to our Blueprinted controller
	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerBPClass(TEXT("/Game/TopDown/Blueprints/BP_TopDownPlayerController"));
	if(PlayerControllerBPClass.Class != NULL)
	{
		PlayerControllerClass = PlayerControllerBPClass.Class;
	}

	// set default controller to our Blueprinted controller
	static ConstructorHelpers::FClassFinder<AHUD> GameHUDBPClass(TEXT("/Game/TopDown/Blueprints/BP_GameHUD"));
	if (GameHUDBPClass.Class != NULL)
	{
		HUDClass = GameHUDBPClass.Class;
	}
	
	static ConstructorHelpers::FClassFinder<UUserWidget> GameHUDWidgetClass(TEXT("/Game/TopDown/UI/GameHUD"));
	if (GameHUDWidgetClass.Class != NULL)
	{
		GameHUDClass = GameHUDWidgetClass.Class;
	}
	TimeLeft = 99;
	
	UE_LOG(LogTemp, Warning, TEXT("Hello World! 2"));
}

void AMyProject2CppGameMode::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("edmond :: begin play"));

	CreateHUDWidget();

	LoadPlayers();
}

void AMyProject2CppGameMode::CreateHUDWidget()
{
	UE_LOG(LogTemp, Warning, TEXT("edmond :: hud name: %s"), *GameHUDClass->GetName());
	//NEED GAME INSTANCE
	UUserWidget* NewWidgetInst = CreateWidget<UUserWidget>(GetWorld(), GameHUDClass);
	GameHUDWidgetInst = Cast<UGameHUD>(NewWidgetInst);
	GameHUDWidgetInst->AddToViewport();
	UE_LOG(LogTemp, Warning, TEXT("edmond :: hud inst name: %s"), *GameHUDWidgetInst->GetName());
}

//Gets all the actors for me of my choosing and puts them into an array
template<typename T>
void FindAllActors(UWorld* World, TArray<T*>& Out)
{
	for (TActorIterator<T> It(World); It; ++It)
	{
		Out.Add(*It);
	}
}

void AMyProject2CppGameMode::PostLogin(APlayerController* NewPlayerController)
{
	Super::PostLogin(NewPlayerController);
}

void AMyProject2CppGameMode::LoadPlayers()
{
	UE_LOG(LogTemp, Warning, TEXT("edmond :: game mode max players: %d"), GetMaxPlayerCount());

	if (GetMaxPlayerCount())
	{
		UE_LOG(LogTemp, Warning, TEXT("in if"));
		UWorld* currentWorld = GetWorld();

		UGameInstance* gameInstance = currentWorld->GetGameInstance();
		UGameViewportClient* gameViewport = currentWorld->GetGameViewport();

		// Remove split screen because I want a 2D game
		gameViewport->SetForceDisableSplitscreen(true);

		// Load players
		for (int32 a = 0; a < GetMaxPlayerCount(); a++)
		{
			UE_LOG(LogTemp, Warning, TEXT("edmond :: game mode load player for loop: %d"), a);

			FString error;
			ULocalPlayer* newPlayer = gameInstance->CreateLocalPlayer(a, error, true);

			if (!newPlayer)
			{
				UE_LOG(LogTemp, Warning, TEXT("edmond :: already have player: %d"), a);
				newPlayer = gameInstance->GetLocalPlayerByIndex(a);
			}

			if (newPlayer)
			{
				UE_LOG(LogTemp, Warning, TEXT("edmond :: got player: %d"), a);
				APlayerController* newController = newPlayer->GetPlayerController(currentWorld);
				if (newController)
				{
					UE_LOG(LogTemp, Warning, TEXT("edmond :: got controller: %d"), a);
					FString IntAsString = FString::FromInt(a + 1);
					AActor* newPLayerStart = FindPlayerStart(newController, IntAsString);
					if (newPLayerStart)
					{
						UE_LOG(LogTemp, Warning, TEXT("edmond :: got player start: %d"), a);
						FVector spawnLocation = newPLayerStart->GetActorLocation(); // Assuming 'this' is a Player Start actor
						FRotator spawnRotation = newPLayerStart->GetActorRotation();
						APawn* newPawn = newController->GetPawn();
						if (newPawn)
						{
							UE_LOG(LogTemp, Warning, TEXT("edmond :: got pawn: %d"), a);
							newPawn->SetActorLocation(spawnLocation, false, nullptr, ETeleportType::None);
							newPawn->SetActorRotation(spawnRotation, ETeleportType::None);
						}
					}
				}
			}
		}
	}
	
}

int AMyProject2CppGameMode::GetMaxPlayerCount()
{
	return 4;
}


void AMyProject2CppGameMode::Tick(float DeltaTime)
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

void AMyProject2CppGameMode::GameModeTick(float delta, UGameHUD* hud)
{
	/*
	if (hud != nullptr)
	{
		TimeLeft -= delta;
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("game mode tick %f -> %f"), delta, TimeLeft));
		hud->SetTime(TimeLeft);
	}
	*/
}