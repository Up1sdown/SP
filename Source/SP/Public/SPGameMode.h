// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SPGameMode.generated.h"

UCLASS(minimalapi)
class ASPGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ASPGameMode();

	virtual void Tick(float DeltaSeconds) override;

	virtual void OnActorKilled(AActor* Victim, AActor* Killer);

protected:

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class ASPEnemyBase> EnemyToSpawn;

	UPROPERTY(EditDefaultsOnly)
	TArray<TSubclassOf<class ASPWeaponSpawner>> WeaponsToSpawn;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int32 ScorePerKill;

	UPROPERTY(EditDefaultsOnly)
	float MaxWeaponSpawnRadius;

	UPROPERTY(EditDefaultsOnly)
	float MaxEnemySpawnRadius;

	UPROPERTY(EditDefaultsOnly)
	float  MinEnemySpawnRadius;

	UPROPERTY(EditDefaultsOnly)
	float EnemySpawnRate;

	UPROPERTY(EditDefaultsOnly)
	float MinEnemySpawnRate;

	//How fast spawn rate will decrease
	UPROPERTY(EditDefaultsOnly)
	float EnemySpawnRateDelta;

	UPROPERTY(EditDefaultsOnly)
	float WeaponSpawnRate;
	
	UFUNCTION(BlueprintCallable)
	void SpawnEnemy();

	UFUNCTION(BlueprintCallable)
	void TryToSpawnEnemies();

	UFUNCTION(BlueprintCallable)
	void TryToSpawnWeapons();

	UFUNCTION(BlueprintCallable)
	void SpawnWeapon();

	UFUNCTION(BlueprintCallable)
	void SaveRecord();

	UFUNCTION(BlueprintCallable)
	void LoadRecord();

	virtual void BeginPlay() override;

	FTimerHandle EnemySpawnTimerHandler;
	FTimerHandle WeaponSpawnTimerHandler;

	bool bShouldSpawnEnemies;
	bool bShouldSpawnWeapons;

	UFUNCTION(BlueprintCallable)
	FVector FindRandomReachablePointInRadius(FVector& Origin, float Radius);

	UFUNCTION(BlueprintCallable)
	void StartGame();

	UFUNCTION(BlueprintCallable)
	void StopGame();



};



