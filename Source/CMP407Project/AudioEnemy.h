// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "AudioEnemy.generated.h"

UCLASS()
class CMP407PROJECT_API AAudioEnemy : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AAudioEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
