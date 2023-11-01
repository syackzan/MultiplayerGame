// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyGameMode.h"

void ALobbyGameMode::PostLogin(APlayerController* NewPlayer)
{
    NumberOfPlayers++;

    if(NumberOfPlayers >= 3)
    {
        UE_LOG(LogTemp, Warning, TEXT("Start Match"));
    }
};

void ALobbyGameMode::Logout(AController* Exiting)
{
    NumberOfPlayers--;

    if(NumberOfPlayers <= 0)
    {
        UE_LOG(LogTemp, Warning, TEXT("End Game"));
    }
}

