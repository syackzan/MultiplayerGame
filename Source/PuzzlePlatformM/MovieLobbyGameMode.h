// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MovieGameMode.h"
#include "MovieLobbyGameMode.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEPLATFORMM_API AMovieLobbyGameMode : public AMovieGameMode
{
	GENERATED_BODY()

public:

	void PostLogin(APlayerController* NewPlayer) override;

	void Logout(AController* Exiting) override;

	void SetWidgetToEdit(class UMovieLobbyMenu* _Widget);

	UPROPERTY(EditAnywhere)
	class UMovieLobbyMenu* MovieLobbyWidget;

private:
	int32 NumberOfPlayers = 0;

	int NumberOfPlayersAssignedCharacter = 0;

	class UUserWidget* LobbyWidgetToEdit;

	void StartMatchAfterTimer();

	void AddPlayerAssignedCharacter();
	
	//Set up an FTimerHandle
    FTimerHandle StartMovieGameTimer;
	
};
