// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "DefenseBlockBase.h"

#include "Sam.generated.h"










UCLASS()
class GMTK2023_API ASam : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASam();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<TSubclassOf<ADefenseBlockBase>> towerTypes;
	
	UPROPERTY(BlueprintReadWrite)
		float perRoundMoney;

	UPROPERTY(BlueprintReadWrite)
		float currentMoney;


	UPROPERTY()
		bool spawnQueued;

	UPROPERTY()
		float spawnDelayTimer;

	UPROPERTY(EditAnywhere)
		float spawnDelay = 1.0f;

	UPROPERTY()
		int spawnWaveNumber;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	UFUNCTION(BLueprintCallable)
		void SpawnTowers(int waveNumber);

	UFUNCTION(BlueprintCallable)
		TSubclassOf<ADefenseBlockBase> GetCheapestTower();

	UFUNCTION(BlueprintCallable)
		void ForceSpawnTowers(int waveNumber);

};
