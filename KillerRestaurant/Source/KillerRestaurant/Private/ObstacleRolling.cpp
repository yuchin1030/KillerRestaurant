// Fill out your copyright notice in the Description page of Project Settings.


#include "ObstacleRolling.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"

AObstacleRolling::AObstacleRolling()
{
	PrimaryActorTick.bCanEverTick = true;

	sceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("sceneRoot"));
	caps_RollingDamageColl = CreateDefaultSubobject<UCapsuleComponent>(TEXT("caps_RollingDamageColl"));
	rollingMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	endMarker = CreateDefaultSubobject<USceneComponent>(TEXT("endMarker"));

	SetRootComponent(sceneRoot);
	caps_RollingDamageColl->SetupAttachment(sceneRoot);
	rollingMeshComp->SetupAttachment(caps_RollingDamageColl);
	endMarker->SetupAttachment(caps_RollingDamageColl);

	caps_RollingDamageColl->SetRelativeRotation((FRotator(0, 0, 90.f)));
	caps_RollingDamageColl->SetCapsuleHalfHeight(140.f);
	caps_RollingDamageColl->SetCapsuleRadius(70.f);
	//rollingMeshComp->SetRelativeRotation((FRotator(0, 0, 90.f)));

	caps_RollingDamageColl->SetCollisionProfileName(TEXT("Obstacle"));
	rollingMeshComp->SetCollisionProfileName(TEXT("Obstacle"));
}

void AObstacleRolling::BeginPlay()
{
	Super::BeginPlay();

	caps_RollingDamageColl->OnComponentBeginOverlap.AddDynamic(this, &AFloor3ObstacleBase::OnObstacleOverlapDamage);

	startPoint = GetActorLocation(); // 현재 위치를 시작점으로
	currentSpeed = 0.f;
	targetSpeed = moveSpeed;

	endPoint = endMarker->GetComponentLocation();

}

void AObstacleRolling::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!bWaiting)
	{
		FVector currentLocation = GetActorLocation();
		FVector targetLocation = bMovingToEnd ? endPoint : startPoint;
		FVector moveDir = (targetLocation - currentLocation).GetSafeNormal();
		float distance = FVector::Dist(currentLocation, targetLocation);

		// 감속 구간
		if (distance < slowDownDist)
			targetSpeed = 0.f;
		else
			targetSpeed = moveSpeed;

		// 부드러운 가감속
		currentSpeed = FMath::FInterpTo(currentSpeed, targetSpeed, DeltaTime, accelInterpSpeed);

		// 이동
		FVector newLocation = currentLocation + moveDir * currentSpeed * DeltaTime;
		SetActorLocation(newLocation, true);

		// 도착 판정
		if (distance < 10.f && currentSpeed < 50.f)
		{
			bWaiting = true;
			ToggleDirection();
			//GetWorldTimerManager().SetTimer(WaitTimerHandle, this, &AObstacleRolling::ToggleDirection, stopDelay, false);
		}
	}
	
	// --- 회전 처리 (항상 - Cylinder가 굴러가는 느낌)
	float rollDegrees;

	if (currentSpeed > 0.f)
	{
		// 이동 속도 기반 회전
		// Cylinder 반지름을 고려해서 회전량 계산
		// 회전각 (rad) = 이동거리​ / 반지름
		float rollRadians = currentSpeed * DeltaTime / rotateRadius;	// 숫자 높을수록 느리게 굴러감(Default: 50, 인스턴스별로 조정 가능)

		/*
		Mesh 자체를 Scale로 키우면 실제 radius도 같이 Scale 적용
		따라서 코드에서 CylinderRadius를 Mesh의 실제 반지름 * Scale로 계산하면 항상 자연스러움:
		이렇게 하면 Mesh 크기가 커지든 작아지든 항상 올바른 회전량을 적용할 수 있음

		float ActualRadius = rotateRadius(50) * MeshComp->GetComponentScale().X;
		float RollRadians = CurrentSpeed * DeltaTime / ActualRadius;
		*/

		// 언리얼에서 회전 단위는 도(degree) 이므로 변환 (degree = rad * 180/파이)
		rollDegrees = FMath::RadiansToDegrees(rollRadians);
	}
	// 멈췄을 때 회전
	else
	{
		// 도착지점에서 회전 아예 없는거보다 살짝은 굴러야 자연스러움(필요에 따라 수치(50) 조절해주기)
		rollDegrees = (rotateRadius + 50) * DeltaTime;
	}

	AddActorLocalRotation(FRotator(rollDegrees, 0.f, 0.f));

}

void AObstacleRolling::ToggleDirection()
{
	bMovingToEnd = !bMovingToEnd;
	bWaiting = false;
}