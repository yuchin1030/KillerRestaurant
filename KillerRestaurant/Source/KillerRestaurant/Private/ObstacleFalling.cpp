// Fill out your copyright notice in the Description page of Project Settings.


#include "ObstacleFalling.h"
#include "GeometryCollection/GeometryCollectionComponent.h"
#include "Components/SphereComponent.h"
#include <Kismet/GameplayStatics.h>
#include "KillerRestaurantCharacter.h"

AObstacleFalling::AObstacleFalling()
{
    PrimaryActorTick.bCanEverTick = true;

    destructibleMeshComp = CreateDefaultSubobject<UGeometryCollectionComponent>(TEXT("destructibleMeshComp"));
    sph_DamageColl = CreateDefaultSubobject<USphereComponent>(TEXT("sph_DamageColl"));

    SetRootComponent(sph_DamageColl);

    destructibleMeshComp->SetupAttachment(sph_DamageColl);
    destructibleMeshComp->SetSimulatePhysics(true);
    destructibleMeshComp->SetNotifyRigidBodyCollision(true);

    sph_DamageColl->SetCollisionProfileName(TEXT("Obstacle"));
    //destructibleMeshComp->SetCollisionProfileName(TEXT("PhysicsActor"));

}

void AObstacleFalling::BeginPlay()
{
    /*
    Origin: 폭발 중심점 - 이 위치를 기준으로 모든 파편이나 물체에 바깥쪽으로 힘이 전달됨
    Radius: 충격이 미치는 범위(반경)
    Stength: 충격의 세기 - 값이 클수록 더 멀리, 더 강하게 튕겨나감. 보통 200~2000 사이가 적당하고, 물체 질량이 클수록 더 큰 값이 필요함.
    ERadialImpulseFalloff: RIF_Constant - Radius 안의 모든 물체에 동일한 힘 적용 || RIF_Linear - 중심에서 멀어질수록 점점 힘이 약해짐
    bVelChange: true면 질량을 무시하고 순수 속도 변화만 적용. 
    - 가벼운 조각들이 똑같이 튀게 하고 싶다면 true, 실제 물리(무거운 건 덜 튀게)로 하려면 false. (여기서는 false로 해야 제자리에서 깨짐)
    */
    // AddRadialImpulse: 모아져 있다가 밖으로 터지듯 분해되는 효과 - Chaos Geometry Collection에서 일종의 Explode 효과
    destructibleMeshComp->AddRadialImpulse(GetActorLocation(), 100, 300, ERadialImpulseFalloff::RIF_Constant, false);
    sph_DamageColl->OnComponentBeginOverlap.AddDynamic(this, &AFloor3ObstacleBase::OnObstacleOverlapDamage);
    //UE_LOG(LogTemp, Warning, TEXT("?????????"));

}

//
//void AObstacleFalling::OnDamageHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
//{
//   /* if (OtherActor && OtherActor->ActorHasTag("Player"))
//    {
//        class AKillerRestaurantCharacter* player = Cast<AKillerRestaurantCharacter>((UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)));
//
//        player->TakeDamage(ObstacleInfo.damage);
//    }*/
//}
