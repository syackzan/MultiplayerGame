// Fill out your copyright notice in the Description page of Project Settings.

#include "MovingPlatform.h"

AMovingPlatform::AMovingPlatform()
{

    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    SetMobility(EComponentMobility::Movable);
}

void AMovingPlatform::BeginPlay()
{
    Super::BeginPlay();

    if (HasAuthority())
    {
        SetReplicates(true);
        SetReplicateMovement(true);
        UE_LOG(LogTemp, Warning, TEXT("Hello!"));
    }

    GlobalStartLocation = GetActorLocation();

    GlobalTargetLocation = GetTransform().TransformPosition(TargetLocation);
}

void AMovingPlatform::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    UE_LOG(LogTemp, Warning, TEXT("Is anything working?"));

    // if(!HasAuthority())
    // {
    //     UE_LOG(LogTemp, Warning, TEXT("Does Not Have Authority"));
    // }

    // if (HasAuthority())
    // {
    //     UE_LOG(LogTemp, Warning, TEXT("HasAuthority"));
    //     if (MovePlatform)
    //     {

    //         UE_LOG(LogTemp, Warning, TEXT("Moving?"));
    //         float JourneyLength = FVector::Dist(GlobalStartLocation, GetActorLocation());
    //         float StartLength = FVector::Dist(GlobalStartLocation, GlobalTargetLocation);

    //         if (JourneyLength >= StartLength)
    //         {
    //             UE_LOG(LogTemp, Warning, TEXT("Turn Around Bright Eyes"));
    //             FVector Swap = GlobalStartLocation;
    //             GlobalStartLocation = GlobalTargetLocation;
    //             GlobalTargetLocation = Swap;
    //         }
    //         else
    //         {

    //             FVector Direction = (GlobalTargetLocation - GlobalStartLocation).GetSafeNormal();
    //             FVector Location = GetActorLocation();
    //             Location += Speed * DeltaTime * Direction;
    //             SetActorLocation(Location);
    //         }
    //     }
    // }
}

void AMovingPlatform::SetMovePlatform(bool IsMoving)
{
    //UE_LOG(LogTemp, Warning, TEXT("Should Be Moving!"));
    MovePlatform = IsMoving;
}