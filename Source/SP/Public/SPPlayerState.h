// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "SPPlayerState.generated.h"

// Event Handler for Personal Record Score
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnRecordScoreChanged, ASPPlayerState*, PlayerState, int32, NewScore, int32, OldRecord);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnScoreChanged, ASPPlayerState*, PlayerState, int32, NewScore, int32, Delta);

UCLASS()
class SP_API ASPPlayerState : public APlayerState
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditDefaultsOnly)
	int32 PersonalScore;

	UPROPERTY(EditDefaultsOnly)
	int32 RecordScore;

public:

	UFUNCTION(BlueprintCallable)
	int32 GetScore() const;

	UFUNCTION(BlueprintCallable)
	int32 GetRecordScore() const;

	UFUNCTION(BlueprintCallable)
	void SetRecordScore(int32 NewScore);

	UFUNCTION(BlueprintCallable)
	void AddScore(int32 Delta);

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnScoreChanged OnScoreChanged;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnRecordScoreChanged OnRecordScoreChanged;
	
};
