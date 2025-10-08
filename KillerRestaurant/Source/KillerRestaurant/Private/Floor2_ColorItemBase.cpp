// Fill out your copyright notice in the Description page of Project Settings.


#include "Floor2_ColorItemBase.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"
#include "Materials/MaterialInterface.h"

AFloor2_ColorItemBase::AFloor2_ColorItemBase()
{
	PrimaryActorTick.bCanEverTick = true;

	sceneComp = CreateDefaultSubobject<USceneComponent>(TEXT("sceneComp"));
	SetRootComponent(sceneComp);

	smComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("smComp"));
	smComp->SetupAttachment(sceneComp);
}

void AFloor2_ColorItemBase::BeginPlay()
{
	Super::BeginPlay();

	materialPaths = {
	TEXT("/Script/Engine.Material'/Game/Yuchin/Material/M_Red.M_Red'"),
	TEXT("/Script/Engine.Material'/Game/Yuchin/Material/M_Yellow.M_Yellow'"),
	TEXT("/Script/Engine.Material'/Game/Yuchin/Material/M_Green.M_Green'"),
	TEXT("/Script/Engine.Material'/Game/Yuchin/Material/M_Blue.M_Blue'")
	};

	for (const FString& Path : materialPaths)
	{
		UMaterialInterface* mat = LoadObject<UMaterialInterface>(nullptr, *Path);
		if (mat)
		{
			loadedMaterials.Add(mat);
		}
	}
}

void AFloor2_ColorItemBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFloor2_ColorItemBase::ChangeColor()
{
	switch (cnt %= 4)
	{
	case 0:
		smComp->SetMaterial(0, loadedMaterials[0]);
		break;
	case 1:
		smComp->SetMaterial(0, loadedMaterials[1]);
		break;
	case 2:
		smComp->SetMaterial(0, loadedMaterials[2]);
		break;
	case 3:
		smComp->SetMaterial(0, loadedMaterials[3]);
		break;
	default:
		break;
	}

	cnt++;
}

