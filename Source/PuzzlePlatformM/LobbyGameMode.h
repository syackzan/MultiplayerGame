// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PuzzlePlatformMGameMode.h"
#include "LobbyGameMode.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEPLATFORMM_API ALobbyGameMode : public APuzzlePlatformMGameMode
{
	GENERATED_BODY()

public:

	void PostLogin(APlayerController* NewPlayer) override;

	void Logout(AController* Exiting) override;

private:
	int32 NumberOfPlayers = 0;

	void StartMatchAfterTimer();
	
	//Set up an FTimerHandle
    FTimerHandle StartGameTimer;
};
