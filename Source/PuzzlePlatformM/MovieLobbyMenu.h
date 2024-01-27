// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MenuInterface.h"
#include "MovieLobbyMenu.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEPLATFORMM_API UMovieLobbyMenu : public UUserWidget
{
	GENERATED_BODY()

protected:

	virtual bool Initialize();

public:

	// UPROPERTY(meta = (BindWidget))
	// class UButton* StartGame;

public:

	void SetMenuInterface(IMenuInterface* SpecificMenuInterface);

	//void SetListOfSessions(TArray<FServerData> ListOfServers);

	void SetUp();

	//void SelectIndex(uint32 Index);

	//virtual void NativeDestruct() override;

private:

	IMenuInterface* MenuInterface;
	
};
