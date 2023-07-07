// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"

#include "InputAction.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInput/Public/EnhancedInputComponent.h"


#include "Kismet/GameplayStatics.h"

#include "Engine/EngineTypes.h"


#include "PlayerCharacter.generated.h"

/**
 * 
 */
UCLASS()
class GMTK2023_API APlayerCharacter : public APaperCharacter
{
	GENERATED_BODY()

public:
	APlayerCharacter();










	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Controls")
		UInputAction* leftClickAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Controls")
		UInputAction* leftDownAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Controls")
		UInputAction* rightClickAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Controls")
		UInputAction* rightDownAction;



	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Control Mappings")
		UInputMappingContext* baseControls;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Control Mappings")
		int32 baseControlsPriority = 0;



	UFUNCTION()
		void leftClickInput(const FInputActionValue& value);

	UFUNCTION()
		void leftDownInput(const FInputActionValue& value);

	UFUNCTION()
		void rightClickInput(const FInputActionValue& value);

	UFUNCTION()
		void rightDownInput(const FInputActionValue& value);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
};
