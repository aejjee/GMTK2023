// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TroopBase.h"
#include "Components/SphereComponent.h"
#include "PaperCharacter.h"
#include "DefenseBlockBase.generated.h"

/**
 * 
 */
UCLASS()
class GMTK2023_API ADefenseBlockBase : public APaperCharacter
{
	GENERATED_BODY()
	
public:

	// This block's name.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Name;
	
	// This block's cost.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int BlockCost;

	// This block's total health.
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Health;

	// The damage this block does to enemies (if) it attacks.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Damage;

	// The cooldown time between attacks.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float AttackCooldownTime;

	// A list of enemies that are currently in the attack range.
	UPROPERTY(BlueprintReadWrite)
	TArray<ATroopBase*> EnemiesInRange;
	
	// Sets default values for this actor's properties
	ADefenseBlockBase();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Deal damage to this defense block, and returns true if it was killed.
	UFUNCTION(BlueprintCallable)
	bool DamageBlock(int damageAmount);

	// The sphere used to check if enemies are in range.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USphereComponent* RangeSphere;

	// Calls the blueprint attack function to attack an enemy.
	void StartAttack();

	// Implement in blueprints.
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void Attack();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	// Gets called whenever an enemy enters the attack range.
	void ActorEnteredAttackRange(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);

	// Gets called whenever an enemy enters the attack range.
	void ActorExitedAttackRange(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex);

	// Used to run the attack timer
	FTimerHandle InputTimeHandle;
};
