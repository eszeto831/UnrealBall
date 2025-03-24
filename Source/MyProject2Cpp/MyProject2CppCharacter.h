// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyProject2CppCharacter.generated.h"

UCLASS(Blueprintable)
class AMyProject2CppCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AMyProject2CppCharacter();

	// Called every frame.
	virtual void Tick(float DeltaSeconds) override;

	/** Returns TopDownCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	UFUNCTION(BlueprintCallable, Category = "Game Logic")
	void CharacterTick(float delta);

	UFUNCTION(BlueprintCallable, Category = "Attack Logic")
	void CharacterMove(FVector worldDirection);

	UFUNCTION(BlueprintCallable, Category = "Attack Logic")
	void CharacterJump();

	UFUNCTION(BlueprintCallable, Category = "Attack Logic")
	void CrouchIdle();

	UFUNCTION(BlueprintCallable, Category = "Attack Logic")
	void Dash();

	UFUNCTION(BlueprintCallable, Category = "Attack Logic")
	void AttackLight();

	UFUNCTION(BlueprintCallable, Category = "Attack Logic")
	void AttackMedium();

	UFUNCTION(BlueprintCallable, Category = "Attack Logic")
	void AttackHard();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attacks")
	bool useCrouchIdle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attacks")
	bool useDash;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attacks")
	bool useLightAttack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attacks")
	bool useMediumAttack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attacks")
	bool useHardAttack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	bool playerHealth;

private:
	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* TopDownCameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;
};

