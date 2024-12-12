// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AudioEnemy.generated.h"

class UAIPerceptionComponent;

UCLASS()
class CMP407PROJECT_API AAudioEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AAudioEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	TObjectPtr<AActor> PlayerActor;

	// Work on this tomorrow
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TObjectPtr<UAIPerceptionComponent> PerceptionComponent;
};
