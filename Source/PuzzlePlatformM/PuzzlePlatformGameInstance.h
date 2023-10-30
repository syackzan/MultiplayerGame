// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MenuInterface.h"
#include "OnlineSubsystem.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "PuzzlePlatformGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEPLATFORMM_API UPuzzlePlatformGameInstance : public UGameInstance, public IMenuInterface
{
	GENERATED_BODY()

public:

	UPuzzlePlatformGameInstance(const FObjectInitializer & ObjectInitializer);

	virtual void Init();

	UFUNCTION(Exec)
	void Host();

	UFUNCTION(Exec)
	void Join(uint32 Index);

	UFUNCTION(Exec, BlueprintCallable) 
	void LoadMenu();

	UFUNCTION(BlueprintCallable)
	void SetInGameMenuWidgetInterface();

	UFUNCTION(Exec)
	void LeaveGame();

	void PrintSessions();

private:

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UMainMenu> MainMenuWidgetClass;

	UPROPERTY()
	class UMainMenu* MainMenuWidget;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UInGameMenu> InGameMenuWidgetClass;

	class UInGameMenu* InGameMenuWidget;

	void OnCreateSessionComplete(FName SessionName, bool Success);

	void OnDestroySessionComplete(FName SessionName, bool Success);

	void OnFindSessionComplete(bool Success);

	void OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result);

	IOnlineSessionPtr SessionInterface;

	void CreateSessionThis();

	TSharedPtr<class FOnlineSessionSearch> SessionSearch;
	
};
