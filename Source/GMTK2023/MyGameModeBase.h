// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MyGameModeBase.generated.h"

class ASam;

/**
 * 
 */
UCLASS()
class GMTK2023_API AMyGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

private:
	// Determines whether the game is paused (but still lets the player move the
	// camera around).
	bool bGamePausedButAllowCamera;

	// Determines whether a wave is currently going.
	bool bCombatMode;
	
	// The number of enemies spawned this wave.
	int NumOfEnemies;

public:
	// The amount of currency the player currently has to spend on enemies.
	UPROPERTY(BlueprintReadOnly)
	int CurrentCurrency;

	// The amount of currency the player has at the start of this wave.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int StartingCurrency;

	// The amount of additional currency the player gets at the start of each wave.
	UPROPERTY(EditAnywhere)
	int CurrencyPerWave;

	UPROPERTY(BlueprintReadOnly)
		int wave;

	UPROPERTY(EditAnywhere)
		TSubclassOf<ASam> samClass;

	UPROPERTY(BlueprintReadOnly)
		ASam* sam;


public:

	AMyGameModeBase();
	
	// Gets whether the game is currently paused, returning true if it is.
	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool GetGamePaused();
	
	// Gets whether the current wave is in progress.
	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool IsWaveInProgress();

	// Sets whether the game is paused (but still allow the player to move the
	// camera around).
	UFUNCTION(BlueprintCallable)
	void PauseGameButAllowCamera(bool isPaused);

	// Tells the game to start the next wave.
	UFUNCTION(BlueprintCallable)
	void StartWave();

	// Tells the game that the current wave is over.
	UFUNCTION(BlueprintCallable)
	void FinishWave();

	// Gets the current number of enemies.
	UFUNCTION(BlueprintGetter)
	int GetNumOfEnemies() const;

	// Sets the current number of enemies onscreen. When the number reaches 0,
	// the wave is automatically ended.
	UFUNCTION(BlueprintSetter)
	void SetNumOfEnemies(int newNum);




	UFUNCTION()
		ASam* SpawnSam();

protected:
	virtual void BeginPlay() override;
};
