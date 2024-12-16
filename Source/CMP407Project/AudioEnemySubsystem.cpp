// Fill out your copyright notice in the Description page of Project Settings.


#include "AudioEnemySubsystem.h"
#include "AudioEnemy.h"

void UAudioEnemySubsystem::RegisterAudioEnemy(AAudioEnemy* InEnemy)
{
	// If empty before registering, then player must be getting chased, swap music
	if (RegisteredEnemies.IsEmpty())
	{
		OnStartedChasing.Broadcast();
	}

	if (ensure(InEnemy))
	{
		RegisteredEnemies.Add(InEnemy);
		OnRegisteredEnemy.Broadcast();
	}
}

void UAudioEnemySubsystem::UnRegisterAudioEnemy(AAudioEnemy* InEnemy)
{
	if (ensure(InEnemy))
	{
		RegisteredEnemies.Remove(InEnemy);
		OnUnRegisteredEnemy.Broadcast();
	}

	// If empty after removing last enemy, player no longer being chased, swap music
	if (RegisteredEnemies.IsEmpty())
	{
		OnFinishedChasing.Broadcast();
	}
}

bool UAudioEnemySubsystem::IsCurrentlyRegistered(AAudioEnemy* InEnemy)
{
	if (ensure(InEnemy))
	{
		return RegisteredEnemies.Contains(InEnemy);
	}

	return false;
}

