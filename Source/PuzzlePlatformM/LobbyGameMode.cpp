// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyGameMode.h"

void ALobbyGameMode::PostLogin(APlayerController* NewPlayer)
{

    Super::PostLogin(NewPlayer);

    UE_LOG(LogTemp, Warning, TEXT("From Lobby Game Mode"));
    NumberOfPlayers++;

    if(NumberOfPlayers >= 2)
    {
        UE_LOG(LogTemp, Warning, TEXT("Start Match"));

        //Start Game!
        UWorld *World = GetWorld();
        if(World)
        {
            bUseSeamlessTravel = true;
            World->ServerTravel("/Game/ThirdPerson/Maps/ThirdPersonMap?listen");
        }
        
    }
};

void ALobbyGameMode::Logout(AController* Exiting)
{

    Super::Logout(Exiting);

    NumberOfPlayers--;

    if(NumberOfPlayers <= 0)
    {
        UE_LOG(LogTemp, Warning, TEXT("End Game"));
    }
}

