// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "PaperFlipbook.h"
#include "Kismet/GameplayStatics.h"

#include "Engine/EngineTypes.h"


#include "PaperFlipbook.h"

#include "Marker.h"
#include "MyGameModeBase.h"

#include "PlayerCharacter.h"

#include "TroopBase.generated.h"


class ADefenseBlockBase;

/**
 * 
 */
UCLASS()
class GMTK2023_API ATroopBase : public APaperCharacter
{
	GENERATED_BODY()
public:
	ATroopBase();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float health;

	UPROPERTY(BlueprintReadWrite)
		AMarker* targetLocation;

	UPROPERTY(BlueprintReadWrite)
		AMarker* nextLocation;

	// Used to stop the troops if they get to the end of the path.	
	UPROPERTY(BlueprintReadWrite)
	bool idle;

	// The cost of this enemy in currency
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int SpawnCost;	
	
	UPROPERTY(BlueprintReadWrite)
		TMap<int, AMarker*> levelLocations;

	UPROPERTY(BlueprintReadWrite)
		int currentLocationPosition;
	


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float attackDamage;


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float attackRange = 10.0f;


	UPROPERTY(BlueprintReadWrite)
		bool inAttackRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float attackSpeed = 0.5f;

	UPROPERTY(BlueprintReadOnly)
		float attackTimer;

	UPROPERTY(BlueprintReadWrite)
		UPaperFlipbook* attackAnimation;


	UPROPERTY(BlueprintReadWrite)
		ADefenseBlockBase* targetedTower;

	UPROPERTY(BlueprintReadWrite)
		TArray< ADefenseBlockBase*> towerTargets;

	UPROPERTY()
		float targetSearchTime;

	// A reference to the current game mode.
	UPROPERTY(BlueprintReadOnly)
	AMyGameModeBase* CurrentGameMode;

	// The animation that plays when this enemy dies.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UPaperFlipbook* DeathAnimation;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable)
		virtual bool DamageHealth(float value);

	UFUNCTION(BlueprintCallable)
		virtual TArray<ADefenseBlockBase*> GetTargets();

	UFUNCTION(BlueprintCallable)
		virtual ADefenseBlockBase* FindClosestTarget();



	UFUNCTION(BlueprintCallable)
		virtual TArray<AMarker*> GetLocationPath();

	UFUNCTION(BlueprintCallable)
		virtual void AdvanceLocation();

	UFUNCTION()
		virtual void Move(float DeltaTime);



	//pulled from DefenseBlockBase
	UFUNCTION()
		// Gets called whenever an enemy enters the attack range.
		void ActorEnteredAttackRange(AActor* MyOverlappedActor, AActor* OtherActor);

	UFUNCTION()
	// Gets called whenever an enemy enters the attack range.
	void ActorExitedAttackRange(AActor* MyOverlappedActor, AActor* OtherActor);

	UFUNCTION(BlueprintImplementableEvent)
		void PlayAttackAnimation();


private:
	// Gets the number of seconds for this animation, taking play rate into account.
	float GetAnimationDuration(UPaperFlipbook* animation);

};
