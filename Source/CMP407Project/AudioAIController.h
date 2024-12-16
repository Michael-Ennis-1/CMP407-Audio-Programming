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

	// Bind to delegate on possessed enemy to update behaviour tree
	UFUNCTION()
	void StartChasingPlayer();

	UFUNCTION()
	void StopChasingPlayer();

	UFUNCTION()
	void DisableBehaviourTree();

protected:
	TObjectPtr<AActor> PlayerActor;

	bool bIsChasingPlayer;
};
