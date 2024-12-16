// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AudioPlayerComponent.generated.h"

class UAudioEnemySubsystem;
class UPhysicalMaterial;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable)
class CMP407PROJECT_API UAudioPlayerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UAudioPlayerComponent();

	UFUNCTION(BlueprintImplementableEvent)
	void PlayFootsteps();

	UFUNCTION(BlueprintImplementableEvent)
	void SwitchFootsteps(AActor* InOtherActor);

	UFUNCTION(BlueprintImplementableEvent)
	void PlayChaseMusic();

	UFUNCTION(BlueprintImplementableEvent)
	void PlayHiddenMusic();

	UFUNCTION(BlueprintImplementableEvent)
	void PlayHitByBullet();

	UFUNCTION(BlueprintImplementableEvent)
	void IncreaseAmountOfEnemiesRTPC();

	UFUNCTION(BlueprintImplementableEvent)
	void DecreaseAmountOfEnemiesRTPC();

protected:
	virtual void BeginPlay() override;

	UAudioEnemySubsystem* GetAudioEnemySubsystem();
};
