// Fill out your copyright notice in the Description page of Project Settings.


#include "NPCBase.h"
#include "KillerRestaurantCharacter.h"
#include "Components/BoxComponent.h"


ANPCBase::ANPCBase()
{
	PrimaryActorTick.bCanEverTick = true;

	boxColl = CreateDefaultSubobject<UBoxComponent>(TEXT("boxColl"));
	boxColl->SetupAttachment(RootComponent);
	boxColl->SetRelativeScale3D(FVector(2, 2, 4.4));
}

void ANPCBase::BeginPlay()
{
	Super::BeginPlay();
	
	boxColl->OnComponentBeginOverlap.AddDynamic(this, &ANPCBase::OnOverlapNPCBegin);
	boxColl->OnComponentEndOverlap.AddDynamic(this, &ANPCBase::OnOverlapNPCEnd);

}

void ANPCBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ANPCBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ANPCBase::StartInteract()
{
	UE_LOG(LogTemp, Warning, TEXT("ANPCBase::StartInteract"));

}

void ANPCBase::OnOverlapNPCBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (AKillerRestaurantCharacter* player = Cast<AKillerRestaurantCharacter>(OtherActor))
	{
		player->currentOverlappedNPC = this;		
	}
}

void ANPCBase::OnOverlapNPCEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (AKillerRestaurantCharacter* player = Cast<AKillerRestaurantCharacter>(OtherActor))
	{
		if (player->currentOverlappedNPC == this)
		{
			player->currentOverlappedNPC = nullptr;
		}
	}
}

