// Copyright Epic Games, Inc. All Rights Reserved.

#include "MyProject2CppGameMode.h"
#include "MyProject2CppPlayerController.h"
#include "MyProject2CppCharacter.h"
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

//Gets all the actors for me of my choosing and puts them into an array
template<typename T>
void FindAllActors(UWorld* World, TArray<T*>& Out)
{
	for (TActorIterator<T> It(World); It; ++It)
	{
		Out.Add(*It);
	}
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
		/*
		TArray<APlayerStart*> playerStart;
		FindAllActors(currentWorld, playerStart);
		int a = 1;
		for (auto obj : playerStart)
		{
			UE_LOG(LogTemp, Warning, TEXT("game mode load player for loop: %d"), a);

			FString error;
			ULocalPlayer* newPlayer = gameInstance->CreateLocalPlayer(a, error, true);
			
			if (newPlayer)
			{
				FVector spawnLocation = obj->GetActorLocation(); // Assuming 'this' is a Player Start actor
				FRotator spawnRotation = obj->GetActorRotation();
				
				APlayerController* newController = newPlayer->GetPlayerController(currentWorld);
				//APlayerController* newController = UGameplayStatics::CreatePlayer(GetWorld(), newPlayer->GetControllerId(), true, false);
				if (newController)
				{
					APawn* newPawn = GetWorld()->SpawnActor<APawn>(DefaultPawnClass, spawnLocation, spawnRotation);
					newController->Possess(newPawn);
				}
				
			}
			
			a++;
		}
		*/
		//FindPlayerStart()

		
		//TArray<AActor*> FoundActors;
		//UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerStart::StaticClass(), FoundActors);
		for (int32 a = 1; a <= GetMaxPlayerCount(); a++)
		{
			UE_LOG(LogTemp, Warning, TEXT("game mode load player for loop: %d"), a);

			FString error;
			ULocalPlayer* newPlayer = gameInstance->CreateLocalPlayer(a, error, true);
			
			//APlayerStart* newPLayerStart = FoundActors[a - 1];

			if (newPlayer)
			{
				//FVector spawnLocation = newPLayerStart->GetActorLocation(); // Assuming 'this' is a Player Start actor
				//FRotator spawnRotation = newPLayerStart->GetActorRotation();
				APlayerController* newController = newPlayer->GetPlayerController(currentWorld);
				//APlayerController* newController = UGameplayStatics::CreatePlayer(GetWorld(), newPlayer->GetControllerId(), true, false);
				if (newController)
				{
					FString IntAsString = FString::FromInt(a);
					AActor* newPLayerStart = FindPlayerStart(newController, IntAsString);
					if (newPLayerStart)
					{
						FVector spawnLocation = newPLayerStart->GetActorLocation(); // Assuming 'this' is a Player Start actor
						FRotator spawnRotation = newPLayerStart->GetActorRotation();
						APawn* newPawn = newController->GetPawn();
						if (newPawn)
						{
							newPawn->SetActorLocation(spawnLocation, false, nullptr, ETeleportType::None);
							newPawn->SetActorRotation(spawnRotation, ETeleportType::None);
						}
					}
					//APawn* newPawn = GetWorld()->SpawnActor<APawn>(DefaultPawnClass, spawnLocation, spawnRotation);
					//newController->Possess(newPawn);
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
	//UE_LOG(LogTemp, Warning, TEXT("game mode tick: %f"), DeltaTime);
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("game mode tick %f -> %f"), DeltaTime, 0));
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