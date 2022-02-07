// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SPProjectileBase.h"
#include "SPBFGProjectile.generated.h"


UCLASS()
class SP_API ASPBFGProjectile : public ASPProjectileBase
{
	GENERATED_BODY()
	
public:
	
	ASPBFGProjectile();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float DamageRadius;

protected:

	virtual void ApplyDamage(AActor* OtherActor) override;

};
