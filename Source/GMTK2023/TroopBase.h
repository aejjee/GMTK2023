// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"


#include "LocationMarker.h"

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
		ALocationMarker* targetLocation;

	UPROPERTY(BlueprintReadWrite)
		ALocationMarker* nextLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float attackDamage;

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


};
