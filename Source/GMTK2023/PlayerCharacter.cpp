// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"


// Sets default values
APlayerCharacter::APlayerCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	//camera->ProjectionMode = ECameraProjectionMode::Orthographic;
	//camera->OrthoWidth = 1000.0f;
	//camera->AspectRatio = 1.0f;

	//camera->SetRelativeLocation(FVector::ZeroVector);

	Cast<APlayerController>(GetController())->bEnableMouseOverEvents = true;



	if (APlayerController* playerController = Cast<APlayerController>(GetController())) {
		UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(playerController->GetLocalPlayer());

		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::White, playerController->GetName());
		FString name = playerController->GetName();
		UE_LOG(LogTemp, Warning, TEXT("Player Base Setting Up: %s"), *name);

		if (Subsystem) {
			Subsystem->ClearAllMappings();

			Subsystem->AddMappingContext(baseControls, baseControlsPriority);
		}
	}







}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);


	if (UEnhancedInputComponent* playerEnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {

		//GEngine->AddOnScreenDebugMessage(-1, 1.5f, FColor::White, "valid");

		playerEnhancedInput->BindAction(leftDownAction, ETriggerEvent::Triggered, this, &APlayerCharacter::leftDownInput);


	}




}




void APlayerCharacter::leftClickInput(const FInputActionValue& value) {

}


void APlayerCharacter::leftDownInput(const FInputActionValue& value) {
	GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::White, "Left Down");
}


void APlayerCharacter::rightClickInput(const FInputActionValue& value) {

}


void APlayerCharacter::rightDownInput(const FInputActionValue& value) {

}