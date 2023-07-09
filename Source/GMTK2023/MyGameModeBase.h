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

	// The number of towers in this level.
	int NumOfTowers;

	// The current wave count.
	int CurrentWaveCount;

	// The max wave count.
	int MaxWaveCount;

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

	// Gets the current number of towers
	UFUNCTION(BlueprintCallable, BlueprintPure)
	int GetNumOfTowers() const;

	// Sets the current number of towers onscreen. When the number reaches 0,
	// the level is automatically completed.
	UFUNCTION(BlueprintCallable)
	void SetNumOfTowers(int newNum);

	// Gets the current wave count
	UFUNCTION(BlueprintCallable, BlueprintPure)
	int GetCurrentWaveCount();

	// Gets the max wave count
	UFUNCTION(BlueprintCallable, BlueprintPure)
	int GetMaxWaveCount();
	
	// Sets the max wave count
	UFUNCTION(BlueprintCallable)
	void SetMaxWaveCount(int newCount);
	
	// Gets whether the game is currently paused, returning true if it is.
	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool GetGamePaused();
	
	// Gets whether the current wave is in progress.
	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool IsWaveInProgress();

	// Returns true if a wave can be started.
	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool CanStartWave();

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
