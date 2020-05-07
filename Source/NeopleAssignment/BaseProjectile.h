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
a. Q Ű�� ������ ���� �߻�˴ϴ�.
b. �߻�ü�� ������ ���� ( X��, �𸮾� �⺻ �� )�� ����Ű�� ȭ��ǥ( Arrow Component )�� ������ ����( Actor )�� ����ϴ�.
c. ������ ĳ���Ͱ� �ٶ󺸴� �������� 20 ����( unit, �𸮾� �⺻ �� ), ĳ���� �� �ؿ��� 50 ���� ������ ��ġ�� ����ϴ�.
d. ���� ��, ĳ���Ͱ� �ٶ󺸴� �������� ���� � �մϴ�. ( �ӵ��� 100 ���� / �� )
e. 3�� �� �ڵ� �Ҹ�˴ϴ�.
f. ĳ���͸� ��� ( Block )�ϴ� ��� ������ ������Ʈ�� ���� �浹 �� ��� �Ҹ��մϴ�.
*/
// EChargeProj.
/*
a. Q Ű�� 3�� �̻� ������ ���� �߻�˴ϴ�. ( 1�� �߻�ü�� �߻���� �ʽ��ϴ�. )
b. 1-b �� �����ϵ�, ȭ��ǥ�� ũ�⸸ 3�� Ȯ���մϴ�.
c. ������ ĳ���Ͱ� �ٶ󺸴� �������� 20 ����( unit, �𸮾� �⺻ �� ), ĳ���� �� �ؿ��� 50 ���� ������ ��ġ�� ����ϴ�.
d. ���� ��, ĳ���Ͱ� �ٶ󺸴� �������� ���� � �մϴ�. ( �ӵ��� 100 ���� / �� )
e. 5�� �� �ڵ� �Ҹ��մϴ�.
f. ĳ���͸� ��� ( Block )�ϴ� ��� ������ ������Ʈ�� ���� �浹 �� ��� �Ҹ��մϴ�.
*/
// ESplitProj.
/*
a. Q Ű�� ������ ���� 1�� �̳��� WŰ�� ������ �� �߻�˴ϴ�.
b. 1-b �� ������ ���¿���, X���� �� ������ 45��( Degree ) Ʋ���� ȭ��ǥ�� 2�� �߰��մϴ�.
c. ������ ĳ���Ͱ� �ٶ󺸴� �������� 20 ����( unit, �𸮾� �⺻ �� ), ĳ���� �� �ؿ��� 50 ���� ������ ��ġ�� ����ϴ�.
d. ���� ��, ĳ���Ͱ� �ٶ󺸴� �������� ���� � �մϴ�. ( �ӵ��� 100 ���� / �� )
e. 3�� ��, 1�� �߻�ü�� �ڽ� ������ ȭ��ǥ ������ ���� ���� �߻��մϴ�.
( 3���� 1�� �߻�ü�� ���� ����, �� �� 45���� �߻� )
( �ڱ� �ڽ��� �Ҹ��մϴ�. )
f. 1-f �� ����
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
	// źü �ӵ�(s)
	UPROPERTY()
		float Velocity;
	// źü ����(�߻� ��ü�� �ٶ󺸴� ������ ������ ��)
	UPROPERTY()
		float Degree;
	// źü ���ӽð�
	UPROPERTY()
		float Lifetime;
	// źü�� �޸� ArrowComponent ������.
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
