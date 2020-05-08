// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseProjectile.h"
#include "Engine/Classes/GameFramework/ProjectileMovementComponent.h"
#include "Engine/Classes/Components/StaticMeshComponent.h"
#include "Engine/Classes/Components/ArrowComponent.h"
#include "Engine/Classes/Components/SphereComponent.h"

// Sets default values
ABaseProjectile::ABaseProjectile()
:Velocity(100.f), ArrowCount(1), Lifetime(3.f), ArrowScale(1.f)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 구체 콜리전 설정
	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	CollisionComponent->InitSphereRadius(60.0f);
	CollisionComponent->BodyInstance.SetCollisionProfileName(TEXT("Projectile"));
	
	CollisionComponent->SetCollisionObjectType(ECollisionChannel::ECC_GameTraceChannel1);
	CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	CollisionComponent->SetCollisionProfileName(TEXT("Projectile"));
	
	CollisionComponent->OnComponentHit.AddDynamic(this, &ABaseProjectile::OnHit);
	RootComponent = CollisionComponent;
	
	// 메쉬&머터리얼 설정
	SphereMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SphereMeshComp"));
	SphereMesh->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	ConstructorHelpers::FObjectFinder<UStaticMesh> mesh(TEXT("StaticMesh'/Game/Meshes/Sphere.Sphere'"));
	SphereMesh->SetStaticMesh(mesh.Object);
	ConstructorHelpers::FObjectFinder<UMaterialInterface> mat(TEXT("Material'/Game/Materials/BasicShapeMaterial.BasicShapeMaterial'"));
	SphereMesh->SetMaterial(0, mat.Object);
	SphereMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	SphereMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);

	// 탄체 무브먼트 설정
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	ProjectileMovementComponent->SetUpdatedComponent(RootComponent);
	ProjectileMovementComponent->ProjectileGravityScale = 0.f;
	ProjectileMovementComponent->Velocity = FVector::ZeroVector;

	// 화살표 설정
	ArrowComponent = CreateDefaultSubobject<UArrowComponent>(TEXT("ArrowComponent"));
	ArrowComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	ArrowComponent->bUseInEditorScaling = false;
	ArrowComponent->SetVisibility(true);
	ArrowComponent->SetHiddenInGame(false);
	ArrowComponent->SetRelativeLocation(FVector::ZeroVector);
}

// Called when the game starts or when spawned
void ABaseProjectile::BeginPlay()
{
	// 변수 설정
	ProjectileMovementComponent->InitialSpeed = Velocity;
	InitialLifeSpan = Lifetime;
	ArrowComponent->ArrowSize = ArrowScale;
	ArrowComponent->MarkRenderStateDirty();
	Super::BeginPlay();
}

void ABaseProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor)
	{
		Destroy();
	}
}
void ABaseProjectile::SetVelocity(FVector& InDir)
{
	FRotator rot = InDir.Rotation();
	// 탄체가 진행방향을 바라보게(ArrowComponent 정렬)
	SetActorRelativeRotation(rot);
	// 진행방향 벡터에 속도 스칼라 곱
	ProjectileMovementComponent->Velocity = InDir * ProjectileMovementComponent->InitialSpeed;
}

// Called every frame
void ABaseProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

