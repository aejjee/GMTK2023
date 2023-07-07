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
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Music")
	float MusicVolume = 1.0;

	// The track that plays in the main menu.
	UPROPERTY(EditAnywhere, Category="Music")
	USoundBase* MainMenuMusicTrack;
	
	// The list of music tracks.
	UPROPERTY(EditAnywhere, Category="Music")
	TArray<USoundBase*> InGameMusicTracks;

	void Init() override;

	// Updates the music volume.
	UFUNCTION(BlueprintCallable, Category="Music")
	void SetMusicVolume(float volume);
	
	UFUNCTION(BlueprintCallable, Category="Music")
	void PlayMainMenuMusic();
	
	// Starts playing music
	UFUNCTION(BlueprintCallable, Category="Music")	
	void PlayMusic();

	UFUNCTION(BlueprintCallable, Category="Music")
	void PlayMusicTrack(USoundBase* track);
	
	// Pauses the music
	UFUNCTION(BlueprintCallable, Category="Music")
	void PauseMusic();

	// Go to the next music track
	UFUNCTION(BlueprintCallable, Category="Music")
	void GoToNextMusicTrack();

	// Gets the currently playing music track.
	UFUNCTION(BlueprintCallable, BlueprintPure, Category="Music")
	USoundBase* GetNextMusicTrack();
	
private:
	UPROPERTY()
	USoundBase* CurrentMusicTrack;

	UPROPERTY()
	UAudioComponent* CurrentAudioComponent;
	
	// Used to start the next track after this one finishes.
	TScriptDelegate<FWeakObjectPtr> TrackFinished;

};
