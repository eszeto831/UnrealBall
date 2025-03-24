// Copyright Epic Games, Inc. All Rights Reserved.

#include "MyProject2CppCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/DecalComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "Materials/Material.h"
#include "Engine/World.h"

AMyProject2CppCharacter::AMyProject2CppCharacter()
{
	// Set size for player capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	// Activate ticking in order to update the cursor every frame.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	useCrouchIdle = false;
	useDash = false;
	useLightAttack = false;
	useMediumAttack = false;
	useHardAttack = false;

	UE_LOG(LogTemp, Warning, TEXT("edmond :: creating char"));
}

void AMyProject2CppCharacter::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("edmond :: char normal tick!!!"));
}

void AMyProject2CppCharacter::CharacterTick(float delta)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("edmond :: char call tick!!!"));
}

void AMyProject2CppCharacter::CharacterMove(FVector worldDirection)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("edmond :: crouch"));
	AddMovementInput(worldDirection, 1.0, false);
}

void AMyProject2CppCharacter::CharacterJump()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("edmond :: crouch"));
	Jump();
}

void AMyProject2CppCharacter::CrouchIdle()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("edmond :: crouch"));
	useCrouchIdle = true;
}

void AMyProject2CppCharacter::Dash()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("edmond :: dash"));
	useDash = true;
}

void AMyProject2CppCharacter::AttackLight()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("edmond :: light attack"));
	useLightAttack = true;
}

void AMyProject2CppCharacter::AttackMedium()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("edmond :: med attack"));
	useMediumAttack = true;
}

void AMyProject2CppCharacter::AttackHard()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("edmond :: hard attack"));
	useHardAttack = true;
}
