// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameModeBase.h"

void AMyGameModeBase::PauseGameButAllowCamera(bool isPaused)
{
	bGamePausedButAllowCamera = isPaused;
}

bool AMyGameModeBase::GetGamePaused()
{
	return bGamePausedButAllowCamera;
}

bool AMyGameModeBase::IsWaveInProgress()
{
	return bCombatMode;
}

void AMyGameModeBase::StartWave()
{
	bCombatMode = true;
}

void AMyGameModeBase::FinishWave()
{
	bCombatMode = false;
}