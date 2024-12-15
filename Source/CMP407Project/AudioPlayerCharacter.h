// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CMP407ProjectCharacter.h"
#include "AudioPlayerCharacter.generated.h"

class UBoxComponent;
class UProjectileMovementComponent;

/**
 * 
 */
UCLASS()
class CMP407PROJECT_API AAudioPlayerCharacter : public ACMP407ProjectCharacter
{
	GENERATED_BODY()

	AAudioPlayerCharacter();

public:

	virtual void BeginPlay() override;

	// Occurs when character gets hit
	UFUNCTION()
	void OnBeginCharacterOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	// Occurs when bullet passes nearby player, could occur in conjunction with player being hit.
	UFUNCTION()
	void OnBeginPassbyOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	bool PredictProjectileCollision(AActor* InOtherActor, UProjectileMovementComponent* InProjectileMovementComponent);

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TObjectPtr<UBoxComponent> BulletPassbyBoxCollider;
};
