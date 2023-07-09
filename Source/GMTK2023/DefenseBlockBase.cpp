// Fill out your copyright notice in the Description page of Project Settings.


#include "DefenseBlockBase.h"
#include "PaperFlipbookComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
ADefenseBlockBase::ADefenseBlockBase()
	: BlockCost(10), StartingHealth(100.0f), CurrencyReward(10), Damage(10.0f),
	AttackCooldownTime(1.0f)
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RangeSphere = CreateDefaultSubobject<USphereComponent>(FName("RangeSphere"));
	RangeSphere->SetupAttachment(RootComponent);
	RangeSphere->OnComponentBeginOverlap.AddDynamic(this,
		&ADefenseBlockBase::ActorEnteredAttackRange);
	RangeSphere->OnComponentEndOverlap.AddDynamic(this,
		&ADefenseBlockBase::ActorExitedAttackRange);

	GetCharacterMovement()->GravityScale = 0.0f;


	Tags.Add("Tower");

	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetCapsuleComponent()->SetCapsuleRadius(4.0f);
	GetCapsuleComponent()->SetCapsuleHalfHeight(8.0f);
	IsDead = false;
}

// Called when the game starts or when spawned
void ADefenseBlockBase::BeginPlay()
{
	Super::BeginPlay();
	CurrentGameMode = Cast<AMyGameModeBase>(GetWorld()->GetAuthGameMode());
	GetSprite()->SetFlipbook(IdleAnimation);
	if (Damage > 0)
	{
		GetWorldTimerManager().SetTimer(AttackTimeHandle, this,
			&ADefenseBlockBase::StartAttack, AttackCooldownTime, true);
	}
	CurrentHealth = StartingHealth;
}

void ADefenseBlockBase::StartAttack()
{
	for (int i = 0; i < EnemiesInRange.Num(); i++)
	{
		if (EnemiesInRange[i] == nullptr)
		{
			EnemiesInRange.RemoveAt(i);	
		}
	}
	if (EnemiesInRange.Num() > 0 && !CurrentGameMode->GetGamePaused() &&
		CurrentGameMode->IsWaveInProgress() && !IsDead)
	{
		Attack();
		GetSprite()->SetFlipbook(AttackAnimation);
		GetWorldTimerManager().SetTimer(IdleTimeHandle, this,
			&ADefenseBlockBase::ResetToIdleAnimation,
			GetAnimationDuration(AttackAnimation), false);
	}
	
}

void ADefenseBlockBase::ActorEnteredAttackRange(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                                UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ATroopBase* enemy = Cast<ATroopBase>(OtherActor);
	if (enemy == nullptr)
	{
		return;
	}
	EnemiesInRange.Add(enemy);
	enemy->towerTargets.Add(this);


}

void ADefenseBlockBase::ActorExitedAttackRange(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	ATroopBase* enemy = Cast<ATroopBase>(OtherActor);
	if (enemy == nullptr)
	{
		return;
	}
	EnemiesInRange.Remove(enemy);
	enemy->towerTargets.Remove(this);



}

void ADefenseBlockBase::ResetToIdleAnimation()
{
	GetSprite()->SetFlipbook(IdleAnimation);
}

float ADefenseBlockBase::GetAnimationDuration(UPaperFlipbook* animation)
{
	if (animation == nullptr)
	{
		return 0.0f;
	}
	return animation->GetTotalDuration() * (1 / GetSprite()->GetPlayRate());
}

// Called every frame
void ADefenseBlockBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ADefenseBlockBase::DamageBlock(int damage)
{
	if (IsDead)
	{
		return;
	}
	CurrentHealth -= damage;
	IsDead = (CurrentHealth <= 0);
	if (IsDead)
	{
		CurrentGameMode->SetNumOfTowers(CurrentGameMode->GetNumOfTowers() - 1);
		CurrentGameMode->StartingCurrency += CurrencyReward;
		GetSprite()->SetFlipbook(DestroyedAnimation);
		SetLifeSpan(DestroyedAnimation->GetTotalDuration());
	}
	else
	{
		GetSprite()->SetFlipbook(TakeDamageAnimation);
		GetWorldTimerManager().SetTimer(HealthCheckTimeHandle, this,
			&ADefenseBlockBase::ResetToIdleAnimation,
			GetAnimationDuration(TakeDamageAnimation), false);
	}
}
