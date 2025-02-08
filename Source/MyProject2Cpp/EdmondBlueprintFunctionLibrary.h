// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "EdmondBlueprintFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT2CPP_API UEdmondBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	static FString GetPointlessMessage();

	UFUNCTION(BlueprintCallable)
	static FString GetPointlessMessage2();

	UFUNCTION(BlueprintCallable)
	static FString GetPointlessMessage3();

};
