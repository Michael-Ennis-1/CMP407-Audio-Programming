// Fill out your copyright notice in the Description page of Project Settings.


#include "AudioPlayerComponent.h"
#include "AudioEnemySubsystem.h"

UAudioPlayerComponent::UAudioPlayerComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UAudioPlayerComponent::BeginPlay()
{
	Super::BeginPlay();

	// Bind to audio enemy subsystem delegates to inform player when they are being chased by enemies and when a new enemy is registered/de-registered
	UAudioEnemySubsystem* AudioEnemySubsystem = GetAudioEnemySubsystem();
	if (ensure(AudioEnemySubsystem))
	{
		AudioEnemySubsystem->OnStartedChasing.AddUniqueDynamic(this, &UAudioPlayerComponent::PlayChaseMusic);
		AudioEnemySubsystem->OnFinishedChasing.AddUniqueDynamic(this, &UAudioPlayerComponent::PlayHiddenMusic);

		AudioEnemySubsystem->OnRegisteredEnemy.AddUniqueDynamic(this, &UAudioPlayerComponent::IncreaseAmountOfEnemiesRTPC);
		AudioEnemySubsystem->OnUnRegisteredEnemy.AddUniqueDynamic(this, &UAudioPlayerComponent::DecreaseAmountOfEnemiesRTPC);
	}
}

UAudioEnemySubsystem* UAudioPlayerComponent::GetAudioEnemySubsystem()
{
	AActor* OwningActor = GetOwner();
	if (ensure(OwningActor))
	{
		UGameInstance* GameInstance = OwningActor->GetGameInstance();
		if (ensure(GameInstance))
		{
			return GameInstance->GetSubsystem<UAudioEnemySubsystem>();
		}
	}

	return nullptr;
}

