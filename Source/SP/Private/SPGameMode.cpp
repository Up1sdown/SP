// Copyright Epic Games, Inc. All Rights Reserved.

#include "SPGameMode.h"
#include "SPCharacter.h"
#include "SPEnemyBase.h"
#include "SPWeaponSpawner.h"
#include "SPPlayerState.h"
#include "SPSaveGame.h"
#include "NavigationSystem.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "UObject/ConstructorHelpers.h"

ASPGameMode::ASPGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Blueprints/BP_SPCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	bShouldSpawnEnemies = false;
	bShouldSpawnWeapons = false;
	PrimaryActorTick.bCanEverTick = true;
}

void ASPGameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (bShouldSpawnEnemies)
	{
		TryToSpawnEnemies();
	}

	if (bShouldSpawnWeapons)
	{
		TryToSpawnWeapons();
	}
}

void ASPGameMode::OnActorKilled(AActor* Victim, AActor* Killer)
{
	ASPCharacter* Player = Cast<ASPCharacter>(Victim);
	if (Player)
	{	
		StopGame();
		SaveRecord();
	}
	
	// Give Credits for kill
	APawn* KillerPawn = Cast<APawn>(Killer);
	// Don't credit kills of self
	if (KillerPawn && KillerPawn != Victim)
	{
		// Only Players will have a 'PlayerState' instance, bots have nullptr
		ASPPlayerState* PS = KillerPawn->GetPlayerState<ASPPlayerState>();
		if (PS)
		{			
			PS->AddScore(ScorePerKill);
		}
	}
}

void ASPGameMode::SpawnEnemy()
{
	if (EnemyToSpawn)
	{
		ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
		FVector PlayerCharacterLocation = PlayerCharacter->GetActorLocation();

		FVector SpawnLocation = FindRandomReachablePointInRadius(PlayerCharacterLocation, MaxEnemySpawnRadius);
		FRotator SpawnRotation = UKismetMathLibrary::FindLookAtRotation(SpawnLocation, PlayerCharacterLocation);

		if (FVector::Dist(SpawnLocation, PlayerCharacterLocation) >= MinEnemySpawnRadius)
		{
			GetWorld()->SpawnActor<ASPEnemyBase>(EnemyToSpawn, SpawnLocation, SpawnRotation);

			EnemySpawnRate = FMath::Clamp(EnemySpawnRate - EnemySpawnRateDelta, MinEnemySpawnRate, EnemySpawnRate);
		}
		else
		{
			GetWorld()->GetTimerManager().ClearTimer(EnemySpawnTimerHandler);
		}
	}	
}

void ASPGameMode::TryToSpawnEnemies()
{
	if (!GetWorld()->GetTimerManager().IsTimerActive(EnemySpawnTimerHandler))
	{
		GetWorld()->GetTimerManager().SetTimer(EnemySpawnTimerHandler, this, &ASPGameMode::SpawnEnemy, EnemySpawnRate, false);
	}
}

void ASPGameMode::TryToSpawnWeapons()
{
	if (!GetWorld()->GetTimerManager().IsTimerActive(WeaponSpawnTimerHandler))
	{
		GetWorld()->GetTimerManager().SetTimer(WeaponSpawnTimerHandler, this, &ASPGameMode::SpawnWeapon, WeaponSpawnRate, false);
	}	
}

void ASPGameMode::SpawnWeapon()
{
	if (WeaponsToSpawn.Num() > 0)
	{
		ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
		FVector PlayerCharacterLocation = PlayerCharacter->GetActorLocation();

		FVector SpawnLocation = FindRandomReachablePointInRadius(PlayerCharacterLocation, MaxWeaponSpawnRadius);
		FRotator SpawnRotation = FRotator::ZeroRotator;
		
		int32 RandIndex = FMath::RandRange(0, WeaponsToSpawn.Num()-1);
		
		GetWorld()->SpawnActor<ASPWeaponSpawner>(WeaponsToSpawn[RandIndex], SpawnLocation, SpawnRotation);
		
	}

}

void ASPGameMode::SaveRecord()
{
	ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	ASPPlayerState* PlayerState = Cast<ASPPlayerState>(PlayerCharacter->GetPlayerState());
	USPSaveGame* SaveGameInstance = Cast<USPSaveGame>(UGameplayStatics::CreateSaveGameObject(USPSaveGame::StaticClass()));
	SaveGameInstance->RecordScore = PlayerState->GetRecordScore();
	UGameplayStatics::SaveGameToSlot(SaveGameInstance, TEXT("RecordSlot"), 0);
}

void ASPGameMode::LoadRecord()
{
	ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	ASPPlayerState* PlayerState = Cast<ASPPlayerState>(PlayerCharacter->GetPlayerState());
	USPSaveGame* SaveGameInstance = Cast<USPSaveGame>(UGameplayStatics::CreateSaveGameObject(USPSaveGame::StaticClass()));

	SaveGameInstance = Cast<USPSaveGame>(UGameplayStatics::LoadGameFromSlot(TEXT("RecordSlot"), 0));
	if (SaveGameInstance)
	{
		PlayerState->SetRecordScore(SaveGameInstance->RecordScore);
	}	
}

void ASPGameMode::BeginPlay()
{
	Super::BeginPlay();
	LoadRecord();
	StartGame();
}

FVector ASPGameMode::FindRandomReachablePointInRadius(FVector &Origin, float Radius)
{
	UNavigationSystemV1* NavigationArea = UNavigationSystemV1::GetCurrent(GetWorld());
	

	FNavLocation ResultNavLocation;
	NavigationArea->GetRandomReachablePointInRadius(Origin, Radius, ResultNavLocation);

	return ResultNavLocation.Location;
}

void ASPGameMode::StartGame()
{	
	bShouldSpawnEnemies = true;
	bShouldSpawnWeapons = true;	
}

void ASPGameMode::StopGame()
{
	bShouldSpawnEnemies = false;
	bShouldSpawnWeapons = false;
	GetWorld()->GetTimerManager().ClearTimer(EnemySpawnTimerHandler);
	GetWorld()->GetTimerManager().ClearTimer(WeaponSpawnTimerHandler);

}
