// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MazeGenerator.generated.h"

USTRUCT()
struct FMazeCell
{
    GENERATED_BODY()

    bool bIsWall = false;
    bool bIsGate = false;
    bool bIsUnlocked = true;
    bool bIsDungeonEntrance = false;

    int32 InstanceIndex = -1; // ISM 인스턴스 관리용
};

UCLASS()
class KILLERRESTAURANT_API AMazeGenerator : public AActor
{
	GENERATED_BODY()
	
public:	
	AMazeGenerator();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

    // 미로 데이터 (0: 빈칸, 1: 벽, 2: 던전입구, 3: 잠긴문)
    TArray<TArray<int32>> MazeData;

    // 셀 데이터
    TArray<TArray<FMazeCell>> MazeCells;

    // Instanced Mesh Components
    UPROPERTY(EditAnywhere)
    UInstancedStaticMeshComponent* WallISM;

    UPROPERTY(EditAnywhere)
    UInstancedStaticMeshComponent* GateISM;

    UPROPERTY(EditAnywhere, Category = "MySettings")
    TSubclassOf<AActor> DungeonEntranceClass;

    // 미로의 각 셀(칸) 간격 ? 한 칸의 실제 월드 공간 크기
    UPROPERTY(EditAnywhere)
    float CellSize = 100.f;


    UFUNCTION()
    void GenerateMaze();

    UFUNCTION()
    void SpawnDungeonEntrance(const FVector& Location);

    UFUNCTION(BlueprintCallable)
    void UnlockGateAt(FIntPoint Cell);

};
