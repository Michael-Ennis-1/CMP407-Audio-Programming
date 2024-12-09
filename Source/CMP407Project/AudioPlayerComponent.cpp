// Fill out your copyright notice in the Description page of Project Settings.


#include "AudioPlayerComponent.h"

UAudioPlayerComponent::UAudioPlayerComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UAudioPlayerComponent::BeginPlay()
{
	Super::BeginPlay();
}

