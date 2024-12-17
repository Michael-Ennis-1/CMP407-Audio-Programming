// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "AudioEnemySubsystem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnGenericEnemySubsystemEvent);

class AAudioEnemy;

UCLASS()
class CMP407PROJECT_API UAudioEnemySubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:

	// This subsystem ensures that chased music is playing while at least one enemy is registered, utilizing an event-driven approach, avoiding the update loop entirely.
	// Also sends signals when an enemy is added/removed from system for dynamic music 

	UFUNCTION(BlueprintCallable)
	void RegisterAudioEnemy(AAudioEnemy* InEnemy);

	UFUNCTION(BlueprintCallable)
	void UnRegisterAudioEnemy(AAudioEnemy* InEnemy);

	UFUNCTION(BlueprintCallable)
	bool IsCurrentlyRegistered(AAudioEnemy* InEnemy);

	FOnGenericEnemySubsystemEvent OnFinishedChasing;
	FOnGenericEnemySubsystemEvent OnStartedChasing;

	FOnGenericEnemySubsystemEvent OnRegisteredEnemy;
	FOnGenericEnemySubsystemEvent OnUnRegisteredEnemy;

protected:
	TArray<AAudioEnemy*> RegisteredEnemies;
};
