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
	: NumOfEnemies(0), CurrentWaveCount(0), MaxWaveCount(5), CurrentCurrency(50),
	StartingCurrency(50)
{
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
		// Win condition code here.
		FinishWave();
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Add the win code here"));	
	}
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

bool AMyGameModeBase::CanStartWave()
{
	return (NumOfEnemies > 0 && !IsWaveInProgress());
}

void AMyGameModeBase::StartWave()
{
	if (IsWaveInProgress())
	{
		return;
	}
	FString count = FString::FromInt(CurrentWaveCount + 1);
	FString message = FString("Wave ").Append(count).Append(": Attack Phase");
	SpawnNotification(message);
	// It's not great for performance but it'll work
	TArray<AActor*> FoundEnemies;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(),
		ADefenseBlockBase::StaticClass(), FoundEnemies);
	SetNumOfTowers(FoundEnemies.Num());
	
	bCombatMode = true;
}

void AMyGameModeBase::FinishWave()
{


	sam->SpawnTowers(CurrentWaveCount);



	bCombatMode = false;
	StartingCurrency += CurrencyPerWave;
	CurrentCurrency = StartingCurrency;
	CurrentWaveCount++;
	if (CurrentWaveCount > MaxWaveCount)
	{
		// Lose condition here
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Add the lose code here"));
	}
	else
	{
		FString count = FString::FromInt(CurrentWaveCount + 1);
		FString message = FString("Wave ").Append(count).Append(": Preparation Phase");
		SpawnNotification(message);
	}
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

	CurrentWaveCount = 0;

	sam->perRoundMoney = 30.0f;
	sam->SpawnTowers(CurrentWaveCount);

	FString count = FString::FromInt(CurrentWaveCount + 1);
	FString message = FString("Wave ").Append(count).Append(": Preparation Phase");
	SpawnNotification(message);
}


ASam* AMyGameModeBase::SpawnSam() {

	FActorSpawnParameters params;

	FTransform spawnTransform;
	spawnTransform.SetLocation(FVector::ZeroVector);
	spawnTransform.SetRotation(FVector(1.0f, 0.0f, 0.0f).Rotation().Quaternion());


	ASam* retSam = GetWorld()->SpawnActor<ASam>(samClass, params);

	return retSam;
}