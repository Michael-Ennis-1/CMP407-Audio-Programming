// Fill out your copyright notice in the Description page of Project Settings.

#include "AudioAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "AudioEnemy.h"

AAudioAIController::AAudioAIController(const FObjectInitializer& ObjectInitializer) : bIsChasingPlayer(false)
{
}

void AAudioAIController::BeginPlay()
{
	Super::BeginPlay();

	UWorld* World = GetWorld();
	if (ensure(World))
	{
		APlayerController* PlayerController = UGameplayStatics::GetPlayerController(World, 0);
		if (ensure(PlayerController))
		{
			PlayerActor = PlayerController->GetPawn();
		}
	}

	if (ensure(PlayerActor) && ensure(Blackboard))
	{
		Blackboard->SetValueAsObject(FName("PlayerActor"), PlayerActor);
	}

	APawn* PossessedEnemy = GetPawn();
	if (ensure(PossessedEnemy))
	{
		AAudioEnemy* AudioEnemy = Cast<AAudioEnemy>(PossessedEnemy);
		if (ensure(AudioEnemy))
		{
			AudioEnemy->OnEnemyStartedChasing.AddUniqueDynamic(this, &AAudioAIController::StartChasingPlayer);
			AudioEnemy->OnEnemyStoppedChasing.AddUniqueDynamic(this, &AAudioAIController::StopChasingPlayer);
		}
	}
}

void AAudioAIController::StartChasingPlayer()
{
	bIsChasingPlayer = true;
	if (ensure(Blackboard))
	{
		Blackboard->SetValueAsBool(FName("bIsChasingPlayer"), bIsChasingPlayer);
	}
}

void AAudioAIController::StopChasingPlayer()
{
	bIsChasingPlayer = false;
	if (ensure(Blackboard))
	{
		Blackboard->SetValueAsBool(FName("bIsChasingPlayer"), bIsChasingPlayer);
	}
}
