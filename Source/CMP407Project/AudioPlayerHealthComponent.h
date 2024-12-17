// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AudioPlayerHealthComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable )
class CMP407PROJECT_API UAudioPlayerHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UAudioPlayerHealthComponent();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void HealHealth(float InValue);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void RemoveHealth(float InValue);

	void DealProjectileDamage();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ProjectileDamage = 2.5f;
};
