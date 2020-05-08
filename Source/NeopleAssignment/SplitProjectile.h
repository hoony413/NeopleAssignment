// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseProjectile.h"
#include "SplitProjectile.generated.h"

/**
 * 
 */
UCLASS()
class NEOPLEASSIGNMENT_API ASplitProjectile : public ABaseProjectile
{
	GENERATED_BODY()
	
public:
	ASplitProjectile();

	virtual void SetVelocity(FVector& InDir) override;
	virtual void LifeSpanExpired() override;

protected:
	void AddSplitArrowComponent();

protected:
	UPROPERTY(VisibleAnywhere, Category = Projectile)
		UArrowComponent* LeftArrowComponent;
	UPROPERTY(VisibleAnywhere, Category = Projectile)
		UArrowComponent* RightArrowComponent;

	UPROPERTY()
		TArray<UArrowComponent*> Arrows;
};
