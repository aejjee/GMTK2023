// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameModeBase.h"

void AMyGameModeBase::PauseGameButAllowCamera(bool isPaused)
{
	bGamePausedButAllowCamera = isPaused;
}

AMyGameModeBase::AMyGameModeBase()
	: NumOfEnemies(0), CurrentCurrency(50), MaxCurrency(50)
{
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
	MaxCurrency += CurrencyPerWave;
	CurrentCurrency = MaxCurrency;
}

int AMyGameModeBase::GetNumOfEnemies() const
{
	return NumOfEnemies;
}

void AMyGameModeBase::SetNumOfEnemies(int newNum)
{
	NumOfEnemies = newNum;
	if (NumOfEnemies <= 0)
	{
		FinishWave();
	}
}
