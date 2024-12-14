// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_FireProjectile.h"

#include "AIController.h"
#include "AudioEnemyProjectileComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UBTTask_FireProjectile::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	// Return "InProgress" for now to continuously execute Tick Task every frame
	bNotifyTick = true;
	return EBTNodeResult::InProgress;
}

void UBTTask_FireProjectile::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	UBlackboardComponent* BlackboardComponent = OwnerComp.GetBlackboardComponent();

	// Determine if bullet fires this frame, if so exit task with succeeded otherwise continue this task indefinitely
	AAIController* AIController = OwnerComp.GetAIOwner();
	if (ensure(AIController))
	{
		APawn* OwnerPawn = AIController->GetPawn();
		if (ensure(OwnerPawn))
		{
			UAudioEnemyProjectileComponent* ProjectileComponent = OwnerPawn->GetComponentByClass<UAudioEnemyProjectileComponent>();
			if (ensure(ProjectileComponent) && ensure(BlackboardComponent))
			{
				UObject* PlayerObject = BlackboardComponent->GetValueAsObject(FName("PlayerActor"));
				if (ensure(PlayerObject))
				{
					AActor* PlayerActor = Cast<AActor>(PlayerObject);
					if (ensure(PlayerActor))
					{
						if (ProcessFiringLogic(ProjectileComponent, PlayerActor, DeltaSeconds))
						{
							FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
						}
					}
				}
			}
		}
	}

}

bool UBTTask_FireProjectile::ProcessFiringLogic(UAudioEnemyProjectileComponent* InProjectileComponent, AActor* InTarget, float InDeltaTime)
{
	InProjectileComponent->CurrentReloadTime += InDeltaTime;

	// Fire bullet if current reload time exceeds maximum
	if (InProjectileComponent->CurrentReloadTime >= InProjectileComponent->MaxReloadTime)
	{
		InProjectileComponent->CurrentReloadTime = 0;
		InProjectileComponent->FireProjectile(InTarget);

		return true;
	}

	return false;
}
