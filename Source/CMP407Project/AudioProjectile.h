// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AudioProjectile.generated.h"

class UProjectileMovementComponent;
class UStaticMeshComponent;
class USphereComponent;

UCLASS()
class CMP407PROJECT_API AAudioProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	AAudioProjectile();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ProjectileSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ProjectileLifespan;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UProjectileMovementComponent> ProjectileMovementComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UStaticMeshComponent> ProjectileMeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<USphereComponent> ProjectileSphereCollider;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<USceneComponent> SceneRootComponent;
};
