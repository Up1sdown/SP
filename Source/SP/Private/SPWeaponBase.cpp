// Fill out your copyright notice in the Description page of Project Settings.


#include "SPWeaponBase.h"
#include "SPProjectileBase.h"
#include "TimerManager.h"
#include "Components/ArrowComponent.h"



// Sets default values
ASPWeaponBase::ASPWeaponBase()
{	
	FakeRoot = CreateDefaultSubobject<USceneComponent>(TEXT("FakeRoot"));
	FakeRoot->SetupAttachment(RootComponent);
	
	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponMesh"));
	WeaponMesh->SetupAttachment(FakeRoot);
	
	Muzzle = CreateDefaultSubobject<UArrowComponent>(TEXT("Muzzle"));
	Muzzle->SetupAttachment(FakeRoot);

	FireRate = 0.0f;
	Ammo = 0;
	bIsFiring = false;
}

void ASPWeaponBase::OnFire()
{
	if (Ammo > 0)
	{
		if (ProjectileClass)
		{
			UWorld* World = GetWorld();
			if (World)
			{
				FTransform SpawnTransform = Muzzle->GetComponentTransform();

				APawn* SpawnInstigator = Cast<APawn>(GetParentActor());
				ASPProjectileBase* SpawnedProjectile = World->SpawnActorDeferred<ASPProjectileBase>(ProjectileClass, SpawnTransform, this, SpawnInstigator, ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
				if (IsValid(SpawnedProjectile))
				{
					Ammo--;
					OnAmmoChanged.Broadcast(Ammo);
					SpawnedProjectile->Damage = WeaponDamage;
					SpawnedProjectile->FinishSpawning(SpawnTransform, true);
				}
			}
		}
	}	
}

void ASPWeaponBase::StopFiring()
{
	bIsFiring = false;
	GetWorld()->GetTimerManager().ClearTimer(FireRateTimerHandler);
}

void ASPWeaponBase::AfterFire()
{

}

void ASPWeaponBase::TryToFire()
{
	if (!bIsFiring)
	{
		bIsFiring = true;
		GetWorld()->GetTimerManager().SetTimer(FireRateTimerHandler, this, &ASPWeaponBase::OnFire, FireRate, true, 0.0f);
	}
}


