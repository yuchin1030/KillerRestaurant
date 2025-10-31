// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemBase.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "KillerRestaurantCharacter.h"

AItemBase::AItemBase()
{
	PrimaryActorTick.bCanEverTick = true;

	smComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("smComp"));
	sphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("sphereComp"));

	SetRootComponent(sphereComp);
	smComp->SetupAttachment(sphereComp);

	Tags.Add(FName("Interact/PickUpItem"));
}

void AItemBase::BeginPlay()
{
	Super::BeginPlay();
	
	sphereComp->OnComponentBeginOverlap.AddDynamic(this, &AItemBase::OnItemOverlapInteract);
	sphereComp->OnComponentEndOverlap.AddDynamic(this, &AItemBase::OnItemOverlapInteractEnd);
}

void AItemBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AItemBase::OnItemOverlapInteract(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor->ActorHasTag("Player"))
	{
		class AKillerRestaurantCharacter* player = Cast<AKillerRestaurantCharacter>(OtherActor);

		if (player)
			player->currentOverlappedInteractItem = this;
	}
}

void AItemBase::OnItemOverlapInteractEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor && OtherActor->ActorHasTag("Player"))
	{
		class AKillerRestaurantCharacter* player = Cast<AKillerRestaurantCharacter>(OtherActor);

		if (player)
			player->currentOverlappedInteractItem = nullptr;
	}
}

