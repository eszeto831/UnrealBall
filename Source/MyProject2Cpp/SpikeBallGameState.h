// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "UI/GameHUD.h"
#include "SpikeBallGameState.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT2CPP_API ASpikeBallGameState : public AGameStateBase
{
	GENERATED_BODY()

public:
	ASpikeBallGameState();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	void CreateHUDWidget();

	float TimeLeft;
	TSubclassOf<UUserWidget> GameHUDClass;
	UGameHUD* GameHUDWidgetInst;
};
