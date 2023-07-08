// Fill out your copyright notice in the Description page of Project Settings.


#include "GlobTroop.h"

// Sets default values
AGlobTroop::AGlobTroop()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	health = 15.0f;
}

// Called when the game starts or when spawned
void AGlobTroop::BeginPlay()
{
	Super::BeginPlay();



}

void AGlobTroop::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AGlobTroop::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);



}