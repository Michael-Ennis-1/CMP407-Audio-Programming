// Fill out your copyright notice in the Description page of Project Settings.


#include "AudioProjectileSubsystem.h"

void UAudioProjectileSubsystem::InformPlayedWhizzEffect()
{
	UWorld* World = GetWorld();
	if (ensure(World))
	{
		if (!World->GetTimerManager().IsTimerActive(ResetTimer))
		{
			World->GetTimerManager().SetTimer(ResetTimer, this, &UAudioProjectileSubsystem::TimerCallback, TimeBetweenWhizzEffects);
			bCanPlayWhizz = false;
		}
	}
}

bool UAudioProjectileSubsystem::CanPlayWhizzEffect()
{
	return bCanPlayWhizz;
}

void UAudioProjectileSubsystem::TimerCallback()
{
	bCanPlayWhizz = true;
}
