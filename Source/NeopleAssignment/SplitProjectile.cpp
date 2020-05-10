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
	// 왼쪽 화살표 설정
	LeftArrowComponent = CreateDefaultSubobject<UArrowComponent>(TEXT("LeftArrowComponent"));
	LeftArrowComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	LeftArrowComponent->bUseInEditorScaling = false;
	LeftArrowComponent->SetVisibility(true);
	LeftArrowComponent->SetHiddenInGame(false);
	LeftArrowComponent->SetRelativeLocation(FVector::ZeroVector);

	// 오른쪽 화살표 설정
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
	// 직진 진행방향으로부터 -45도, 45도 방향 계산
	FRotator rot = InDir.Rotation();
	// 왼쪽 화살표 갱신
	rot.SetComponentForAxis(EAxis::Z, -45.f);
	LeftArrowComponent->SetRelativeRotation(rot);
	// 오른쪽 화살표 갱신
	rot.SetComponentForAxis(EAxis::Z, 45.f);
	RightArrowComponent->SetRelativeRotation(rot);
}
void ASplitProjectile::LifeSpanExpired()
{
	FActorSpawnParameters spawnParam;
	spawnParam.Owner = this->GetOwner();

	// 각 화살표 방향으로 노멀 탄체를 날린 후 자기 자신 소멸.
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