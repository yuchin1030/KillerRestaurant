// Fill out your copyright notice in the Description page of Project Settings.


#include "ObstacleAutoRotatingElectric.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"
#include "NiagaraComponent.h"

AObstacleAutoRotatingElectric::AObstacleAutoRotatingElectric()
{
	PrimaryActorTick.bCanEverTick = true;

	sceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("sceneRoot"));
	boxDamageColl = CreateDefaultSubobject<UBoxComponent>(TEXT("boxDamageColl"));
	smComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("smComp"));
	VFX_electric = CreateDefaultSubobject<UNiagaraComponent>(TEXT("VFX_electric"));

	SetRootComponent(sceneRoot);
	smComp->SetupAttachment(sceneRoot);
	boxDamageColl->SetupAttachment(sceneRoot);
	VFX_electric->SetupAttachment(boxDamageColl);

	boxDamageColl->SetRelativeLocation(FVector(180, 0, 50));
	boxDamageColl->SetBoxExtent(FVector(120, 20, 32));
	VFX_electric->SetRelativeLocation(FVector(-150, 0, 0));
	smComp->SetRelativeScale3D(FVector(0.5, 0.5, 2));

	boxDamageColl->SetCollisionProfileName(TEXT("Obstacle"));
}

void AObstacleAutoRotatingElectric::BeginPlay()
{
	Super::BeginPlay();

	boxDamageColl->OnComponentBeginOverlap.AddDynamic(this, &AFloor3ObstacleBase::OnObstacleOverlapDamage);

	FTimerHandle autoRotateTimerHdl;
	GetWorldTimerManager().SetTimer(autoRotateTimerHdl, this, &AObstacleAutoRotatingElectric::StartRotation, rotateInterval, false);
}

void AObstacleAutoRotatingElectric::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bRotating)
	{
		rotateElapsedTime += DeltaTime;
		float alpha = FMath::Clamp(rotateElapsedTime / rotateDuration, 0.f, 1.f);
		FRotator newRot = FMath::Lerp(sceneRoot->GetRelativeRotation(), targetRot, alpha);
		sceneRoot->SetRelativeRotation(newRot);

		if (alpha >= 1.f)
		{
			bRotating = false;

			FTimerHandle autoRotateTimerHdl;
			// 다음 회전을 위해 Timer 시작
			GetWorldTimerManager().SetTimer(autoRotateTimerHdl, this, &AObstacleAutoRotatingElectric::StartRotation, rotateInterval, false);
		}
	}
}

void AObstacleAutoRotatingElectric::StartRotation()
{
	if (bAutoRotateRight)
	{
		targetRot = sceneRoot->GetRelativeRotation() + FRotator(0, 90.f, 0);
	}
	else
	{
		targetRot = sceneRoot->GetRelativeRotation() + FRotator(0, -90.f, 0);
	}

	rotateElapsedTime = 0;
	bRotating = true;
}

