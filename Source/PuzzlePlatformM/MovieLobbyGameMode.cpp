// Fill out your copyright notice in the Description page of Project Settings.


#include "MovieLobbyGameMode.h"

#include "PuzzlePlatformGameInstance.h"

void AMovieLobbyGameMode::PostLogin(APlayerController* NewPlayer)
{

    Super::PostLogin(NewPlayer);

    UE_LOG(LogTemp, Warning, TEXT("From Lobby Game Mode"));
    NumberOfPlayers++;

    if(NumberOfPlayers >= 5)
    {   
        //GetWorldTimerManager().SetTimer(StartMovieGameTimer, this, &AMovieLobbyGameMode::StartMatchAfterTimer, 25.0f, false);
    }
};

void AMovieLobbyGameMode::StartMatchAfterTimer()
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

void AMovieLobbyGameMode::AddPlayerAssignedCharacter()
{

    NumberOfPlayersAssignedCharacter++;

    if(NumberOfPlayersAssignedCharacter > 2)
    {
        //Enable Start Button
        
    }
}

void AMovieLobbyGameMode::Logout(AController* Exiting)
{

    Super::Logout(Exiting);

    NumberOfPlayers--;

    if(NumberOfPlayers <= 0)
    {
        UE_LOG(LogTemp, Warning, TEXT("End Game"));
    }
}

void AMovieLobbyGameMode::SetWidgetToEdit(UMovieLobbyMenu *_Widget)
{

    MovieLobbyWidget = _Widget;
}
