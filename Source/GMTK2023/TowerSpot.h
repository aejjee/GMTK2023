// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"


#include "TowerSpot.generated.h"

class ADefenseBlockBase;

UCLASS()
class GMTK2023_API ATowerSpot : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATowerSpot();


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int waveUnlock;

	UPROPERTY(BlueprintReadWrite)
		bool occupied;

	UPROPERTY(BlueprintReadWrite)
		ADefenseBlockBase* OccupyingTower;

	//Higher number indicates higher priority
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int priority = 0;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
