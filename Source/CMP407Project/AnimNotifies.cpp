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
			UAudioPlayerComponent* AudioComponent = OwningActor->GetComponentByClass<UAudioPlayerComponent>();
			if (AudioComponent)
			{
				AudioComponent->PlayFootsteps();
			}
		}
	}
}
