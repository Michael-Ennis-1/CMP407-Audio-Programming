// Fill out your copyright notice in the Description page of Project Settings.

#include "AudioAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "AudioEnemy.h"
#include "BrainComponent.h"

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

	APawn* PossessedEnemy = GetPawn();
	if (ensure(PossessedEnemy))
	{
		if (ensure(PlayerActor) && ensure(Blackboard))
		{
			FVector StartLocation = PossessedEnemy->GetActorLocation();

			Blackboard->SetValueAsObject(FName("PlayerActor"), PlayerActor);
			Blackboard->SetValueAsVector(FName("CachedPosition"), StartLocation);
		}

		AAudioEnemy* AudioEnemy = Cast<AAudioEnemy>(PossessedEnemy);
		if (ensure(AudioEnemy))
		{
			// Bind to delegates on possessed enemy to inform behaviour tree if player is spotted
			AudioEnemy->OnEnemyStartedChasing.AddUniqueDynamic(this, &AAudioAIController::StartChasingPlayer);
			AudioEnemy->OnEnemyStoppedChasing.AddUniqueDynamic(this, &AAudioAIController::StopChasingPlayer);

			// Bind to delegate to disable behaviour tree when enemy destroyed, but still playing explosion VFX
			AudioEnemy->OnEnemyDisabled.AddUniqueDynamic(this, &AAudioAIController::DisableBehaviourTree);
		}
	}
}

void AAudioAIController::StartChasingPlayer()
{
	// Set blackboard variable to true when player is being chased
	bIsChasingPlayer = true;
	if (ensure(Blackboard))
	{
		Blackboard->SetValueAsBool(FName("bIsChasingPlayer"), bIsChasingPlayer);
	}
}

void AAudioAIController::StopChasingPlayer()
{
	// Set blackboard variable to false when player is no longer being chased
	bIsChasingPlayer = false;
	if (ensure(Blackboard))
	{
		Blackboard->SetValueAsBool(FName("bIsChasingPlayer"), bIsChasingPlayer);
	}
}

void AAudioAIController::DisableBehaviourTree()
{
	if (ensure(BrainComponent))
	{
		BrainComponent->StopLogic("Destroyed");
	}
}
