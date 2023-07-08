// Fill out your copyright notice in the Description page of Project Settings.


#include "DefenseBlockBase.h"

#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
ADefenseBlockBase::ADefenseBlockBase()
	: BlockCost(10), Health(100.0f), Damage(10.0f), AttackCooldownTime(3.0f)
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
}

// Called when the game starts or when spawned
void ADefenseBlockBase::BeginPlay()
{
	Super::BeginPlay();
	if (Damage > 0)
	{
		GetWorldTimerManager().SetTimer(InputTimeHandle, this,
			&ADefenseBlockBase::StartAttack, AttackCooldownTime, true, 0.0f);
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
	Attack();
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

// Called every frame
void ADefenseBlockBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

bool ADefenseBlockBase::DamageBlock(int damage)
{
	Health -= damage;
	if (Health <= 0)
	{
		this->Destroy();
		return true;
	}
	return false;
}
