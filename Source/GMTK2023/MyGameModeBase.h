// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MyGameModeBase.generated.h"

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

public:
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
};
