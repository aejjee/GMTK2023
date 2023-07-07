// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/AudioComponent.h"
#include "Engine/GameInstance.h"
#include "MyGameInstance.generated.h"

/**
 * The game instance for the project. Among other things, this class keeps track
 * of the game music.
 */
UCLASS()
class GMTK2023_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:

	// The volume of the music tracks.
	UPROPERTY(EditAnywhere)
	float MusicVolume = 1.0;

	// The list of music tracks.
	UPROPERTY(EditAnywhere)
	TArray<USoundBase*> MusicTracks;

	void Init() override;
	
	// Starts playing music
	UFUNCTION(BlueprintCallable)	
	void PlayMusic();

	// Pauses the music
	UFUNCTION(BlueprintCallable)
	void PauseMusic();

	// Go to the next music track
	UFUNCTION(BlueprintCallable)
	void GoToNextMusicTrack();

	// Gets the currently playing music track.
	UFUNCTION(BlueprintCallable, BlueprintPure)
	USoundBase* GetNextMusicTrack();
	
private:
	UPROPERTY()
	USoundBase* CurrentMusicTrack;

	UPROPERTY()
	UAudioComponent* CurrentAudioComponent;
	
	// Used to start the next track after this one finishes.
	TScriptDelegate<FWeakObjectPtr> TrackFinished;
};
