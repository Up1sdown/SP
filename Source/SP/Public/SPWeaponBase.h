// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SPWeaponBase.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAmmoChanged, uint8, NewValue);

class ASPProjectileBase;

UCLASS()
class SP_API ASPWeaponBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASPWeaponBase();

protected:

	

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attributes")
	TSubclassOf<ASPProjectileBase> ProjectileClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = CharacterMesh, meta = (AllowPrivateAccess = "true"))
	class USceneComponent* FakeRoot;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* WeaponMesh;

	UPROPERTY(EditAnywhere, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UArrowComponent* Muzzle;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attributes")
	float FireRate;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attributes")
	uint8 Ammo;

	UPROPERTY(BlueprintAssignable, Category = "Attributes")
	FOnAmmoChanged OnAmmoChanged;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attributes")
	float WeaponDamage;

	UFUNCTION(BlueprintCallable, Category = "Attributes")
	void OnFire();

	UFUNCTION(BlueprintCallable, Category = "Attributes")
	void AfterFire();

	FTimerHandle FireRateTimerHandler;

	bool bIsFiring;

public:

	FORCEINLINE uint8 GetAmmo() const { return Ammo; }

	UFUNCTION(BlueprintCallable, Category = "Attributes")
	void StopFiring();

	UFUNCTION(BlueprintCallable, Category = "Attributes")
	void TryToFire();

};
