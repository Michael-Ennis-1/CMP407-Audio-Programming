// Fill out your copyright notice in the Description page of Project Settings.

#include "AudioEnemy.h"
#include "Kismet/GameplayStatics.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AIPerceptionTypes.h"
#include "AudioEnemySubsystem.h"

// Sets default values
AAudioEnemy::AAudioEnemy()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>("Perception Component");
}

// Called when the game starts or when spawned
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
