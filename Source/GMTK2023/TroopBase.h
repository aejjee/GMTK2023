// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "PaperFlipbook.h"
#include "Kismet/GameplayStatics.h"

#include "Engine/EngineTypes.h"



#include "Marker.h"
#include "MyGameModeBase.h"

#include "PlayerCharacter.h"

#include "TroopBase.generated.h"

/**
 * 
 */
UCLASS()
class GMTK2023_API ATroopBase : public APaperCharacter
{
	GENERATED_BODY()
public:
	ATroopBase();

	UPROPERTY(BlueprintReadWrite)
		float health;

	UPROPERTY(BlueprintReadWrite)
		AMarker* targetLocation;

	UPROPERTY(BlueprintReadWrite)
		AMarker* nextLocation;

	// Used to stop the troops if they get to the end of the path.	
	UPROPERTY(BlueprintReadWrite)
	bool idle;

	// The cost of this enemy in currency
	UPROPERTY(BlueprintReadWrite)
	int SpawnCost;	
	
	UPROPERTY(BlueprintReadWrite)
		TMap<int, AMarker*> levelLocations;

	UPROPERTY(BlueprintReadWrite)
		int currentLocationPosition;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float attackDamage;

	UPROPERTY(BlueprintReadWrite)
		AActor* targetedTower;

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
		virtual void DamageHealth(float value);

	UFUNCTION(BlueprintCallable)
		virtual TArray<AActor*> GetTargets();

	UFUNCTION(BlueprintCallable)
		virtual TArray<AMarker*> GetLocationPath();

	UFUNCTION(BlueprintCallable)
		virtual void AdvanceLocation();

	UFUNCTION()
		virtual void Move(float DeltaTime);

private:
	// Gets the number of seconds for this animation, taking play rate into account.
	float GetAnimationDuration(UPaperFlipbook* animation);
};
