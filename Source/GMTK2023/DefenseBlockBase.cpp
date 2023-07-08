// Fill out your copyright notice in the Description page of Project Settings.


#include "DefenseBlockBase.h"
#include "PaperFlipbookComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
ADefenseBlockBase::ADefenseBlockBase()
	: BlockCost(10), Health(100.0f), Damage(10.0f), AttackCooldownTime(1.0f)
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
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetCapsuleComponent()->SetCapsuleRadius(4.0f);
	GetCapsuleComponent()->SetCapsuleHalfHeight(8.0f);
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
		CurrentGameMode->IsWaveInProgress())
	{
		Attack();
		GetSprite()->SetFlipbook(AttackAnimation);
		GetWorldTimerManager().SetTimer(IdleTimeHandle, this,
			&ADefenseBlockBase::ResetToIdleAnimation, AttackAnimation->GetTotalDuration(), false);
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
}

void ADefenseBlockBase::CheckRemainingHealth()
{
	if (Health <= 0)
	{
		GetSprite()->SetFlipbook(DestroyedAnimation);
		SetLifeSpan(5.0f);
	}
	else
	{
		GetSprite()->SetFlipbook(IdleAnimation);
	}
}

void ADefenseBlockBase::ResetToIdleAnimation()
{
	GetSprite()->SetFlipbook(IdleAnimation);
}

// Called every frame
void ADefenseBlockBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ADefenseBlockBase::DamageBlock(int damage)
{
	Health -= damage;
	GetSprite()->SetFlipbook(TakeDamageAnimation);
	GetWorldTimerManager().SetTimer(HealthCheckTimeHandle, this,
		&ADefenseBlockBase::CheckRemainingHealth,
		TakeDamageAnimation->GetTotalDuration(), false);
}
