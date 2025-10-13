// Fill out your copyright notice in the Description page of Project Settings.


#include "ObstacleBulletSpawner.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"
#include "ObstacleBulletProjectile.h"

AObstacleBulletSpawner::AObstacleBulletSpawner()
{
	PrimaryActorTick.bCanEverTick = true;

	sceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("sceneRoot"));
	spawnerMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("bulletMesh"));

	SetRootComponent(sceneRoot);
	spawnerMesh->SetupAttachment(sceneRoot);
}

void AObstacleBulletSpawner::BeginPlay()
{
	Super::BeginPlay();

	// spawnInterval 간격으로 반복 발사
	FTimerHandle spawnTimerHdl;
	GetWorldTimerManager().SetTimer(spawnTimerHdl, this, &AObstacleBulletSpawner::SpawnBullet, spawnInterval, true);
}

void AObstacleBulletSpawner::SpawnBullet()
{
	if (!bulletClass)
		return;

	FActorSpawnParameters params;
	// 이 액터를 소유한(Spawn시킨) 액터 지정
	params.Owner = this;

	FVector SpawnLocation = GetActorLocation();

	AObstacleBulletProjectile* spawnedBulletRef = GetWorld()->SpawnActor<AObstacleBulletProjectile>(bulletClass, SpawnLocation, spawnRot, params);
	
}
