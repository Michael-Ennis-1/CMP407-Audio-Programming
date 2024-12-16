// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "AudioProjectileSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class CMP407PROJECT_API UAudioProjectileSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:

	// This subsystem further limits the playrate of whizz sound effects, depending on how recently one has been played.
	// The virtualization of voices has been implemented in Wwise already, but only checks if one is playing, not how
	// long after one has been played, hence the implementation of this custom AudioProjectileSubsystem.

	void InformPlayedWhizzEffect();

	bool CanPlayWhizzEffect();

	void TimerCallback();

	FTimerHandle ResetTimer;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float TimeBetweenWhizzEffects = 0.1f;

protected:
	bool bCanPlayWhizz = true;
};
