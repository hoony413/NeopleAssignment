// Fill out your copyright notice in the Description page of Project Settings.

#include "SplitProjectile.h"
#include "Engine/Classes/Components/ArrowComponent.h"
#include "NormalProjectile.h"

ASplitProjectile::ASplitProjectile()
{
	Velocity = 100.f;
	Lifetime = 3.f;
	ArrowScale = 1.f;

	AddSplitArrowComponent();
}
void ASplitProjectile::AddSplitArrowComponent()
{
	// ���� ȭ��ǥ ����
	LeftArrowComponent = CreateDefaultSubobject<UArrowComponent>(TEXT("LeftArrowComponent"));
	LeftArrowComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	LeftArrowComponent->bUseInEditorScaling = false;
	LeftArrowComponent->SetVisibility(true);
	LeftArrowComponent->SetHiddenInGame(false);
	LeftArrowComponent->SetRelativeLocation(FVector::ZeroVector);

	// ������ ȭ��ǥ ����
	RightArrowComponent = CreateDefaultSubobject<UArrowComponent>(TEXT("RightArrowComponent"));
	RightArrowComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	RightArrowComponent->bUseInEditorScaling = false;
	RightArrowComponent->SetVisibility(true);
	RightArrowComponent->SetHiddenInGame(false);
	RightArrowComponent->SetRelativeLocation(FVector::ZeroVector);

	Arrows.Add(LeftArrowComponent);
	Arrows.Add(ArrowComponent);
	Arrows.Add(RightArrowComponent);
}
void ASplitProjectile::SetVelocity(FVector& InDir)
{	
	Super::SetVelocity(InDir);
	// ���� ����������κ��� -45��, 45�� ���� ���
	FRotator rot = InDir.Rotation();
	// ���� ȭ��ǥ ����
	rot.SetComponentForAxis(EAxis::Z, -45.f);
	LeftArrowComponent->SetRelativeRotation(rot);
	// ������ ȭ��ǥ ����
	rot.SetComponentForAxis(EAxis::Z, 45.f);
	RightArrowComponent->SetRelativeRotation(rot);
}
void ASplitProjectile::LifeSpanExpired()
{
	FActorSpawnParameters spawnParam;
	spawnParam.Owner = this->GetOwner();

	// �� ȭ��ǥ �������� ��� źü�� ���� �� �ڱ� �ڽ� �Ҹ�.
	for (int32 i = 0; i < Arrows.Num(); ++i)
	{
		ANormalProjectile* proj = GetWorld()->SpawnActor<ANormalProjectile>(
			ANormalProjectile::StaticClass(),
			GetActorLocation(), FRotator::ZeroRotator, spawnParam);
		proj->SetActorScale3D(FVector(0.5f));
		FVector forwardNormal = Arrows[i]->GetForwardVector();
		proj->SetVelocity(forwardNormal);
	}

	Super::LifeSpanExpired();
}