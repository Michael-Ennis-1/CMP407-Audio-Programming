// Fill out your copyright notice in the Description page of Project Settings.

#include "AudioEnemy.h"
#include "Kismet/GameplayStatics.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AIPerceptionTypes.h"
#include "AudioEnemySubsystem.h"
#include "EnemyAudioComponent.h"

AAudioEnemy::AAudioEnemy()
{
	PerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>("Perception Component");
}

void AAudioEnemy::DisableEnemy()
{
	SetActorHiddenInGame(true);

	UEnemyAudioComponent* AudioComponent = GetComponentByClass<UEnemyAudioComponent>();
	if (ensure(AudioComponent))
	{
		AudioComponent->PlayExplosionSFX();
	}

	UAudioEnemySubsystem* AudioSubsystem = GetAudioEnemySubsystem();
	if (ensure(AudioSubsystem))
	{
		AudioSubsystem->UnRegisterAudioEnemy(this);
	}

	SetLifeSpan(2.0f);
}

void AAudioEnemy::BeginPlay()
{
	Super::BeginPlay();
	
	UWorld* World = GetWorld();
	if (ensure(World))
	{
		APlayerController* PlayerController = UGameplayStatics::GetPlayerController(World, 0);
		if (ensure(PlayerController))
		{
			PlayerActor = PlayerController->GetPawn();
		}
	}

	if (ensure(PerceptionComponent))
	{
		// Utilize perception component in Unreal to detect when player is spotted
		PerceptionComponent->OnTargetPerceptionUpdated.AddUniqueDynamic(this, &AAudioEnemy::TargetPerceptionUpdated);
	}
}

void AAudioEnemy::TargetPerceptionUpdated(AActor* InActor, FAIStimulus InStimulus)
{
	if (ensure(InActor) && ensure(PlayerActor))
	{
		if(InActor == PlayerActor)
		{
			UAudioEnemySubsystem* AudioSubsystem = GetAudioEnemySubsystem();

			// If player successfully sensed, register this AI with subsystem and inform behaviour tree
			if (InStimulus.WasSuccessfullySensed())
			{
				if (!AudioSubsystem->IsCurrentlyRegistered(this))
				{
					AudioSubsystem->RegisterAudioEnemy(this);
					OnEnemyStartedChasing.Broadcast();
				}
			}
			else
			{
				// If player is no longer sensed, remove from audio subsystem and inform behaviour tree
				if (AudioSubsystem->IsCurrentlyRegistered(this))
				{
					AudioSubsystem->UnRegisterAudioEnemy(this);
					OnEnemyStoppedChasing.Broadcast();
				}
			}
		}
	}
}

UAudioEnemySubsystem* AAudioEnemy::GetAudioEnemySubsystem()
{
	UGameInstance* GameInstance = GetGameInstance();
	if (ensure(GameInstance))
	{
		return GameInstance->GetSubsystem<UAudioEnemySubsystem>();
	}

	return nullptr;
}
