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
	// Sets default values for this pawn's properties
	AAudioEnemy();

	FOnGenericEnemyEvent OnEnemyStartedChasing;
	FOnGenericEnemyEvent OnEnemyStoppedChasing;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UAudioEnemySubsystem* GetAudioEnemySubsystem();

	UFUNCTION()
	void TargetPerceptionUpdated(AActor* InActor, FAIStimulus InStimulus);

	TObjectPtr<AActor> PlayerActor;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TObjectPtr<UAIPerceptionComponent> PerceptionComponent;
};
