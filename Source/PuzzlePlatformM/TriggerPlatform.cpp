// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerPlatform.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "MovingPlatformRev1.h"

// Sets default values
ATriggerPlatform::ATriggerPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PressureVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("Pressure Volume"));
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));

	if(PressureVolume && StaticMesh)
	{
		RootComponent = PressureVolume;
		StaticMesh->SetupAttachment(PressureVolume);
	}
}

// Called when the game starts or when spawned
void ATriggerPlatform::BeginPlay()
{
	Super::BeginPlay();
	
	PressureVolume->OnComponentBeginOverlap.AddDynamic(this, &ATriggerPlatform::OnOverlapBegin);
	PressureVolume->OnComponentEndOverlap.AddDynamic(this, &ATriggerPlatform::OnOverlapEnd);
}

// Called every frame
void ATriggerPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATriggerPlatform::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{	
	TrackOverlap += 1;

	//Logic to let Overlap Function Fire once
	if(TrackOverlap == 1)
	{
		//UE_LOG(LogTemp, Warning, TEXT("From OverlapBegin"));

		if(MovingPlatforms[0] != nullptr)
		{
			//UE_LOG(LogTemp, Warning, TEXT("Move Platty yes"));
			MovingPlatforms[0]->SetMovePlatform(true);
		}
		
	}
	
};

void ATriggerPlatform::OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	TrackOverlap -= 1;

	//Logic to let Overlap Function Fire once
	if(TrackOverlap == 0)
	{
		//UE_LOG(LogTemp, Warning, TEXT("From OverlapEnd"));
	}

	if(MovingPlatforms[0] != nullptr)
	{
		//UE_LOG(LogTemp, Warning, TEXT("Move Platty no"));
		MovingPlatforms[0]->SetMovePlatform(false);
	}
	
	
};

