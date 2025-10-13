// Fill out your copyright notice in the Description page of Project Settings.


#include "ObstacleElectric.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"
#include "NiagaraComponent.h"
#include "CanInteract.h"

AObstacleElectric::AObstacleElectric()
{
	PrimaryActorTick.bCanEverTick = true;

	sceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("sceneRoot"));
	boxDamageColl = CreateDefaultSubobject<UBoxComponent>(TEXT("boxDamageColl"));
	boxInteractColl = CreateDefaultSubobject<UBoxComponent>(TEXT("boxInteractColl"));
	smComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("smComp"));
	VFX_electric = CreateDefaultSubobject<UNiagaraComponent>(TEXT("VFX_electric"));

	SetRootComponent(sceneRoot);
	boxDamageColl->SetupAttachment(sceneRoot);
	boxInteractColl->SetupAttachment(sceneRoot);
	VFX_electric->SetupAttachment(boxDamageColl);
	smComp->SetupAttachment(boxInteractColl);

	boxDamageColl->SetRelativeLocation(FVector(180, 0, 50));
	boxDamageColl->SetBoxExtent(FVector(120, 20, 32));
	boxInteractColl->SetBoxExtent(FVector(70, 70, 100));
	VFX_electric->SetRelativeLocation(FVector(-150, 0, 0));
	smComp->SetRelativeScale3D(FVector(0.5, 0.5, 2));

	boxDamageColl->SetCollisionProfileName(TEXT("Obstacle"));;
	boxInteractColl->SetCollisionProfileName(TEXT("Obstacle"));
}

void AObstacleElectric::BeginPlay()
{
	Super::BeginPlay();

	// bCanInteract가 true = 상호작용 가능한 물체라는것.
	// 인스턴스들 중 상호작용 가능한 물체만 F키 통해 회전 가능
	// 상호작용 불가능하다면 불에 닿았을 시 데미지만 처리
	if (ObstacleInfo.bCanInteract)
	{
		boxDamageColl->OnComponentBeginOverlap.AddDynamic(this, &AFloor3ObstacleBase::OnObstacleOverlapDamage);
		boxInteractColl->OnComponentBeginOverlap.AddDynamic(this, &AFloor3ObstacleBase::OnObstacleOverlapInteract);
		boxInteractColl->OnComponentEndOverlap.AddDynamic(this, &AFloor3ObstacleBase::OnObstacleOverlapInteractEnd);
	}
	else
	{
		boxDamageColl->OnComponentBeginOverlap.AddDynamic(this, &AFloor3ObstacleBase::OnObstacleOverlapDamage);
	}
}

void AObstacleElectric::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bRotating)
	{
		FRotator newRot = FMath::RInterpTo(GetActorRotation(), targetRot, DeltaTime, rotateSpeed);
		SetActorRotation(newRot);

		// 거의 도달하면 종료
		if (newRot.Equals(targetRot, 0.1f))
		{
			SetActorRotation(targetRot);
			bRotating = false;
		}
	}
}

void AObstacleElectric::RotateTarget()
{
	if (bRotateRight)
	{
		bRotating = true;
		targetRot = GetActorRotation() + FRotator(0, 90.f, 0);
		UE_LOG(LogTemp, Warning, TEXT("RotateRight"));

	}
	else
	{
		bRotating = true;
		targetRot = GetActorRotation() + FRotator(0, -90.f, 0);
		UE_LOG(LogTemp, Warning, TEXT("RotateLeft"));
	}
}
