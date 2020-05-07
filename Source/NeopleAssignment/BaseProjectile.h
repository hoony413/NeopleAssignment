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

UCLASS()
class NEOPLEASSIGNMENT_API ABaseProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseProjectile();

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
	c. 1-c �� ����
	d. 1-d �� ����
	e. 5�� �� �ڵ� �Ҹ��մϴ�.
	f. 1-f �� ����
	*/
	// ESplitProj.
	/*
	a. Q Ű�� ������ ���� 1�� �̳��� WŰ�� ������ �� �߻�˴ϴ�.
	b. 1-b �� ������ ���¿���, X���� �� ������ 45��( Degree ) Ʋ���� ȭ��ǥ�� 2�� �߰��մϴ�.
	c. 1-c �� ����
	d. 1-d �� ����
	e. 3�� ��, 1�� �߻�ü�� �ڽ� ������ ȭ��ǥ ������ ���� ���� �߻��մϴ�.
	( 3���� 1�� �߻�ü�� ���� ����, �� �� 45���� �߻� )
	( �ڱ� �ڽ��� �Ҹ��մϴ�. )
	f. 1-f �� ����
	*/

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	virtual EProjectileType GetProjectileType() { return EProjectileType::ENormalProj; }

	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
