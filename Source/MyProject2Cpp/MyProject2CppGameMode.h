// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "UI/GameHUD.h"
#include "MyProject2CppGameMode.generated.h"

UCLASS(minimalapi)
class AMyProject2CppGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AMyProject2CppGameMode();

	virtual void BeginPlay() override;

	void LoadPlayers();

	int GetMaxPlayerCount();

	UFUNCTION(BlueprintCallable, Category = "Game Logic")
	void GameModeTick(float delta, UGameHUD* hud);

	float TimeLeft;
	/*
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game Settings")
	int TestInt;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UGameHUD> GameHUDClass;

	UPROPERTY()
	class UGameHUD* GameHUDInst;
	*/
};



