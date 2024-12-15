// Fill out your copyright notice in the Description page of Project Settings.


#include "AudioPlayerCharacter.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "AudioPlayerComponent.h"
#include "Components/BoxComponent.h"

AAudioPlayerCharacter::AAudioPlayerCharacter()
{
	BulletPassbyBoxCollider = CreateDefaultSubobject<UBoxComponent>("Bullet Passby Collider");
	if (ensure(BulletPassbyBoxCollider))
	{
		BulletPassbyBoxCollider->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
	}
}

void AAudioPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	UCapsuleComponent* CapsuleCollider = GetCapsuleComponent();
	if (ensure(CapsuleCollider) && ensure(BulletPassbyBoxCollider))
	{
		CapsuleCollider->OnComponentBeginOverlap.AddUniqueDynamic(this, &AAudioPlayerCharacter::OnBeginCharacterOverlap);
		BulletPassbyBoxCollider->OnComponentBeginOverlap.AddUniqueDynamic(this, &AAudioPlayerCharacter::OnBeginPassbyOverlap);
	}
}

void AAudioPlayerCharacter::OnBeginCharacterOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (ensure(OtherActor))
	{
		if (OtherActor->GetComponentByClass<UProjectileMovementComponent>())
		{
			OtherActor->Destroy();

			UAudioPlayerComponent* AudioPlayerComponent = GetComponentByClass<UAudioPlayerComponent>();
			if (AudioPlayerComponent)
			{
				AudioPlayerComponent->PlayHitByBullet();
			}
		}
	}
}

void AAudioPlayerCharacter::OnBeginPassbyOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (ensure(OtherActor))
	{
		UProjectileMovementComponent* ProjectileMovementComponent = OtherActor->GetComponentByClass<UProjectileMovementComponent>();

		if (ProjectileMovementComponent)
		{
			if (!PredictProjectileCollision(OtherActor, ProjectileMovementComponent))
			{
				UAudioPlayerComponent* AudioPlayerComponent = GetComponentByClass<UAudioPlayerComponent>();
				if (AudioPlayerComponent)
				{
					AudioPlayerComponent->PlayPassbyBullet();
				}
			}
		}
	}
}

bool AAudioPlayerCharacter::PredictProjectileCollision(AActor* InOtherActor, UProjectileMovementComponent* InProjectileMovementComponent)
{
	UWorld* World = GetWorld();
	if (!ensure(InOtherActor) || !ensure(InProjectileMovementComponent) || !ensure(World))
	{
		return false;
	}

	// Box collider will be a cube, so X/Y/Z length should be the same
	float LinetraceLength = BulletPassbyBoxCollider->GetScaledBoxExtent().X;

	// Line trace length of box collider to check if player is hit
	FVector ProjectileDirection = InProjectileMovementComponent->Velocity;
	FVector TargetPosition = InOtherActor->GetActorLocation() + (ProjectileDirection * LinetraceLength);

	FHitResult OutHit;
	World->LineTraceSingleByChannel(OutHit, InOtherActor->GetActorLocation(), TargetPosition, ECollisionChannel::ECC_Visibility);
	if (OutHit.bBlockingHit)
	{
		if (OutHit.GetActor() == this)
		{
			// Return true if actor hit is player
			return true;
		}
	}

	// Return false if actor hit is not player or no actor hit
	return false;
}
