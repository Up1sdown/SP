// Fill out your copyright notice in the Description page of Project Settings.


#include "SPBFGProjectile.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"


ASPBFGProjectile::ASPBFGProjectile()
{
	DamageRadius = 0.0f;
}

void ASPBFGProjectile::ApplyDamage(AActor* OtherActor)
{
	//Player can't be damaged by own explosion
	TArray<AActor*> IgnoredActors;
	IgnoredActors.Add(GetInstigator());

	UGameplayStatics::ApplyRadialDamage(GetWorld(), Damage, GetActorLocation(), DamageRadius, nullptr, IgnoredActors, nullptr, GetInstigatorController(), true);

	//Drawing explosion area
	DrawDebugSphere(GetWorld(),GetActorLocation(), DamageRadius, 18, FColor::Blue, false, 2, 0U, 5.0f);
}


