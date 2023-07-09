// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"

#include "FogOfWarCloud.h"
#include "TroopBase.h"


// Sets default values
APlayerCharacter::APlayerCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	grabStarted = false;
	spawnTimer = 0.0f;
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	CurrentGameMode = Cast<AMyGameModeBase>(GetWorld()->GetAuthGameMode());

	previousGrabLocation = GetActorLocation();
	grabStartLocation = GetActorLocation();

	//camera->ProjectionMode = ECameraProjectionMode::Orthographic;
	//camera->OrthoWidth = 1000.0f;
	//camera->AspectRatio = 1.0f;

	//camera->SetRelativeLocation(FVector::ZeroVector);

	Cast<APlayerController>(GetController())->bEnableMouseOverEvents = true;



	if (APlayerController* playerController = Cast<APlayerController>(GetController())) {
		UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(playerController->GetLocalPlayer());

		FString name = playerController->GetName();
		UE_LOG(LogTemp, Warning, TEXT("Player Base Setting Up: %s"), *name);

		if (Subsystem) {
			Subsystem->ClearAllMappings();

			Subsystem->AddMappingContext(baseControls, baseControlsPriority);
		}
	}
	GetWorld()->GetFirstPlayerController()->SetControlRotation(FVector(0.0f, 1.0f, 0.0f).Rotation());
}

void APlayerCharacter::SpawnEnemy(const FVector& location)
{
	if (CurrentGameMode->IsWaveInProgress() || CurrentGameMode->GetGamePaused())
	{
		return;
	}
	int spawnCost = spawnType->GetDefaultObject<ATroopBase>()->SpawnCost;
	if (CurrentGameMode->CurrentCurrency < spawnCost)
	{
		return;
	}
	CurrentGameMode->CurrentCurrency -= spawnCost;
	CurrentGameMode->SetNumOfEnemies(CurrentGameMode->GetNumOfEnemies() + 1);
	
	spawnTimer = 0.0f;
	
	FActorSpawnParameters params;
	FVector spawnLocation = location;
	spawnLocation.Y = 0.0f;
	
	FTransform spawnTransform;
	spawnTransform.SetLocation(spawnLocation);
	spawnTransform.SetRotation(FVector(1.0f, 0.0f, 0.0f).Rotation().Quaternion());

	GetWorld()->SpawnActor<ATroopBase>(spawnType, spawnTransform, params);


	if (spawnCue) {
		UGameplayStatics::PlaySound2D(GetWorld(), spawnCue);
	}

}

void APlayerCharacter::CreateLocationMarker(const FVector& location)
{
	FActorSpawnParameters params;
	FVector spawnLocation = location;
	spawnLocation.Y = 0.0f;
	
	FTransform spawnTransform;
	spawnTransform.SetLocation(spawnLocation);
	spawnTransform.SetRotation(FVector(1.0f, 0.0f, 0.0f).Rotation().Quaternion());

	AMarker* marker = GetWorld()->SpawnActor<AMarker>(MarkerType, spawnTransform, params);
	if (marker == nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, FString("Location marker is null pointer")); 
		return;
	}
	FString tag = FString("PlayerOverride");
	marker->markerSpecialty = tag;

	TArray<AActor*> enemies;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATroopBase::StaticClass(), enemies);
	for (int i = 0; i < enemies.Num(); i++)
	{
		ATroopBase* enemy = Cast<ATroopBase>(enemies[i]);
		if (enemy != nullptr)
		{
			enemy->OverrideLocationMarker(marker);
		}
	}
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	spawnTimer += DeltaTime;

	//playerCamera->SetWorldRotation((GetActorLocation() - playerCamera->GetComponentLocation()).GetSafeNormal().ToOrientationRotator());
	
	playerCamera->SetRelativeLocation(FVector::ZeroVector);
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);


	if (UEnhancedInputComponent* playerEnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {

		playerEnhancedInput->BindAction(leftDownAction, ETriggerEvent::Triggered, this, &APlayerCharacter::leftDownInput);
		playerEnhancedInput->BindAction(leftReleaseAction, ETriggerEvent::Triggered, this, &APlayerCharacter::leftReleaseInput);

		playerEnhancedInput->BindAction(rightDownAction, ETriggerEvent::Triggered, this, &APlayerCharacter::rightDownInput);
		playerEnhancedInput->BindAction(rightClickAction, ETriggerEvent::Triggered, this, &APlayerCharacter::rightClickInput);


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
	//check if the cursor is over a timeline
	FHitResult cursorHit;
	//get the cursor hit result
	Cast<APlayerController>(GetController())->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, cursorHit);
	//if the cursor is over anything
	if (cursorHit.bBlockingHit) {
		
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
	APlayerController* playerController = Cast<APlayerController>(GEngine->GetFirstLocalPlayerController(GetWorld()));
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, FString("Right mouse click"));
	//check if the cursor is over a timeline
	FHitResult cursorHit;
	//get the cursor hit result
	playerController->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, cursorHit);
	
	if (CurrentGameMode->IsWaveInProgress())
	{
		if (cursorHit.bBlockingHit)
		{
			CreateLocationMarker(cursorHit.Location);	
		}
	}
	else
	{
		AFogOfWarCloud* fogReference = Cast<AFogOfWarCloud>(cursorHit.GetActor());
		if (fogReference != nullptr)
		{
			// We shouldn't spawn enemies in the fog of war zone.
			return;
		}
	
		if (cursorHit.bBlockingHit && spawnTimer > 0.2f && spawnType)
		{
			SpawnEnemy(cursorHit.Location);
		}
	}
}

// change to right click input
void APlayerCharacter::rightDownInput(const FInputActionValue& value) {
}

void APlayerCharacter::scrollInput(const FInputActionValue& value) {
	playerCamera->OrthoWidth = playerCamera->OrthoWidth * (1.0f - (0.1f * FMath::Sign(value.Get<float>())));
}