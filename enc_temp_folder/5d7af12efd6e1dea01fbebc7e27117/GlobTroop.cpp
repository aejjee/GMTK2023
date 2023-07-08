// Fill out your copyright notice in the Description page of Project Settings.


#include "GlobTroop.h"

// Sets default values
AGlobTroop::AGlobTroop()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	
}

// Called when the game starts or when spawned
void AGlobTroop::BeginPlay()
{
	Super::BeginPlay();



}

// Called every frame
void AGlobTroop::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (health <= 0.0f) {
		Destroy();
	}

}

// Called to bind functionality to input
void AGlobTroop::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);



}