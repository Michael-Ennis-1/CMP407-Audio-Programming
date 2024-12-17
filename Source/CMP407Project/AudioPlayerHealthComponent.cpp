#include "AudioPlayerHealthComponent.h"
// Fill out your copyright notice in the Description page of Project Settings.


UAudioPlayerHealthComponent::UAudioPlayerHealthComponent()
{

}

void UAudioPlayerHealthComponent::DealProjectileDamage()
{
	RemoveHealth(ProjectileDamage);
}
