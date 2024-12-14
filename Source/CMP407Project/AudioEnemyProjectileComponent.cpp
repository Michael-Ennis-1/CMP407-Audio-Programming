// Fill out your copyright notice in the Description page of Project Settings.


#include "AudioEnemyProjectileComponent.h"
#include "AudioProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"

UAudioEnemyProjectileComponent::UAudioEnemyProjectileComponent() : MaxReloadTime(5.0f), CurrentReloadTime(MaxReloadTime)
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UAudioEnemyProjectileComponent::BeginPlay()
{
	Super::BeginPlay();
}

FVector UAudioEnemyProjectileComponent::CalculateProjectileDirection(AActor* InTarget)
{
	// Determine projectile direction, based on target 
	AActor* OwningActor = GetOwner();
	if (ensure(InTarget) && ensure(OwningActor))
	{
		FVector TargetLocation = InTarget->GetActorLocation();
		FVector StartLocation = OwningActor->GetActorLocation();
		FVector DirectionVector = TargetLocation - StartLocation;
		DirectionVector.Normalize();

		return DirectionVector;
	}

	return FVector{ 0, 0, 0 };
}

AAudioProjectile* UAudioEnemyProjectileComponent::SpawnProjectile()
{
	// Spawn projectile in the world with a given location and rotation, based on scene component inside enemy BP
	if (ensureMsgf(ProjectileSpawnTransform, TEXT("'ProjectileSpawnTransform' scene component not set")))
	{
		UWorld* World = GetWorld();
		if (ensure(World))
		{
			FVector SpawnLocation = ProjectileSpawnTransform->GetComponentLocation();
			FRotator SpawnRotation = ProjectileSpawnTransform->GetComponentRotation();

			AActor* SpawnedActor = World->SpawnActor(ProjectileClass, &SpawnLocation, &SpawnRotation);

			return Cast<AAudioProjectile>(SpawnedActor);
		}
	}

	return nullptr;
}

void UAudioEnemyProjectileComponent::ApplyProjectileParameters(AAudioProjectile* InProjectile, FVector InProjectileDirection)
{
	// Apply any projectile parameters after spawning projecitle
	if (ensure(InProjectile))
	{
		UProjectileMovementComponent* ProjectileMovementComponent = InProjectile->FindComponentByClass<UProjectileMovementComponent>();
		if (ensure(ProjectileMovementComponent))
		{
			ProjectileMovementComponent->Velocity = InProjectileDirection * InProjectile->ProjectileSpeed;
		}
	}
}

void UAudioEnemyProjectileComponent::FireProjectile(AActor* InTarget)
{
	if (ensure(InTarget))
	{
		FVector ProjectileVelocity = CalculateProjectileDirection(InTarget);

		AAudioProjectile* SpawnedProjectile = SpawnProjectile();

		ApplyProjectileParameters(SpawnedProjectile, ProjectileVelocity);
	}
}

