// Fill out your copyright notice in the Description page of Project Settings.


#include "SPPlayerState.h"

int32 ASPPlayerState::GetScore() const
{
	return PersonalScore;
}

int32 ASPPlayerState::GetRecordScore() const
{
	return RecordScore;
}

void ASPPlayerState::SetRecordScore(int32 NewScore) 
{
	RecordScore = NewScore;
}


void ASPPlayerState::AddScore(int32 Delta)
{
	PersonalScore += Delta;
	OnScoreChanged.Broadcast(this, PersonalScore, Delta);	
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::FromInt(PersonalScore));
	if (PersonalScore > RecordScore)
	{			
		OnRecordScoreChanged.Broadcast(this, PersonalScore, Delta);
		RecordScore = PersonalScore;
	}
}
