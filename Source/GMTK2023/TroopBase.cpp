// Fill out your copyright notice in the Description page of Project Settings.


#include "TroopBase.h"



// Sets default values
ATroopBase::ATroopBase()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	

	health = 100.0f;
}

// Called when the game starts or when spawned
void ATroopBase::BeginPlay()
{
	Super::BeginPlay();



}

// Called every frame
void ATroopBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (health <= 0.0f) {
		Destroy();
	}

}

// Called to bind functionality to input
void ATroopBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);



}


void ATroopBase::DamageHealth(float value) {
	health -= value;
}


