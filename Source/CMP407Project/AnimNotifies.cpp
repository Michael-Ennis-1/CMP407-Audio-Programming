// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotifies.h"
#include "AudioPlayerComponent.h"

void UFootstepAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	if (MeshComp)
	{
		AActor* OwningActor = MeshComp->GetOwner();
		if (OwningActor)
		{
			UWorld* World = GetWorld();
			if (ensure(World))
			{
				float LinetraceLength = 100.0f;

				FVector TargetPosition = -OwningActor->GetActorUpVector() * LinetraceLength;

				FHitResult OutHit;
				World->LineTraceSingleByChannel(OutHit, OwningActor->GetActorLocation(), TargetPosition, ECollisionChannel::ECC_Visibility);
				
				if (OutHit.bBlockingHit)
				{
					AActor* HitActor = OutHit.GetActor();
					if (HitActor != OwningActor)
					{
						UStaticMeshComponent* HitMesh = HitActor->GetComponentByClass<UStaticMeshComponent>();
						if (ensure(HitMesh))
						{

						}
					}
				}
			}

			UAudioPlayerComponent* AudioComponent = OwningActor->GetComponentByClass<UAudioPlayerComponent>();
			if (AudioComponent)
			{
				AudioComponent->PlayFootsteps();
			}
		}
	}
}
