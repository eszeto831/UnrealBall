// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MyProject2CppGameMode.generated.h"

UCLASS(minimalapi)
class AMyProject2CppGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AMyProject2CppGameMode();
	/*
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game Settings")
	int TestInt;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UGameHUD> GameHUDClass;

	UPROPERTY()
	class UGameHUD* GameHUDInst;
	*/
};



