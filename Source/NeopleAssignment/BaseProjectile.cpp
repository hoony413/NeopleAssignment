// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseProjectile.h"
#include "Engine/Classes/GameFramework/ProjectileMovementComponent.h"
#include "Engine/Classes/Components/StaticMeshComponent.h"
#include "Engine/Classes/Components/ArrowComponent.h"
#include "Engine/Classes/Components/SphereComponent.h"

// Sets default values
ABaseProjectile::ABaseProjectile()
:Velocity(100.f), Degree(0.f), Lifetime(3.f), ArrowScale(1.f)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	CollisionComponent->InitSphereRadius(60.0f);
	CollisionComponent->BodyInstance.SetCollisionProfileName(TEXT("Projectile"));
	
	CollisionComponent->SetCollisionObjectType(ECollisionChannel::ECC_GameTraceChannel1);
	CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	CollisionComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldStatic, ECollisionResponse::ECR_Block);
	
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
	ProjectileMovementComponent->InitialSpeed = Velocity;
	ProjectileMovementComponent->Velocity = FVector::ZeroVector;

	// 화살표 설정
	ArrowComponent = CreateDefaultSubobject<UArrowComponent>(TEXT("ArrowComponent"));
	ArrowComponent->ScreenSize = 1.f;
	ArrowComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	ArrowComponent->bUseInEditorScaling = false;
	ArrowComponent->SetVisibility(true);
	ArrowComponent->SetHiddenInGame(false);
	ArrowComponent->SetRelativeLocation(FVector::ZeroVector);
}

// Called when the game starts or when spawned
void ABaseProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABaseProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (HitComp)
	{
		
	}
}
void ABaseProjectile::SetVelocity(FVector& InDir)
{
	FRotator rot = InDir.Rotation();
	SetActorRelativeRotation(rot);
	ProjectileMovementComponent->Velocity = InDir * ProjectileMovementComponent->InitialSpeed;
}

// Called every frame
void ABaseProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

