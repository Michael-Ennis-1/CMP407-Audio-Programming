// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EnemyAudioComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable)
class CMP407PROJECT_API UEnemyAudioComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UEnemyAudioComponent();

	UFUNCTION(BlueprintImplementableEvent)
	void PlayBulletSFX();

protected:
	virtual void BeginPlay() override;
		
};
