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
	void Host(FString ServerName) override;

	UFUNCTION(Exec)
	void Join(uint32 Index) override;

	UFUNCTION(Exec, BlueprintCallable) 
	void LoadMenu();

	UFUNCTION(Exec, BlueprintCallable) 
	void LoadMovieLobbyMenu();

	UFUNCTION(BlueprintCallable)
	void SetInGameMenuWidgetInterface();

	UFUNCTION(Exec)
	void LeaveGame();

	void PrintSessions();

	void StartSession();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UMovieLobbyMenu* MovieLobbyWidget;

private:

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UMainMenu> MainMenuWidgetClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UMovieLobbyMenu> MovieLobbyMenuWidgetClass;

	UPROPERTY()
	class UMainMenu* MainMenuWidget;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UInGameMenu> InGameMenuWidgetClass;

	class UInGameMenu* InGameMenuWidget;

	void OnCreateSessionComplete(FName SessionName, bool Success);

	void OnDestroySessionComplete(FName SessionName, bool Success);

	void OnFindSessionComplete(bool Success);

	void OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result);

	void OnNetworkFailure(UWorld* World, UNetDriver* NetDriver, ENetworkFailure::Type FailureType, const FString& ErrorString);

	IOnlineSessionPtr SessionInterface;

	void CreateSessionThis();

	TSharedPtr<class FOnlineSessionSearch> SessionSearch;

	FString DesiredServerName = "";
	
};
