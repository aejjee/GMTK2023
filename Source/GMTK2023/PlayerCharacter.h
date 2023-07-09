// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"

#include "InputAction.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "MyGameModeBase.h"
#include "EnhancedInput/Public/EnhancedInputComponent.h"


#include "Kismet/GameplayStatics.h"

#include "Engine/EngineTypes.h"


#include "Camera/CameraComponent.h"




#include "PlayerCharacter.generated.h"



class ATroopBase;

/**
 * 
 */
UCLASS()
class GMTK2023_API APlayerCharacter : public APaperCharacter
{
	GENERATED_BODY()

public:
	APlayerCharacter();

	UPROPERTY(BlueprintReadWrite)
		UCameraComponent* playerCamera;


	UPROPERTY(BlueprintReadOnly)
		FVector grabStartLocation;

	UPROPERTY(BlueprintReadOnly)
		FVector previousGrabLocation;

	UPROPERTY(BlueprintReadOnly)
		bool grabStarted;

	// The current game mode.
	UPROPERTY(BlueprintReadOnly)
	AMyGameModeBase* CurrentGameMode;


	UPROPERTY(BlueprintReadWrite)
		TSubclassOf<ATroopBase> spawnType;
	UPROPERTY(BlueprintReadWrite)
		float spawnTimer;



	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Controls")
		UInputAction* leftClickAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Controls")
		UInputAction* leftReleaseAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Controls")
		UInputAction* leftDownAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Controls")
		UInputAction* rightClickAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Controls")
		UInputAction* rightDownAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Controls")
		UInputAction* lookAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Controls")
		UInputAction* scrollAction;



	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Control Mappings")
		UInputMappingContext* baseControls;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Control Mappings")
		int32 baseControlsPriority = 0;

	UFUNCTION()
		void lookInput(const FInputActionValue& value);

	UFUNCTION()
		void leftClickInput(const FInputActionValue& value);

	UFUNCTION()
		void leftDownInput(const FInputActionValue& value);

	UFUNCTION()
		void leftReleaseInput(const FInputActionValue& value);

	UFUNCTION()
		void rightClickInput(const FInputActionValue& value);

	UFUNCTION()
		void rightDownInput(const FInputActionValue& value);

	UFUNCTION()
		void scrollInput(const FInputActionValue& value);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	// Spawns an enemy at the given location.
	void SpawnEnemy(const FVector& location);

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
};
