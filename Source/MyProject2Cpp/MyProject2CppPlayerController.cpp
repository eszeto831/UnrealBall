// Copyright Epic Games, Inc. All Rights Reserved.

#include "MyProject2CppPlayerController.h"
#include "GameFramework/Pawn.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "MyProject2CppCharacter.h"
#include "Engine/World.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"
#include "Kismet/GameplayStatics.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

AMyProject2CppPlayerController::AMyProject2CppPlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
	CachedDestination = FVector::ZeroVector;
	FollowTime = 0.f;
}

void AMyProject2CppPlayerController::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();
}

void AMyProject2CppPlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("edmond :: set up inputs!!!"));

	// Add Input Mapping Context
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}

	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		/*
		// Setup mouse input events
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Started, this, &AMyProject2CppPlayerController::OnInputStarted);
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Triggered, this, &AMyProject2CppPlayerController::OnSetDestinationTriggered);
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Completed, this, &AMyProject2CppPlayerController::OnSetDestinationReleased);
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Canceled, this, &AMyProject2CppPlayerController::OnSetDestinationReleased);

		// Setup touch input events
		EnhancedInputComponent->BindAction(SetDestinationTouchAction, ETriggerEvent::Started, this, &AMyProject2CppPlayerController::OnInputStarted);
		EnhancedInputComponent->BindAction(SetDestinationTouchAction, ETriggerEvent::Triggered, this, &AMyProject2CppPlayerController::OnTouchTriggered);
		EnhancedInputComponent->BindAction(SetDestinationTouchAction, ETriggerEvent::Completed, this, &AMyProject2CppPlayerController::OnTouchReleased);
		EnhancedInputComponent->BindAction(SetDestinationTouchAction, ETriggerEvent::Canceled, this, &AMyProject2CppPlayerController::OnTouchReleased);
		*/

		// Setup movement events
		EnhancedInputComponent->BindAction(SetMoveAction, ETriggerEvent::Started, this, &AMyProject2CppPlayerController::OnInputStarted);
		EnhancedInputComponent->BindAction(SetMoveAction, ETriggerEvent::Triggered, this, &AMyProject2CppPlayerController::OnMovementTriggered);
		EnhancedInputComponent->BindAction(SetMoveAction, ETriggerEvent::Completed, this, &AMyProject2CppPlayerController::OnMovementReleased);
		EnhancedInputComponent->BindAction(SetMoveAction, ETriggerEvent::Canceled, this, &AMyProject2CppPlayerController::OnMovementReleased);

		// Setup dash events
		EnhancedInputComponent->BindAction(SetDashAction, ETriggerEvent::Started, this, &AMyProject2CppPlayerController::OnInputStarted);
		EnhancedInputComponent->BindAction(SetDashAction, ETriggerEvent::Triggered, this, &AMyProject2CppPlayerController::OnDashTriggered);
		EnhancedInputComponent->BindAction(SetDashAction, ETriggerEvent::Completed, this, &AMyProject2CppPlayerController::OnDashReleased);
		EnhancedInputComponent->BindAction(SetDashAction, ETriggerEvent::Canceled, this, &AMyProject2CppPlayerController::OnDashReleased);

		// Setup jump events
		EnhancedInputComponent->BindAction(SetJumpAction, ETriggerEvent::Started, this, &AMyProject2CppPlayerController::OnInputStarted);
		EnhancedInputComponent->BindAction(SetJumpAction, ETriggerEvent::Triggered, this, &AMyProject2CppPlayerController::OnJumpTriggered);
		EnhancedInputComponent->BindAction(SetJumpAction, ETriggerEvent::Completed, this, &AMyProject2CppPlayerController::OnJumpReleased);
		EnhancedInputComponent->BindAction(SetJumpAction, ETriggerEvent::Canceled, this, &AMyProject2CppPlayerController::OnJumpReleased);

		/*
		// Setup movement events
		EnhancedInputComponent->BindAction(SetMoveActionPlayer1, ETriggerEvent::Started, this, &AMyProject2CppPlayerController::OnInputStartedPlayer1);
		EnhancedInputComponent->BindAction(SetMoveActionPlayer1, ETriggerEvent::Triggered, this, &AMyProject2CppPlayerController::OnMovementTriggeredPlayer1);
		EnhancedInputComponent->BindAction(SetMoveActionPlayer1, ETriggerEvent::Completed, this, &AMyProject2CppPlayerController::OnMovementReleasedPlayer1);
		EnhancedInputComponent->BindAction(SetMoveActionPlayer1, ETriggerEvent::Canceled, this, &AMyProject2CppPlayerController::OnMovementReleasedPlayer1);
		*/

		// Setup options UI events
		EnhancedInputComponent->BindAction(SetOptionsUIAction, ETriggerEvent::Started, this, &AMyProject2CppPlayerController::OnOptionsUIStarted);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void AMyProject2CppPlayerController::OnInputStarted()
{
	//StopMovement();
	APawn* ControlledPawn = GetPawn();
	float InputValue = 0;
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("edmond :: stop!!! pad %f"), InputValue));
	//OnSetDestinationTriggered();

	PlayerPawnMove(ControlledPawn, InputValue);
}
/*
void AMyProject2CppPlayerController::OnInputStartedPlayer1()
{
	//StopMovement();
	APlayerController* Controller = UGameplayStatics::GetPlayerController(GetWorld(), 1);
	APawn* ControlledPawn = Controller->GetPawn();
	float InputValue = 0;
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("edmond :: stop!!! player2 %f"), InputValue));
	//OnSetDestinationTriggered();

	MovePlayerPawn(ControlledPawn, InputValue);
}
*/

// Triggered every frame when the input is held down
void AMyProject2CppPlayerController::OnSetDestinationTriggered()
{
	return;
	/*
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("edmond :: NO!!! %f"), 0));



	// We flag that the input is being pressed
	FollowTime += GetWorld()->GetDeltaSeconds();
	
	// We look for the location in the world where the player has pressed the input
	FHitResult Hit;
	bool bHitSuccessful = false;
	if (bIsTouch)
	{
		bHitSuccessful = GetHitResultUnderFinger(ETouchIndex::Touch1, ECollisionChannel::ECC_Visibility, true, Hit);
	}
	else
	{
		bHitSuccessful = GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, Hit);
	}

	// If we hit a surface, cache the location
	if (bHitSuccessful)
	{
		CachedDestination = Hit.Location;
	}
	
	// Move towards mouse pointer or touch
	APawn* ControlledPawn = GetPawn();
	if (ControlledPawn != nullptr)
	{
		FVector WorldDirection = (CachedDestination - ControlledPawn->GetActorLocation()).GetSafeNormal();
		ControlledPawn->AddMovementInput(WorldDirection, 1.0, false);
	}
	*/
}

void AMyProject2CppPlayerController::OnSetDestinationReleased()
{
	return;
	/*
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("edmond :: NO!!! %f"), 0));



	// If it was a short press
	if (FollowTime <= ShortPressThreshold)
	{
		// We move there and spawn some particles
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, CachedDestination);
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, FXCursor, CachedDestination, FRotator::ZeroRotator, FVector(1.f, 1.f, 1.f), true, true, ENCPoolMethod::None, true);
	}

	FollowTime = 0.f;
	*/
}

// Triggered every frame when the input is held down
void AMyProject2CppPlayerController::OnTouchTriggered()
{
	bIsTouch = true;
	OnSetDestinationTriggered();
}

void AMyProject2CppPlayerController::OnTouchReleased()
{
	bIsTouch = false;
	OnSetDestinationReleased();
}

void AMyProject2CppPlayerController::OnMovementTriggered(const FInputActionValue& Value)
{
	APawn* ControlledPawn = GetPawn();
	float InputValue = Value.Get<float>();
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("edmond :: move pad!!! %f"), InputValue));
	//OnSetDestinationTriggered();

	PlayerPawnMove(ControlledPawn, InputValue);
}
/*
void AMyProject2CppPlayerController::OnMovementTriggeredPlayer1(const FInputActionValue& Value)
{
	APlayerController* Controller = UGameplayStatics::GetPlayerController(GetWorld(), 1);
	APawn* ControlledPawn = Controller->GetPawn();
	float InputValue = Value.Get<float>();
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("edmond :: move player 2!!! %f"), InputValue));
	//OnSetDestinationTriggered();

	MovePlayerPawn(ControlledPawn, InputValue);
}
*/

void AMyProject2CppPlayerController::PlayerPawnMove(APawn* ControlledPawn, float InputValue)
{
	if (ControlledPawn != nullptr)
	{
		//FVector WorldDirection = FVector(InputValue, ControlledPawn->GetActorLocation().Y, 0);
		FVector WorldDirection = FVector(0, 0, 0);
		if (InputValue > 0)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("edmond :: neg 1!!! %f"), 1));
			WorldDirection = FVector(0, 1, 0);
		}
		else if(InputValue < 0)
		{
			WorldDirection = FVector(0, -1, 0);
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("edmond :: 1!!! %f"), 1));
		}
		ControlledPawn->AddMovementInput(WorldDirection, 1.0, false);

	}

	//UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, CachedDestination);
}

void AMyProject2CppPlayerController::OnMovementReleased(const FInputActionValue& Value)
{
	float InputValue = Value.Get<float>();
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("edmond :: move RELEASE!!! %f"), InputValue));
	OnSetDestinationReleased();
}
/*
void AMyProject2CppPlayerController::OnMovementReleasedPlayer1(const FInputActionValue& Value)
{
	float InputValue = Value.Get<float>();
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("edmond :: move RELEASE!!! %f"), InputValue));
	OnSetDestinationReleased();
}
*/
void AMyProject2CppPlayerController::OnDashTriggered()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("edmond :: dash!!!"));
	OnSetDestinationTriggered();
}

void AMyProject2CppPlayerController::OnDashReleased()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("edmond :: dash RELEASE!"));
	OnSetDestinationReleased();
}

void AMyProject2CppPlayerController::OnJumpTriggered()
{
	ACharacter* ControlledCharacter = GetCharacter();
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("edmond :: jump pad!!! %f"), 1));
	//OnSetDestinationTriggered();

	PlayerPawnJump(ControlledCharacter);
}

void AMyProject2CppPlayerController::PlayerPawnJump(ACharacter* ControlledCharacter)
{
	if (ControlledCharacter != nullptr)
	{
		ControlledCharacter->Jump();
	}
}

void AMyProject2CppPlayerController::OnJumpReleased()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("edmond :: jump RELEASE!"));
	OnSetDestinationReleased();
}

void AMyProject2CppPlayerController::OnOptionsUIStarted()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("edmond :: open options!"));
	OnSetDestinationReleased();
}

void AMyProject2CppPlayerController::OnOpenOptionsUI()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("edmond :: open options FUNC!"));
}
