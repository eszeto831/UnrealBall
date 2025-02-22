// Fill out your copyright notice in the Description page of Project Settings.


#include "EdmondBlueprintFunctionLibrary.h"

FString UEdmondBlueprintFunctionLibrary::GetPointlessMessage()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("edmond :: game start pointless msg!!!"));
	return FString(TEXT("pointless hellow world 1"));
}

FString UEdmondBlueprintFunctionLibrary::GetPointlessMessage2()
{
	return FString(TEXT("pointless hellow world 2 22"));
}

FString UEdmondBlueprintFunctionLibrary::GetPointlessMessage3()
{
	return FString(TEXT("pointless hellow world 3"));
}