// Fill out your copyright notice in the Description page of Project Settings.


#include "TroopBase.h"



// Sets default values
ATroopBase::ATroopBase()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Tags.Add("troop");

	health = 100.0f;
}

// Called when the game starts or when spawned
void ATroopBase::BeginPlay()
{
	Super::BeginPlay();


	TArray<AMarker*> tempLocations = GetLocationPath();

	if (tempLocations.Num() > 0) {
		
		for (AMarker* loc : tempLocations) {
			levelLocations.Add(TTuple<int, AMarker*>({ loc->markerIndex, loc }));
		}

		targetLocation = levelLocations[0];
	}

	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, "Location size" + FString::SanitizeFloat(levelLocations.Num()));
	

}

// Called every frame
void ATroopBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	if (health <= 0.0f) {
		Destroy();
	}


	if (targetLocation && !targetedTower) {

		FVector toTargetLocation = targetLocation->GetActorLocation() - GetActorLocation();

		SetActorRotation(toTargetLocation.GetSafeNormal().Rotation());

		SetActorLocation(GetActorLocation() + (toTargetLocation.GetSafeNormal() * 30.0f * DeltaTime), true);

		GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::Green, targetLocation->GetName());

	}
	

	

}

// Called to bind functionality to input
void ATroopBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	

}


void ATroopBase::DamageHealth(float value) {
	health -= value;
}

TArray<AActor*> ATroopBase::GetTargets() {

	
	TArray<AActor*> targets;

	TArray<AActor*> targetActors;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), FName("Tower"), targetActors);

	

	for (AActor* targetActor : targetActors) {
		targets.Add(Cast<AMarker>(targetActor));
	}
	

	return targets;
}

TArray<AMarker*> ATroopBase::GetLocationPath() {

	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::White, "searching");
	
	TArray<AMarker*> locations;

	TArray<AActor*> markerActors;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), "Marker", markerActors);

	for (AActor* marker : markerActors) {
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::White, marker->GetName());
		locations.Add(Cast<AMarker>(marker));
	}


	return locations;
}

void ATroopBase::AdvanceLocation() {
	currentLocationPosition += 1;

	if (levelLocations.Num() > currentLocationPosition) {
		
		targetLocation = levelLocations[currentLocationPosition];
	}
	
}