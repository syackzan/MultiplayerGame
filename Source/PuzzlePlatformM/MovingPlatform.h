// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "MovingPlatform.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEPLATFORMM_API AMovingPlatform : public AStaticMeshActor
{
	GENERATED_BODY()

public:

	AMovingPlatform();
	// void AddActiveTrigger();
	// void RemoveActiveTrigger();

protected:
	// To add mapping context
	virtual void BeginPlay() override;

public:

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	float MovePlatform = false;

	void SetMovePlatform(bool IsMoving);

private:

	UPROPERTY(EditAnywhere)
	float Speed = 150.f;

	UPROPERTY(EditAnywhere, Meta = (MakeEditWidget = true))
	FVector TargetLocation;

	FVector GlobalTargetLocation;

	FVector GlobalStartLocation;

	float Distance;

	UPROPERTY(EditAnywhere)
	int32 ActiveTriggers = 1;
	
};
