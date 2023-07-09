// Fill out your copyright notice in the Description page of Project Settings.


#include "TroopBase.h"

#include "PaperFlipbook.h"
#include "PaperFlipbookComponent.h"

#include "DefenseBlockBase.h"


// Sets default values
ATroopBase::ATroopBase()
	: SpawnCost(10)
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Tags.Add("troop");

	health = 100.0f;

	idle = false;

	targetSearchTime = 0.0f;
	attackTimer = 0.0f;

	//OnActorBeginOverlap.AddDynamic(this, &ATroopBase::ActorEnteredAttackRange);
	//OnActorEndOverlap.AddDynamic(this, &ATroopBase::ActorExitedAttackRange);

	inAttackRange = false;

	targetedTower = nullptr;


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

	CurrentGameMode = Cast<AMyGameModeBase>(GetWorld()->GetAuthGameMode());	

}

// Called every frame
void ATroopBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	targetSearchTime += DeltaTime;
	attackTimer += DeltaTime;

	

	//if combat is on and game is unpaused
	if (!CurrentGameMode->GetGamePaused() && CurrentGameMode->IsWaveInProgress()
		&& !idle) {

		inAttackRange = IsValid(targetedTower) && inAttackRange;
		
		if (!targetedTower && targetSearchTime > 1.0f) {
			targetSearchTime = 0.0f;

			

			//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Green, "Searching for tower");

			targetedTower = FindClosestTarget();
		}
		

		Move(DeltaTime);


		//if in range of the tower then attack
		if (inAttackRange && attackTimer > attackSpeed) {

			targetedTower->DamageBlock(attackDamage);

			if (targetedTower->Health <= 0.0f) {
				targetedTower = nullptr;
			}

			PlayAttackAnimation();

			attackTimer = 0.0f;
		}

	}
}

// Called to bind functionality to input
void ATroopBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}


bool ATroopBase::DamageHealth(float value) {
	health -= value;

	if (health <= 0.0f) {
		CurrentGameMode->SetNumOfEnemies(CurrentGameMode->GetNumOfEnemies());
		GetSprite()->SetFlipbook(DeathAnimation);
		SetLifeSpan(0.33f);
		return true;
	}

	return false;

}

TArray<ADefenseBlockBase*> ATroopBase::GetTargets() {

	
	TArray<ADefenseBlockBase*> targets;

	TArray<AActor*> targetActors;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), FName("Tower"), targetActors);

	

	for (AActor* targetActor : targetActors) {
		targets.Add(Cast<ADefenseBlockBase>(targetActor));
	}
	

	return targets;
}


ADefenseBlockBase* ATroopBase::FindClosestTarget() {

	


	//only if there are tower targets find the closest
	if (towerTargets.Num() > 0) {

		ADefenseBlockBase* closest = nullptr;
		float closestDist = 1000000.0;

		FVector actLoc = GetActorLocation();
		actLoc.Y = 0.0f;

		for (ADefenseBlockBase* tower : towerTargets) {
			
			//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, tower->GetName());


			FVector towerLoc = tower->GetActorLocation();
			towerLoc.Y = 0.0f;

			float d = FVector::Dist(actLoc, towerLoc);

			if (d < closestDist) {
				closestDist = d;
				closest = tower;
			}


		}

		return closest;


	}
	else {

		//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, "No Towers In Sight");
	}

	return nullptr;

}



TArray<AMarker*> ATroopBase::GetLocationPath() {

	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::White, "searching");
	
	TArray<AMarker*> locations;

	TArray<AActor*> markerActors;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), "Marker", markerActors);

	for (AActor* marker : markerActors) {
		//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::White, marker->GetName());
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


void ATroopBase::Move(float DeltaTime) {

	//if there is a targeted path marker, and we aren't currently attacking a tower, then move towards the marker
	if (targetLocation && !targetedTower) {

		FVector toTargetLocation = targetLocation->GetActorLocation() - GetActorLocation();


        //rotate only facing left or right
		FVector rotationV = toTargetLocation;
		rotationV.Z = 0.0f;
		rotationV.Y = 0.0f;

		SetActorRotation(rotationV.GetSafeNormal().Rotation());



		//do a sweep move
		FHitResult hitResult;
		SetActorLocation(GetActorLocation() + (toTargetLocation.GetSafeNormal() * 30.0f * DeltaTime), true, &hitResult);

		//but if troop is blocked by another troop rather than something else then move anyways
		
		if (hitResult.GetActor() == nullptr)
		{
			// Keeps the editor from dying if an enemy gets killed.
			return;
		}
		if (hitResult.bBlockingHit && hitResult.GetActor()->ActorHasTag("troop")) {
			SetActorLocation(GetActorLocation() + (toTargetLocation.GetSafeNormal() * 30.0f * DeltaTime), false);
		}

		//GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::Green, targetLocation->GetName());

	}

	else if (targetedTower) {
		FVector toTargetTower = targetedTower->GetActorLocation() - FVector(0.0f, 0.0f, 20.0f) - GetActorLocation();
		toTargetTower.Y = GetActorLocation().Y;

		FVector rotationV = toTargetTower;
		rotationV.Z = 0.0f;
		rotationV.Y = 0.0f;


		
		SetActorRotation(rotationV.GetSafeNormal().Rotation());
		//SetActorRotation(FVector(-1.0f, 0.0f, 0.0f).Rotation());


		//dont move once close enough
		if (toTargetTower.Length() > attackRange) {
			//do a sweep move
			FHitResult hitResult;
			SetActorLocation(GetActorLocation() + (toTargetTower.GetSafeNormal() * 30.0f * DeltaTime), true, &hitResult);

			if (hitResult.GetActor() == nullptr)
			{
				// Keep the editor from dying if the enemy dies
				return;
			}
			
			//but if troop is blocked by another troop rather than something else then move anyways
			if (hitResult.bBlockingHit && hitResult.GetActor()->ActorHasTag("troop")) {
				SetActorLocation(GetActorLocation() + (toTargetTower.GetSafeNormal() * 30.0f * DeltaTime), false);
			}
		}
		else if(!inAttackRange) {


			//if in attack range
			inAttackRange = true;
		}
		
	}
}





void ATroopBase::ActorEnteredAttackRange(AActor* MyOverlappedActor, AActor* OtherActor)
{
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Green, OtherActor->GetName());
	ADefenseBlockBase* enemy = Cast<ADefenseBlockBase>(OtherActor);
	if (enemy == nullptr)
	{
		return;
	}
	towerTargets.Add(enemy);
}

void ATroopBase::ActorExitedAttackRange(AActor* MyOverlappedActor, AActor* OtherActor)
{
	ADefenseBlockBase* enemy = Cast<ADefenseBlockBase>(OtherActor);
	if (enemy == nullptr)
	{
		return;
	}
	towerTargets.Remove(enemy);
}

float ATroopBase::GetAnimationDuration(UPaperFlipbook* animation)
{
	return animation->GetTotalDuration() * (1 / GetSprite()->GetPlayRate());
}

