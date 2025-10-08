// Fill out your copyright notice in the Description page of Project Settings.


#include "MazeGenerator.h"
#include "Components/InstancedStaticMeshComponent.h"
#include <Kismet/GameplayStatics.h>
#include "KillerRestaurantCharacter.h"

AMazeGenerator::AMazeGenerator()
{
	PrimaryActorTick.bCanEverTick = true;

	WallISM = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("WallISM"));
	RootComponent = WallISM;

	GateISM = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("GateISM"));
	GateISM->SetupAttachment(RootComponent);
}

void AMazeGenerator::BeginPlay()
{
	Super::BeginPlay();
	
    //AKillerRestaurantCharacter* Player = Cast<AKillerRestaurantCharacter>(UGameplayStatics::GetActorOfClass(GetWorld(), AKillerRestaurantCharacter::StaticClass()));
    //
    //if (Player)
    //{
    //    SetActorLocation(Player->GetActorLocation());
    //}


	// 고정 미로 데이터 설정 (나중에 CSV나 DataTable로도 교체 가능)
	MazeData = {
		{1,1,1,1,1,1,1,1},
		{1,0,0,3,0,2,0,1},
		{1,0,1,0,1,1,0,1},
		{1,0,1,0,1,0,0,1},
		{1,0,0,0,0,1,0,1},
		{1,1,1,1,1,1,1,1},
	};

	GenerateMaze();

}

void AMazeGenerator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMazeGenerator::GenerateMaze()
{
    MazeCells.SetNum(MazeData.Num());

    for (int32 Y = 0; Y < MazeData.Num(); ++Y)
    {
        MazeCells[Y].SetNum(MazeData[Y].Num());

        for (int32 X = 0; X < MazeData[Y].Num(); ++X)
        {
            FMazeCell& Cell = MazeCells[Y][X];
            FVector Location = FVector(0) + FVector(X * CellSize, Y * CellSize, 0.f);

            switch (MazeData[Y][X])
            {
            case 1: // 벽
                Cell.bIsWall = true;
                Cell.InstanceIndex = WallISM->AddInstance(FTransform(Location));
                break;

            case 3: // 잠긴 문
                Cell.bIsGate = true;
                Cell.bIsUnlocked = false;
                Cell.InstanceIndex = GateISM->AddInstance(FTransform(Location));
                break;

            case 2: // 던전 입구
                Cell.bIsDungeonEntrance = true;
                SpawnDungeonEntrance(Location);
                break;

            default:
                break;
            }
        }

        UE_LOG(LogTemp, Warning, TEXT("Generate Maze"));
    }


}

void AMazeGenerator::SpawnDungeonEntrance(const FVector& Location)
{
    if (DungeonEntranceClass)
    {
        GetWorld()->SpawnActor<AActor>(DungeonEntranceClass, Location, FRotator::ZeroRotator);
    }
}

void AMazeGenerator::UnlockGateAt(FIntPoint Cell)
{
    if (!MazeCells.IsValidIndex(Cell.Y) || !MazeCells[Cell.Y].IsValidIndex(Cell.X))
        return;

    FMazeCell& Target = MazeCells[Cell.Y][Cell.X];
    if (Target.bIsGate && !Target.bIsUnlocked)
    {
        Target.bIsUnlocked = true;

        // 문을 열기: ISM 인스턴스 제거
        GateISM->RemoveInstance(Target.InstanceIndex);

        // 효과나 사운드, 파티클 추가 가능
        UE_LOG(LogTemp, Log, TEXT("Gate at (%d, %d) unlocked!"), Cell.X, Cell.Y);
    }
}

