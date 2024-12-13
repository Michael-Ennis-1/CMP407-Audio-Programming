// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AudioEnemyProjectileComponent.generated.h"

class AAudioProjectile;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable )
class CMP407PROJECT_API UAudioEnemyProjectileComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UAudioEnemyProjectileComponent();

	UFUNCTION(BlueprintCallable)
	void FireProjectile(AActor* InTarget);

protected:
	virtual void BeginPlay() override;

	FVector CalculateProjectileVelocity(AActor* InTarget);

	AAudioProjectile* SpawnProjectile();

	void ApplyProjectileParameters(AAudioProjectile* InProjectile, FVector InProjectileDirection);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AAudioProjectile> ProjectileClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<USceneComponent> ProjectileSpawnTransform;

};
