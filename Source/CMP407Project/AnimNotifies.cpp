// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotifies.h"
#include "AudioPlayerComponent.h"

void UFootstepAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	// Play footstep audio event and switch based on physical material of the ground
	if (MeshComp)
	{
		AActor* OwningActor = MeshComp->GetOwner();
		if (OwningActor)
		{
			UWorld* World = OwningActor->GetWorld();
			if (ensure(World))
			{
				float LinetraceLength = 200.0f;
				FVector TargetPosition = -OwningActor->GetActorUpVector() * LinetraceLength;

				FHitResult OutHit;
				World->LineTraceSingleByChannel(OutHit, OwningActor->GetActorLocation(), OwningActor->GetActorLocation() + TargetPosition, ECollisionChannel::ECC_Visibility);
				
				if (OutHit.bBlockingHit)
				{
					UAudioPlayerComponent* AudioComponent = OwningActor->GetComponentByClass<UAudioPlayerComponent>();
					if (AudioComponent)
					{
						AActor* OtherActor = OutHit.GetActor();
						if (OtherActor != OwningActor)
						{
							AudioComponent->SwitchFootsteps(OtherActor);
						}

						// Play footstep audio even if no physics material attached. Ensures consistency with audio events
						AudioComponent->PlayFootsteps();
					}
				}
			}
		}
	}
}
