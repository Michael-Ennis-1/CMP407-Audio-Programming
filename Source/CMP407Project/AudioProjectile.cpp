// Fill out your copyright notice in the Description page of Project Settings.


#include "AudioProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Components/SceneComponent.h"
#include "ProjectileAudioComponent.h"
#include "AudioEnemy.h"
#include "AudioTurretEnemy.h"
#include "AudioPlayerHealthComponent.h"

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
		ProjectileSphereCollider->OnComponentBeginOverlap.AddUniqueDynamic(this, &AAudioProjectile::OnBeginOverlap);
	}

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovementComponent");

	SetLifeSpan(ProjectileLifespan);
}

void AAudioProjectile::BeginPlay()
{
	Super::BeginPlay();
}

void AAudioProjectile::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Check that we've collided with a wall, not another bullet
	if (!OtherActor->GetComponentByClass<UProjectileMovementComponent>() && !(OtherActor == CachedTurretActor))
	{
		// Hide actor, disable collision and play sound effect if collided with wall or other enemy
		if (OtherActor->ActorHasTag(FName("Metal")))
		{
			UProjectileAudioComponent* ProjectileAudioComponent = GetComponentByClass<UProjectileAudioComponent>();
			if (ProjectileAudioComponent)
			{
				DisableProjectile();
				ProjectileAudioComponent->PlayProjectileImpactEffect(FName("Metal"));
			}
		}

		if (OtherActor->ActorHasTag(FName("Actor")))
		{
			UProjectileAudioComponent* ProjectileAudioComponent = GetComponentByClass<UProjectileAudioComponent>();
			if (ProjectileAudioComponent)
			{
				DisableProjectile();
				ProjectileAudioComponent->PlayProjectileImpactEffect(FName("Actor"));
				
				AAudioEnemy* AudioEnemy = Cast<AAudioEnemy>(OtherActor);
				if (AudioEnemy && !OtherActor->IsA<AAudioTurretEnemy>())
				{
					AudioEnemy->DisableEnemy();
				}
			}
		}
	}
}

void AAudioProjectile::DisableProjectile()
{
	SetActorHiddenInGame(true);
	ProjectileMovementComponent->Velocity = FVector(0, 0, 0);
	ProjectileSphereCollider->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	SetLifeSpan(3.0f);
}

