// Copyright Epic Games, Inc. All Rights Reserved.

#include "NeopleAssignmentCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "BaseProjectile.h"
#include "NormalProjectile.h"
#include "ChargedProjectile.h"
#include "SplitProjectile.h"
#include "Engine/Classes/GameFramework/ProjectileMovementComponent.h"

ANeopleAssignmentCharacter::ANeopleAssignmentCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate when the controller rotates.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Create a camera boom attached to the root (capsule)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true); // Rotation of the character should not affect rotation of boom
	CameraBoom->bDoCollisionTest = false;
	CameraBoom->TargetArmLength = 500.f;
	CameraBoom->SocketOffset = FVector(0.f,0.f,75.f);
	CameraBoom->SetRelativeRotation(FRotator(0.f,180.f,0.f));

	// Create a camera and attach to boom
	SideViewCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("SideViewCamera"));
	SideViewCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	SideViewCameraComponent->bUsePawnControlRotation = false; // We don't want the controller rotating the camera

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Face in the direction we are moving..
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->GravityScale = 2.f;
	GetCharacterMovement()->AirControl = 0.80f;
	GetCharacterMovement()->JumpZVelocity = 1000.f;
	GetCharacterMovement()->GroundFriction = 3.f;
	GetCharacterMovement()->MaxWalkSpeed = 600.f;
	GetCharacterMovement()->MaxFlySpeed = 600.f;

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)
}

//////////////////////////////////////////////////////////////////////////
// Input

void ANeopleAssignmentCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// set up gameplay key bindings
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &ANeopleAssignmentCharacter::PressedFire);
	PlayerInputComponent->BindAction("Fire", IE_Released, this, &ANeopleAssignmentCharacter::ReleasedFire);

	PlayerInputComponent->BindAction("ChargeFire", IE_Pressed, this, &ANeopleAssignmentCharacter::PressedChargeToggle);

	PlayerInputComponent->BindAxis("MoveRight", this, &ANeopleAssignmentCharacter::MoveRight);

	PlayerInputComponent->BindTouch(IE_Pressed, this, &ANeopleAssignmentCharacter::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &ANeopleAssignmentCharacter::TouchStopped);
}

void ANeopleAssignmentCharacter::MoveRight(float Value)
{
	// add movement in that direction
	AddMovementInput(FVector(0.f,-1.f,0.f), Value);
}

void ANeopleAssignmentCharacter::TouchStarted(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	// jump on any touch
	Jump();
}

void ANeopleAssignmentCharacter::TouchStopped(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	StopJumping();
}

void ANeopleAssignmentCharacter::PressedFire()
{	// Q�� ���� ����
	fPressedFireTimeStamp = GetWorld()->GetRealTimeSeconds();
}
void ANeopleAssignmentCharacter::ReleasedFire()
{
	fReleasedFireTimeStamp = GetWorld()->GetRealTimeSeconds();
}
void ANeopleAssignmentCharacter::PressedChargeToggle()
{
	fPressedSplitTimeStamp = GetWorld()->GetRealTimeSeconds();
}
template<typename T>
void ANeopleAssignmentCharacter::FireProjectile()
{	
	UClass* uc = T::StaticClass();
	if (uc->IsChildOf(ABaseProjectile::StaticClass()) == false)
		return;

	CalculateFirePosition();
	
	FActorSpawnParameters spawnParam;
	spawnParam.Owner = this;

	T* t = GetWorld()->SpawnActor<T>(uc, FirePosition, FRotator::ZeroRotator, spawnParam);
	t->SetActorScale3D(FVector(0.5f));
	FVector forwardNormal = GetActorForwardVector();
	t->SetVelocity(forwardNormal);
	
	// Ÿ�ӽ����� �� �ʱ�ȭ.
	InitializeTimeStamp();
}
void ANeopleAssignmentCharacter::CalculateFirePosition()
{
	// �߻����� ���
	FVector startPos = GetCharacterMovement()->GetActorFeetLocation();
	startPos.Z += 50.f;

	// źü ������ġ: ������ ĳ���� �� ��ġ(50) + ĳ���� ���⺤�� * ��Į�� ��(20) 
	FirePosition = startPos + (GetActorForwardVector() * 20);
}
FVector& ANeopleAssignmentCharacter::GetFirePosition()
{
	CalculateFirePosition();
	return FirePosition;
}
void ANeopleAssignmentCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	if (fPressedFireTimeStamp <= 0.f)
		return;

	fDebugHoldTime += DeltaSeconds;
	GEngine->RemoveOnScreenDebugMessage(iMessageCounter);
	
	iMessageCounter--;
	GEngine->AddOnScreenDebugMessage(iMessageCounter, 10, FColor::Red, FString::Printf(TEXT("Q Hold Time: %f"), fDebugHoldTime));

	if (fPressedSplitTimeStamp > 0.f)
	{	// W ��ư�� ������?
		if (fReleasedFireTimeStamp - fPressedSplitTimeStamp <= 1.f)
		{	// Q�� ��� 1�� �̳��� W�� �����°�? �п� �߻�ü �߻�.
			FireProjectile<ASplitProjectile>();
			return;
		}
	}
	
	if (fReleasedFireTimeStamp - fPressedFireTimeStamp >= 3.f)
	{	// Q�� 3�� �̻� ������? ���� �߻�ü �߻�.
		FireProjectile<AChargedProjectile>();
	}
	else if(fReleasedFireTimeStamp - fPressedFireTimeStamp >= 0.f)
	{	// �Ϲ� �߻�ü �߻�(������ �� �� �߻�Ǿ�� ��).
		FireProjectile<ANormalProjectile>();
	}
}
void ANeopleAssignmentCharacter::InitializeTimeStamp()
{	// ��ϵ� �ð��� �ʱ�ȭ.
	fPressedFireTimeStamp = fReleasedFireTimeStamp = fPressedSplitTimeStamp = fDebugHoldTime = 0.f;
	iMessageCounter = -1;
	GEngine->ClearOnScreenDebugMessages();
}