// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"

#include "Kismet/GameplayStatics.h"

USoundBase* UMyGameInstance::GetNextMusicTrack()
{
	int newTrackIndex = FMath::RandRange(0, InGameMusicTracks.Num() - 1);
	if (newTrackIndex < 0)
	{
		return nullptr;
	}
	return InGameMusicTracks[newTrackIndex];
}

void UMyGameInstance::Init()
{
	Super::Init();
}

void UMyGameInstance::SetMusicVolume(float volume)
{
	MusicVolume = volume;
	CurrentAudioComponent->AdjustVolume(1, MusicVolume);
}

void UMyGameInstance::PlayMainMenuMusic()
{
	PlayMusicTrack(MainMenuMusicTrack);
}

void UMyGameInstance::PlayMusic()
{
	if (CurrentAudioComponent == nullptr)
	{
		GoToNextMusicTrack();
	}
	else
	{
		CurrentAudioComponent->SetPaused(false);
	}
}

void UMyGameInstance::PlayMusicTrack(USoundBase* track)
{
	if (track == nullptr)
	{
		return;
	}
	if (CurrentAudioComponent != nullptr)
	{
		CurrentAudioComponent->Stop();
		CurrentAudioComponent->OnAudioFinished.Remove(TrackFinished);
	}
	CurrentAudioComponent = UGameplayStatics::CreateSound2D(GetWorld(), track,
		MusicVolume, 1, 0.0, nullptr, true);
	TrackFinished.BindUFunction(this, "GoToNextMusicTrack");
	CurrentAudioComponent->OnAudioFinished.Add(TrackFinished);
	
	CurrentAudioComponent->Activate();
	CurrentAudioComponent->Play();
}

void UMyGameInstance::PauseMusic()
{
	if (CurrentAudioComponent == nullptr)
	{
		return;
	}
	CurrentAudioComponent->SetPaused(true);
}

void UMyGameInstance::GoToNextMusicTrack()
{
	PlayMusicTrack(GetNextMusicTrack());
}