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

		// Setup crouch events
		EnhancedInputComponent->BindAction(SetCrouchAction, ETriggerEvent::Started, this, &AMyProject2CppPlayerController::OnInputStarted);
		EnhancedInputComponent->BindAction(SetCrouchAction, ETriggerEvent::Triggered, this, &AMyProject2CppPlayerController::OnCrouchTriggered);
		EnhancedInputComponent->BindAction(SetCrouchAction, ETriggerEvent::Completed, this, &AMyProject2CppPlayerController::OnCrouchReleased);
		EnhancedInputComponent->BindAction(SetCrouchAction, ETriggerEvent::Canceled, this, &AMyProject2CppPlayerController::OnCrouchReleased);

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

		// Setup light attack events
		EnhancedInputComponent->BindAction(SetLightAttackAction, ETriggerEvent::Started, this, &AMyProject2CppPlayerController::OnInputStarted);
		EnhancedInputComponent->BindAction(SetLightAttackAction, ETriggerEvent::Triggered, this, &AMyProject2CppPlayerController::OnLightAttackTriggered);
		EnhancedInputComponent->BindAction(SetLightAttackAction, ETriggerEvent::Completed, this, &AMyProject2CppPlayerController::OnLightAttackReleased);
		EnhancedInputComponent->BindAction(SetLightAttackAction, ETriggerEvent::Canceled, this, &AMyProject2CppPlayerController::OnLightAttackReleased);

		// Setup medium attack events
		EnhancedInputComponent->BindAction(SetMediumAttackAction, ETriggerEvent::Started, this, &AMyProject2CppPlayerController::OnInputStarted);
		EnhancedInputComponent->BindAction(SetMediumAttackAction, ETriggerEvent::Triggered, this, &AMyProject2CppPlayerController::OnMediumAttackTriggered);
		EnhancedInputComponent->BindAction(SetMediumAttackAction, ETriggerEvent::Completed, this, &AMyProject2CppPlayerController::OnMediumAttackReleased);
		EnhancedInputComponent->BindAction(SetMediumAttackAction, ETriggerEvent::Canceled, this, &AMyProject2CppPlayerController::OnMediumAttackReleased);

		// Setup hard attack events
		EnhancedInputComponent->BindAction(SetHardAttackAction, ETriggerEvent::Started, this, &AMyProject2CppPlayerController::OnInputStarted);
		EnhancedInputComponent->BindAction(SetHardAttackAction, ETriggerEvent::Triggered, this, &AMyProject2CppPlayerController::OnHardAttackTriggered);
		EnhancedInputComponent->BindAction(SetHardAttackAction, ETriggerEvent::Completed, this, &AMyProject2CppPlayerController::OnHardAttackReleased);
		EnhancedInputComponent->BindAction(SetHardAttackAction, ETriggerEvent::Canceled, this, &AMyProject2CppPlayerController::OnHardAttackReleased);

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
	ACharacter* ControlledCharacter = GetCharacter();
	AMyProject2CppCharacter* FighterCharacter = Cast<AMyProject2CppCharacter>(ControlledCharacter);
	float InputValue = 0;
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("edmond :: stop!!! pad %f"), InputValue));
	//OnSetDestinationTriggered();

	PlayerPawnMove(FighterCharacter, InputValue);
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
	ACharacter* ControlledCharacter = GetCharacter();
	AMyProject2CppCharacter* FighterCharacter = Cast<AMyProject2CppCharacter>(ControlledCharacter);
	float InputValue = Value.Get<float>();
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("edmond :: move pad!!! %f"), InputValue));
	//OnSetDestinationTriggered();

	PlayerPawnMove(FighterCharacter, InputValue);
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

void AMyProject2CppPlayerController::PlayerPawnMove(AMyProject2CppCharacter* FighterCharacter, float InputValue)
{
	if (FighterCharacter != nullptr)
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
		FighterCharacter->CharacterMove(WorldDirection);

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
void AMyProject2CppPlayerController::OnCrouchTriggered()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("edmond :: crouch!!!"));
	ACharacter* ControlledCharacter = GetCharacter();
	AMyProject2CppCharacter* FighterCharacter = Cast<AMyProject2CppCharacter>(ControlledCharacter);
	FighterCharacter->CrouchIdle();
}

void AMyProject2CppPlayerController::OnCrouchReleased()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("edmond :: crouch RELEASE!"));
	//OnSetDestinationReleased();
}

void AMyProject2CppPlayerController::OnDashTriggered()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("edmond :: dash!!!"));
	ACharacter* ControlledCharacter = GetCharacter();
	AMyProject2CppCharacter* FighterCharacter = Cast<AMyProject2CppCharacter>(ControlledCharacter);
	FighterCharacter->Dash();
}

void AMyProject2CppPlayerController::OnDashReleased()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("edmond :: dash RELEASE!"));
	//OnSetDestinationReleased();
}

void AMyProject2CppPlayerController::OnJumpTriggered()
{
	ACharacter* ControlledCharacter = GetCharacter();
	AMyProject2CppCharacter* FighterCharacter = Cast<AMyProject2CppCharacter>(ControlledCharacter);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("edmond :: jump pad!!! %f"), 1));
	//OnSetDestinationTriggered();

	PlayerPawnJump(FighterCharacter);
}

void AMyProject2CppPlayerController::PlayerPawnJump(AMyProject2CppCharacter* FighterCharacter)
{
	if (FighterCharacter != nullptr)
	{
		FighterCharacter->CharacterJump();
	}
}

void AMyProject2CppPlayerController::OnJumpReleased()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("edmond :: jump RELEASE!"));
	OnSetDestinationReleased();
}

void AMyProject2CppPlayerController::OnLightAttackTriggered()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("edmond :: light attack!!!"));
	ACharacter* ControlledCharacter = GetCharacter();
	AMyProject2CppCharacter* FighterCharacter = Cast<AMyProject2CppCharacter>(ControlledCharacter);
	FighterCharacter->AttackLight();
}

void AMyProject2CppPlayerController::OnLightAttackReleased()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("edmond :: light attack RELEASE!"));
	//OnSetDestinationReleased();
}

void AMyProject2CppPlayerController::OnMediumAttackTriggered()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("edmond :: Medium attack!!!"));
	ACharacter* ControlledCharacter = GetCharacter();
	AMyProject2CppCharacter* FighterCharacter = Cast<AMyProject2CppCharacter>(ControlledCharacter);
	FighterCharacter->AttackMedium();
}

void AMyProject2CppPlayerController::OnMediumAttackReleased()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("edmond :: Medium attack RELEASE!"));
	//OnSetDestinationReleased();
}

void AMyProject2CppPlayerController::OnHardAttackTriggered()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("edmond :: Hard attack!!!"));
	ACharacter* ControlledCharacter = GetCharacter();
	AMyProject2CppCharacter* FighterCharacter = Cast<AMyProject2CppCharacter>(ControlledCharacter);
	FighterCharacter->AttackHard();
}

void AMyProject2CppPlayerController::OnHardAttackReleased()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("edmond :: Hard attack RELEASE!"));
	//OnSetDestinationReleased();
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
