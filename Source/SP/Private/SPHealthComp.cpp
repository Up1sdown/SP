// Fill out your copyright notice in the Description page of Project Settings.


#include "SPHealthComp.h"
#include "SPGameMode.h"

// Sets default values for this component's properties
USPHealthComp::USPHealthComp()
{
	HealthMax = 100;
	Health = HealthMax;
}


// Called when the game starts
void USPHealthComp::BeginPlay()
{
	Super::BeginPlay();
	AActor* Owner = GetOwner();
	if (Owner)
	{
		Owner->OnTakeAnyDamage.AddDynamic(this, &USPHealthComp::TakeAnyDamage);
	}
}

void USPHealthComp::ApplyHealthChange(AActor* InstigatorActor, float Delta)
{	
	if (!GetOwner()->CanBeDamaged() && Delta < 0.0f)
	{
		return;
	}

	float OldHealth = Health;
	float NewHealth = FMath::Clamp(Health + Delta, 0.0f, HealthMax);

	float ActualDelta = NewHealth - OldHealth;
	
	Health = NewHealth;

	if (ActualDelta != 0.0f)
	{
		OnHealthChanged.Broadcast(InstigatorActor, this, Health, ActualDelta);
	}

	// Died
	if (ActualDelta < 0.0f && Health == 0.0f)
	{
		ASPGameMode* GM = GetWorld()->GetAuthGameMode<ASPGameMode>();
		if (GM)
		{
			GM->OnActorKilled(GetOwner(), InstigatorActor);
		}
	}	
}

void USPHealthComp::TakeAnyDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser)
{		
	ApplyHealthChange(InstigatedBy->GetPawn(), -Damage);
}

