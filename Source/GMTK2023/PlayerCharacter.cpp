// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"

#include "TroopBase.h"


// Sets default values
APlayerCharacter::APlayerCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	grabStarted = false;
	

	combatMode = false;

	spawnTimer = 0.0f;
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	previousGrabLocation = GetActorLocation();
	grabStartLocation = GetActorLocation();

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


	GetWorld()->GetFirstPlayerController()->SetControlRotation(FVector(0.0f, 1.0f, 0.0f).Rotation());




}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	spawnTimer += DeltaTime;

	//playerCamera->SetWorldRotation((GetActorLocation() - playerCamera->GetComponentLocation()).GetSafeNormal().ToOrientationRotator());
	
	playerCamera->SetRelativeLocation(FVector::ZeroVector);


	GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::White, GetActorLocation().ToString());

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);


	if (UEnhancedInputComponent* playerEnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {

		//GEngine->AddOnScreenDebugMessage(-1, 1.5f, FColor::White, "valid");

		playerEnhancedInput->BindAction(leftDownAction, ETriggerEvent::Triggered, this, &APlayerCharacter::leftDownInput);
		playerEnhancedInput->BindAction(leftReleaseAction, ETriggerEvent::Triggered, this, &APlayerCharacter::leftReleaseInput);

		playerEnhancedInput->BindAction(rightDownAction, ETriggerEvent::Triggered, this, &APlayerCharacter::rightDownInput);


		playerEnhancedInput->BindAction(lookAction, ETriggerEvent::Triggered, this, &APlayerCharacter::lookInput);

		playerEnhancedInput->BindAction(scrollAction, ETriggerEvent::Triggered, this, &APlayerCharacter::scrollInput);

	}




}



void APlayerCharacter::lookInput(const FInputActionValue& value) {

	//turn
	//AddControllerPitchInput(value.Get<FVector2D>().Y * 20.0f);
	//AddControllerYawInput(value.Get<FVector2D>().X * 20.0f);




}



void APlayerCharacter::leftClickInput(const FInputActionValue& value) {

}


void APlayerCharacter::leftDownInput(const FInputActionValue& value) {
	GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::White, "Left Down");


	//check if the cursor is over a timeline
	FHitResult cursorHit;
	//get the cursor hit result
	Cast<APlayerController>(GetController())->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, cursorHit);
	//if the cursor is over anything
	if (cursorHit.bBlockingHit) {
		
		GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::Green, "hit");

		//get the current grab location
		FVector tempLocation = cursorHit.Location;
		tempLocation.Y = GetActorLocation().Y;

		if (!grabStarted) {

			grabStartLocation = tempLocation;
			
			grabStarted = true;
		}
		else {
			SetActorLocation(GetActorLocation() + (grabStartLocation - tempLocation));
		}

		

	}


}


void APlayerCharacter::leftReleaseInput(const FInputActionValue& value) {
	grabStarted = false;
}




void APlayerCharacter::rightClickInput(const FInputActionValue& value) {

}


void APlayerCharacter::rightDownInput(const FInputActionValue& value) {
	GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::White, "Right Down");


	

	APlayerController* playerController = Cast<APlayerController>(GEngine->GetFirstLocalPlayerController(GetWorld()));

	//check if the cursor is over a timeline
	FHitResult cursorHit;
	//get the cursor hit result
	playerController->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, cursorHit);
	
	if (cursorHit.bBlockingHit && spawnTimer > 0.2f && spawnType) {

		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::White, "Spawn");


		spawnTimer = 0.0f;

		FActorSpawnParameters params;
		
		FVector spawnLocation = cursorHit.Location;
		spawnLocation.Y = 10.0f;

		FTransform spawnTransform;
		spawnTransform.SetLocation(spawnLocation);
		spawnTransform.SetRotation(FVector(1.0f, 0.0f, 0.0f).Rotation().Quaternion());

		
		GetWorld()->SpawnActor<ATroopBase>(spawnType, spawnTransform, params);
	}
	


}

void APlayerCharacter::scrollInput(const FInputActionValue& value) {
	playerCamera->OrthoWidth = playerCamera->OrthoWidth * (1.0f - (0.1f * FMath::Sign(value.Get<float>())));
}