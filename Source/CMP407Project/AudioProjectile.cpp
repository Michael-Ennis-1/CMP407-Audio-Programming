// Fill out your copyright notice in the Description page of Project Settings.


#include "AudioProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Components/SceneComponent.h"

AAudioProjectile::AAudioProjectile() : ProjectileSpeed(250.0f), ProjectileLifespan(5.0f)
{
	PrimaryActorTick.bCanEverTick = false;

	SceneRootComponent = CreateDefaultSubobject<USceneComponent>("SceneRootComponent");
	if (ensure(SceneRootComponent))
	{
		SetRootComponent(SceneRootComponent);
	}

	ProjectileMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("ProjectileMeshComponent");
	if (ensure(ProjectileMeshComponent))
	{
		ProjectileMeshComponent->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
	}

	ProjectileSphereCollider = CreateDefaultSubobject<USphereComponent>("ProjectileSphereCollider");
	if (ensure(ProjectileSphereCollider))
	{
		ProjectileSphereCollider->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
	}

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovementComponent");

	SetLifeSpan(ProjectileLifespan);
}

void AAudioProjectile::BeginPlay()
{
	Super::BeginPlay();
}

