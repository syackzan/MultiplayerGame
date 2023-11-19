// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyGameMode.h"
#include "PuzzlePlatformGameInstance.h"

//FTimerHandle include
#include "Engine/EngineTypes.h"


void ALobbyGameMode::PostLogin(APlayerController* NewPlayer)
{

    Super::PostLogin(NewPlayer);

    UE_LOG(LogTemp, Warning, TEXT("From Lobby Game Mode"));
    NumberOfPlayers++;

    if(NumberOfPlayers >= 2)
    {   

        GetWorldTimerManager().SetTimer(StartGameTimer, this, &ALobbyGameMode::StartMatchAfterTimer, 5.0f, false);
        // StartMatchAfterTimer();
    }
};

void ALobbyGameMode::StartMatchAfterTimer()
{
    UE_LOG(LogTemp, Warning, TEXT("Start Match"));

    UPuzzlePlatformGameInstance* PuzzlePlatformGameInstance = Cast<UPuzzlePlatformGameInstance>(GetGameInstance());
    
    //Checkpoint 
    if(!PuzzlePlatformGameInstance) return;

    PuzzlePlatformGameInstance->StartSession();

    //Start Game!
    UWorld *World = GetWorld();
    if(World)
    {   
        if(HasAuthority())
        {
            bUseSeamlessTravel = true;
            World->ServerTravel("/Game/ThirdPerson/Maps/ThirdPersonMap?listen");
        }
    }
}

void ALobbyGameMode::Logout(AController* Exiting)
{

    Super::Logout(Exiting);

    NumberOfPlayers--;

    if(NumberOfPlayers <= 0)
    {
        UE_LOG(LogTemp, Warning, TEXT("End Game"));
    }
}

