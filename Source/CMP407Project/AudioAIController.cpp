// Fill out your copyright notice in the Description page of Project Settings.

#include "AudioAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

void AAudioAIController::BeginPlay()
{
	Super::BeginPlay();

	UWorld* World = GetWorld();
	if (ensure(World))
	{
		APlayerController* PlayerController = UGameplayStatics::GetPlayerController(World, 0);
		if (ensure(PlayerController))
		{
			AActor* PlayerActor = PlayerController->GetPawn();
			if (ensure(PlayerActor) && ensure(Blackboard))
			{
				Blackboard->SetValueAsObject(FName("PlayerActor"), PlayerActor);
			}
		}
	}
}
