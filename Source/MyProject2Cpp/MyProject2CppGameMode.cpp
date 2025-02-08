// Copyright Epic Games, Inc. All Rights Reserved.

#include "MyProject2CppGameMode.h"
#include "MyProject2CppPlayerController.h"
#include "MyProject2CppCharacter.h"
#include "UObject/ConstructorHelpers.h"

AMyProject2CppGameMode::AMyProject2CppGameMode()
{
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
}