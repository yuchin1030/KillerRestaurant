// Fill out your copyright notice in the Description page of Project Settings.


#include "ObstacleBulletProjectile.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

AObstacleBulletProjectile::AObstacleBulletProjectile()
{
	PrimaryActorTick.bCanEverTick = true;

	sceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("sceneRoot"));
	sph_BulletDamageColl = CreateDefaultSubobject<USphereComponent>(TEXT("sph_BulletDamageColl"));
	bulletMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("bulletMesh"));
	projectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	
	SetRootComponent(sceneRoot);
	sph_BulletDamageColl->SetupAttachment(sceneRoot);
	bulletMesh->SetupAttachment(sph_BulletDamageColl);

	projectileMovement->InitialSpeed = 2000;
	projectileMovement->MaxSpeed = 2000;
	projectileMovement->bRotationFollowsVelocity = true;
	projectileMovement->ProjectileGravityScale = 0.f;

	sph_BulletDamageColl->SetCollisionProfileName(TEXT("Obstacle"));
	bulletMesh->SetCollisionProfileName(TEXT("Obstacle"));
}

void AObstacleBulletProjectile::BeginPlay()
{
	Super::BeginPlay();

	sph_BulletDamageColl->OnComponentBeginOverlap.AddDynamic(this, &AFloor3ObstacleBase::OnObstacleOverlapDamage);

	FTimerHandle lifeTimerHdl;
	GetWorldTimerManager().SetTimer(lifeTimerHdl, this, &AObstacleBulletProjectile::DestroyProjectile, lifeTime, false);
}

void AObstacleBulletProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AObstacleBulletProjectile::DestroyProjectile()
{
	Destroy();
}