// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_FireProjectile.generated.h"

class UAudioEnemyProjectileComponent;

UCLASS()
class CMP407PROJECT_API UBTTask_FireProjectile : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	// Determine if bullet is ready to fire, then fire projectile
	bool ProcessFiringLogic(UAudioEnemyProjectileComponent* InProjectileComponent, AActor* InTarget, float InDeltaTime);

	// Compartmentalize bullet audio from main firing logic
	void PlayBulletAudio(APawn* InOwnerPawn);

};
