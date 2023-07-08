// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"

#include "Kismet/GameplayStatics.h"

#include "Engine/EngineTypes.h"



#include "Marker.h"

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

	UPROPERTY(BlueprintReadWrite)
		TMap<int, AMarker*> levelLocations;

	UPROPERTY(BlueprintReadWrite)
		int currentLocationPosition;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float attackDamage;


	UPROPERTY(BlueprintReadWrite)
		AActor* targetedTower;


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

};
