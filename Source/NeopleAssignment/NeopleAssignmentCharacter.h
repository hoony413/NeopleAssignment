// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "NeopleAssignmentCharacter.generated.h"

enum class EProjectileType : uint8;

UCLASS(config=Game)
class ANeopleAssignmentCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Side view camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* SideViewCameraComponent;

	/** Camera boom positioning the camera beside the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

protected:

	/** Called for side to side input */
	void MoveRight(float Val);

	void PressedFire();
	void ReleasedFire();

	void PressedChargeToggle();

	void CalculateFirePosition();

	/** Handle touch inputs. */
	void TouchStarted(const ETouchIndex::Type FingerIndex, const FVector Location);

	/** Handle touch stop event. */
	void TouchStopped(const ETouchIndex::Type FingerIndex, const FVector Location);

	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
	// End of APawn interface

protected:
	UPROPERTY()
		float fPressedFireTimeStamp = 0.f;
	UPROPERTY()
		float fReleasedFireTimeStamp = 0.f;
	UPROPERTY()
		float fPressedChargeTimeStamp = 0.f;

#if WITH_EDITOR
	UPROPERTY()
		float fDebugHoldTime = 0.f;
	UPROPERTY()
		int32 iMessageCounter = -1;
#endif

	UPROPERTY()
		FVector FirePosition;

	void InitializeTimeStamp();

public:
	ANeopleAssignmentCharacter();

	/** Returns SideViewCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetSideViewCameraComponent() const { return SideViewCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	FVector& GetFirePosition();
	void FireProjectile(EProjectileType InType);

	virtual void Tick(float DeltaSeconds) override;
};
