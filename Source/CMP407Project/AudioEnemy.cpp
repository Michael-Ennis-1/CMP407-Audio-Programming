// Fill out your copyright notice in the Description page of Project Settings.

#include "AudioEnemy.h"
#include "Kismet/GameplayStatics.h"
#include "Perception/AIPerceptionComponent.h"

// Sets default values
AAudioEnemy::AAudioEnemy()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>("Perception Component");
	if (ensure(PerceptionComponent))
	{

	}
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

	
}