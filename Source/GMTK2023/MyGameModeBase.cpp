// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameModeBase.h"

#include "PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"

#include "Sam.h"

void AMyGameModeBase::PauseGameButAllowCamera(bool isPaused)
{
	bGamePausedButAllowCamera = isPaused;
}

AMyGameModeBase::AMyGameModeBase()
	: NumOfEnemies(0), CurrentCurrency(50), StartingCurrency(50)
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

void AMyGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	CurrentCurrency = StartingCurrency;



	sam = SpawnSam();

	wave = 0;

	sam->perRoundMoney = 30.0f;
	sam->SpawnTowers(wave);

}


ASam* AMyGameModeBase::SpawnSam() {

	FActorSpawnParameters params;

	FTransform spawnTransform;
	spawnTransform.SetLocation(FVector::ZeroVector);
	spawnTransform.SetRotation(FVector(1.0f, 0.0f, 0.0f).Rotation().Quaternion());


	ASam* retSam = GetWorld()->SpawnActor<ASam>(samClass, params);

	return retSam;
}