// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "SPSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class SP_API USPSaveGame : public USaveGame
{
	GENERATED_BODY()

public:


	UPROPERTY()
	int32 RecordScore;
	
};
