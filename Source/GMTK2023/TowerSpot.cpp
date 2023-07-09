// Fill out your copyright notice in the Description page of Project Settings.


#include "TowerSpot.h"

// Sets default values
ATowerSpot::ATowerSpot()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Tags.Add("TowerSpot");
	
	occupied = false;
	OccupyingTower = nullptr;

}

// Called when the game starts or when spawned
void ATowerSpot::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATowerSpot::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

