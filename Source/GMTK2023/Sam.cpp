// Fill out your copyright notice in the Description page of Project Settings.


#include "Sam.h"


#include "TowerSpot.h"

// Sets default values
ASam::ASam()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	spawnQueued = false;
	spawnDelayTimer = 0.0f;
	spawnWaveNumber = 0;

}

// Called when the game starts or when spawned
void ASam::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASam::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	if (spawnQueued) {
		spawnDelayTimer += DeltaTime;

		if (spawnDelayTimer > spawnDelay) {
			spawnQueued = false;
			ForceSpawnTowers(spawnWaveNumber);
		}
	}


}

void ASam::SpawnTowers(int waveNumber) {
	
	spawnQueued = true;
	spawnDelayTimer = 0.0f;
	spawnWaveNumber = waveNumber;

}



void ASam::ForceSpawnTowers(int waveNumber) {

	currentMoney = perRoundMoney * (float)(waveNumber + 1);


	if (GetCheapestTower()) {
		float minRequiredMoney = GetCheapestTower()->GetDefaultObject<ADefenseBlockBase>()->BlockCost;

		TArray<ATowerSpot*> towerSpots;

		TArray<AActor*> towerActors;
		UGameplayStatics::GetAllActorsWithTag(GetWorld(), "TowerSpot", towerActors);

		for (AActor* tower : towerActors) {
			towerSpots.Add(Cast<ATowerSpot>(tower));
		}

		//sort the towers spots so that we buy on the higher priority spots first
		Algo::SortBy(towerSpots, &ATowerSpot::priority, TGreater<>());

		//now loop through the towers spots and try to build
		for (ATowerSpot* towerSpot : towerSpots) {

			//only start trying to spawn if sam still has enough money
			if (currentMoney >= minRequiredMoney && waveNumber >= towerSpot->waveUnlock) {


				//while this tower is unoccupied keep trying to spawn
				while (!towerSpot->occupied) {

					//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::White, "Running");



					int rand = (int)FMath::RandRange(0.0f, (float)towerTypes.Num());


					if (currentMoney >= towerTypes[rand]->GetDefaultObject<ADefenseBlockBase>()->BlockCost) {


						FActorSpawnParameters params;
						FVector spawnLocation = towerSpot->GetActorLocation();
						spawnLocation.Y = 0.0f;

						FTransform spawnTransform;
						spawnTransform.SetLocation(spawnLocation);
						spawnTransform.SetRotation(FVector(1.0f, 0.0f, 0.0f).Rotation().Quaternion());


						ADefenseBlockBase* spawned = GetWorld()->SpawnActor<ADefenseBlockBase>(towerTypes[rand], spawnTransform, params);

						towerSpot->occupied = true;
						towerSpot->OccupyingTower = spawned;
						spawned->towerSpot = towerSpot;

						currentMoney -= towerTypes[rand]->GetDefaultObject<ADefenseBlockBase>()->BlockCost;

					}



				}
			}
		}
	}

}









TSubclassOf<ADefenseBlockBase> ASam::GetCheapestTower() {
	float cost = 1000000.0f;
	TSubclassOf<ADefenseBlockBase> cheapest;

	UE_LOG(LogTemp, Warning, TEXT("Length Of Types: %d"), towerTypes.Num());

	for (TSubclassOf<ADefenseBlockBase> tower : towerTypes) {
		float tempCost = tower->GetDefaultObject<ADefenseBlockBase>()->BlockCost;
		
		if (tempCost < cost) {
			cost = tempCost;
			cheapest = tower;
		}

	}

	return cheapest;
}