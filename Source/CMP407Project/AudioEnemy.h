// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AudioEnemy.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnGenericEnemyEvent);

class UAIPerceptionComponent;
class UAudioEnemySubsystem;

struct FAIStimulus;

UCLASS()
class CMP407PROJECT_API AAudioEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	AAudioEnemy();

	// Informs AIController when this enemy starts/stops chasing player
	FOnGenericEnemyEvent OnEnemyStartedChasing;
	FOnGenericEnemyEvent OnEnemyStoppedChasing;

	// Disables enemy when hit by projecile
	void DisableEnemy();

	FOnGenericEnemyEvent OnEnemyDisabled;

protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	UAudioEnemySubsystem* GetAudioEnemySubsystem();

	// Updates whether the player is spotted by this enemy
	UFUNCTION()
	void TargetPerceptionUpdated(AActor* InActor, FAIStimulus InStimulus);

	TObjectPtr<AActor> PlayerActor;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TObjectPtr<UAIPerceptionComponent> PerceptionComponent;
};
