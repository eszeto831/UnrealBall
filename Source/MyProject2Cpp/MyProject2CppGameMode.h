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
	virtual void PostLogin(APlayerController*) override;

	virtual void Tick(float DeltaTime) override;

	//virtual AActor* SpawnDefaultPawnFor(AController* NewPlayer, FTransform const& SpawnTransform) override;
	//virtual APawn* SpawnDefaultPawnFor(AController* NewPlayer, AActor* StartSpot) override;

	void CreateHUDWidget();
	void LoadPlayers();

	int GetMaxPlayerCount();

	UFUNCTION(BlueprintCallable, Category = "Game Logic")
	void GameModeTick(float delta, UGameHUD* hud);

	float TimeLeft;
	TSubclassOf<APawn> SelectedPawnClass;
	TSubclassOf<UUserWidget> GameHUDClass;
	UGameHUD* GameHUDWidgetInst;
	/*
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game Settings")
	int TestInt;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UGameHUD> GameHUDClass;

	UPROPERTY()
	class UGameHUD* GameHUDInst;
	*/
};



