// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LocationMarker.generated.h"

UCLASS()
class GMTK2023_API ALocationMarker : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALocationMarker();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Marker Attributes")
		int markerPosition;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Marker Attributes")
		FString markerSpecialty;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
