// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseProjectile.generated.h"

UENUM()
enum class EProjectileType : uint8
{
	ENormalProj,
	EChargeProj,
	ESplitProj,
};
// ENormalProj.
/*
a. Q 키를 눌렀다 떼면 발사됩니다.
b. 발사체의 외형은 전방 ( X축, 언리얼 기본 값 )을 가리키는 화살표( Arrow Component )를 포함한 액터( Actor )로 만듭니다.
c. 생성은 캐릭터가 바라보는 방향으로 20 유닛( unit, 언리얼 기본 값 ), 캐릭터 발 밑에서 50 유닛 떨어진 위치에 만듭니다.
d. 생성 후, 캐릭터가 바라보는 방향으로 직선 운동 합니다. ( 속도는 100 유닛 / 초 )
e. 3초 후 자동 소멸됩니다.
f. 캐릭터를 블록 ( Block )하는 모든 종류의 오브젝트와 임의 충돌 시 즉시 소멸합니다.
*/
// EChargeProj.
/*
a. Q 키를 3초 이상 누렀다 떼면 발사됩니다. ( 1번 발사체는 발사되지 않습니다. )
b. 1-b 와 동일하되, 화살표의 크기만 3배 확장합니다.
c. 생성은 캐릭터가 바라보는 방향으로 20 유닛( unit, 언리얼 기본 값 ), 캐릭터 발 밑에서 50 유닛 떨어진 위치에 만듭니다.
d. 생성 후, 캐릭터가 바라보는 방향으로 직선 운동 합니다. ( 속도는 100 유닛 / 초 )
e. 5초 후 자동 소멸합니다.
f. 캐릭터를 블록 ( Block )하는 모든 종류의 오브젝트와 임의 충돌 시 즉시 소멸합니다.
*/
// ESplitProj.
/*
a. Q 키를 눌렀다 떼기 1초 이내에 W키를 눌렀을 때 발사됩니다.
b. 1-b 와 동일한 상태에서, X축의 양 옆으로 45도( Degree ) 틀어진 화살표를 2개 추가합니다.
c. 생성은 캐릭터가 바라보는 방향으로 20 유닛( unit, 언리얼 기본 값 ), 캐릭터 발 밑에서 50 유닛 떨어진 위치에 만듭니다.
d. 생성 후, 캐릭터가 바라보는 방향으로 직선 운동 합니다. ( 속도는 100 유닛 / 초 )
e. 3초 후, 1번 발사체를 자신 내부의 화살표 방향들로 각각 생성 발사합니다.
( 3개의 1번 발사체를 진행 방향, 양 옆 45도로 발사 )
( 자기 자신은 소멸합니다. )
f. 1-f 와 동일
*/

class USphereComponent;
class UArrowComponent;
class UStaticMeshComponent;
class UProjectileMovementComponent;

UCLASS()
class NEOPLEASSIGNMENT_API ABaseProjectile : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABaseProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

protected:
	// 탄체 속도(s)
	UPROPERTY()
		float Velocity;
	// 탄체 각도(발사 모체가 바라보는 방향이 기준이 됨)
	UPROPERTY()
		float Degree;
	// 탄체 지속시간
	UPROPERTY()
		float Lifetime;
	// 탄체에 달린 ArrowComponent 스케일.
	UPROPERTY()
		float ArrowScale;

	UPROPERTY(VisibleDefaultsOnly, Category = Projectile)
		USphereComponent* CollisionComponent;
	UPROPERTY(VisibleDefaultsOnly, Category = Projectile)
		UArrowComponent* ArrowComponent;
	UPROPERTY(VisibleDefaultsOnly, Category = Projectile)
		UStaticMeshComponent* SphereMesh;

	UPROPERTY(VisibleAnywhere, Category = Movement)
		UProjectileMovementComponent* ProjectileMovementComponent;

public:
	void SetVelocity(FVector& InDir);
	UProjectileMovementComponent* GetProjectileMoveComponent() { return ProjectileMovementComponent; }
	virtual EProjectileType GetProjectileType() { return EProjectileType::ENormalProj; }

	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
