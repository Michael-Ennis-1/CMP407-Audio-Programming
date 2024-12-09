// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AudioPlayerComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable)
class CMP407PROJECT_API UAudioPlayerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UAudioPlayerComponent();

	UFUNCTION(BlueprintImplementableEvent)
	void PlayFootsteps();

protected:
	virtual void BeginPlay() override;
};
