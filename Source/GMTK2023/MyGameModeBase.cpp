// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameModeBase.h"

#include "DefenseBlockBase.h"
#include "PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"

void AMyGameModeBase::PauseGameButAllowCamera(bool isPaused)
{
	bGamePausedButAllowCamera = isPaused;
}

AMyGameModeBase::AMyGameModeBase()
	: NumOfEnemies(0), CurrentWaveCount(0), MaxWaveCount(5), CurrentCurrency(50),
	StartingCurrency(50)
{
}

int AMyGameModeBase::GetCurrentWaveCount()
{
	return CurrentWaveCount;
}

int AMyGameModeBase::GetMaxWaveCount()
{
	return MaxWaveCount;
}

void AMyGameModeBase::SetMaxWaveCount(int newCount)
{
	MaxWaveCount = newCount;
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
	const APlayerCharacter* playerCharacter = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(),0));
	if (playerCharacter == nullptr)
	{
		return;
	}
}

void AMyGameModeBase::FinishWave()
{
	bCombatMode = false;
	StartingCurrency += CurrencyPerWave;
	CurrentCurrency = StartingCurrency;
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

int AMyGameModeBase::GetNumOfTowers() const
{
	return NumOfTowers;
}

void AMyGameModeBase::SetNumOfTowers(int newNum)
{
	NumOfTowers = newNum;
	if (NumOfTowers <= 0)
	{
		// todo: add code for win condition
		FinishWave();
	}
}

void AMyGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	CurrentCurrency = StartingCurrency;

	TArray<AActor*> FoundEnemies;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(),
		ADefenseBlockBase::StaticClass(), FoundEnemies);
	NumOfTowers = FoundEnemies.Num();
}
