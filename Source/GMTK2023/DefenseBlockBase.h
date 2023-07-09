// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TroopBase.h"
#include "Components/SphereComponent.h"
#include "PaperCharacter.h"
#include "PaperFlipbook.h"
#include "DefenseBlockBase.generated.h"



class ATowerSpot;

/**
 * 
 */
UCLASS()
class GMTK2023_API ADefenseBlockBase : public APaperCharacter
{
	GENERATED_BODY()
	
public:

	// Sets default values for this actor's properties
	ADefenseBlockBase();

	// This block's name.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Name;
	
	// This block's cost.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int BlockCost;

	// This block's total health.
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float StartingHealth;
	
	// This character's current health
	UPROPERTY(BlueprintReadOnly)
	float CurrentHealth;

	// The damage this block does to enemies (if) it attacks.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Damage;

	// The cooldown time between attacks.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float AttackCooldownTime;

	// A list of enemies that are currently in the attack range.
	UPROPERTY(BlueprintReadWrite)
	TArray<ATroopBase*> EnemiesInRange;
	
	// The sphere used to check if enemies are in range.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USphereComponent* RangeSphere;

	// The animation that plays when this block is idle
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UPaperFlipbook* IdleAnimation;
	
	// The animation that plays when this block attacks.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UPaperFlipbook* AttackAnimation;
	
	// The animation that plays when this block takes damage.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UPaperFlipbook* TakeDamageAnimation;

	// The animation that plays when this block dies.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UPaperFlipbook* DestroyedAnimation;

	// A reference to the current game mode.
	UPROPERTY(BlueprintReadOnly)
	AMyGameModeBase* CurrentGameMode;


	// The spot that this tower is sitting on
	UPROPERTY(BlueprintReadOnly)
		ATowerSpot* towerSpot;

	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Deal damage to this defense block, and returns true if it was killed.
	UFUNCTION(BlueprintCallable)
	void DamageBlock(int DamageAmount);

	// Calls the blueprint attack function to attack an enemy.
	UFUNCTION()
	void StartAttack();

	// Implement in blueprints.
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void Attack();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	
	// Used to run the attack timer
	FTimerHandle AttackTimeHandle;
	
	// Used to run the reset animation timer
	FTimerHandle IdleTimeHandle;
	
	// Used to run the health check timer after taking damage
	FTimerHandle HealthCheckTimeHandle;

	// Used to check whether this block is about to die.
	bool IsDead;
	
	UFUNCTION()
	// Gets called whenever an enemy enters the attack range.
	void ActorEnteredAttackRange(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);

	UFUNCTION()
	// Gets called whenever an enemy enters the attack range.
	void ActorExitedAttackRange(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex);

	// A oneliner that gets called after a certain duration to reset the flipbook
	// to the idle animation
	void ResetToIdleAnimation();

	// Gets the number of seconds for this animation, taking play rate into account.
	float GetAnimationDuration(UPaperFlipbook* animation);
};
