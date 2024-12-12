// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AudioAIController.generated.h"

UCLASS()
class CMP407PROJECT_API AAudioAIController : public AAIController
{
	GENERATED_BODY()

	AAudioAIController(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

public:
	virtual void BeginPlay() override;

	UFUNCTION()
	void StartChasingPlayer();

	UFUNCTION()
	void StopChasingPlayer();

protected:
	TObjectPtr<AActor> PlayerActor;

	bool bIsChasingPlayer;
};
