// Fill out your copyright notice in the Description page of Project Settings.

#include "PuzzlePlatformGameInstance.h"
#include "Engine/Engine.h"
#include "Blueprint/UserWidget.h"
#include "MenuInterface.h"
#include "MainMenu.h"
#include "PuzzlePlatformMPlayerController.h"
#include "InGameMenu.h"
#include "OnlineSubsystem.h"
#include "OnlineSessionSettings.h"


const static FName SESSION_NAME = TEXT("My Session Game");

UPuzzlePlatformGameInstance::UPuzzlePlatformGameInstance(const FObjectInitializer &ObjectInitializer)
{
    UE_LOG(LogTemp, Warning, TEXT("GameInstance"));
};

void UPuzzlePlatformGameInstance::Init()
{
    Super::Init();

    UE_LOG(LogTemp, Warning, TEXT("Init"));

    IOnlineSubsystem *Subsystem = IOnlineSubsystem::Get();
    if (Subsystem == nullptr)
    {
        UE_LOG(LogTemp, Warning, TEXT("No Subsystem found"));
    }

    SessionInterface = Subsystem->GetSessionInterface();

    if (SessionInterface == nullptr)
    {
        UE_LOG(LogTemp, Warning, TEXT("No Session Interface"));
    }
    else
    {
        SessionInterface->OnCreateSessionCompleteDelegates.AddUObject(this, &UPuzzlePlatformGameInstance::OnCreateSessionComplete);
        SessionInterface->OnDestroySessionCompleteDelegates.AddUObject(this, &UPuzzlePlatformGameInstance::OnDestroySessionComplete);
        SessionInterface->OnFindSessionsCompleteDelegates.AddUObject(this, &UPuzzlePlatformGameInstance::OnFindSessionComplete);
        SessionInterface->OnJoinSessionCompleteDelegates.AddUObject(this, &UPuzzlePlatformGameInstance::OnJoinSessionComplete);

        SessionSearch = MakeShareable(new FOnlineSessionSearch());
        SessionSearch->bIsLanQuery = true;
    }
};

void UPuzzlePlatformGameInstance::Host()
{

    if (SessionInterface)
    {
        FNamedOnlineSession *ExistingSession = SessionInterface->GetNamedSession(SESSION_NAME);
        if (ExistingSession != nullptr)
        {
            SessionInterface->DestroySession(SESSION_NAME);
        }
        else
        {
            CreateSessionThis();
        }
    }
}

void UPuzzlePlatformGameInstance::CreateSessionThis()
{
    if (SessionInterface)
    {
        FOnlineSessionSettings SessionSettings;
        //SessionSettings.bIsLANMatch = true; //LAN Setting
        SessionSettings.bIsLANMatch = false; //Steam Setting
        SessionSettings.NumPublicConnections = 2;
        SessionSettings.bShouldAdvertise = true;
        SessionSettings.bUsesPresence = true; //Steam Setting (Not required for LAN)
        SessionSettings.bUseLobbiesIfAvailable = true; //Steam Setting v>4.27 (Not required for LAN)

        SessionInterface->CreateSession(0, SESSION_NAME, SessionSettings);
    }
}

void UPuzzlePlatformGameInstance::OnCreateSessionComplete(FName SessionName, bool Success)
{
    if (!Success)
    {
        UE_LOG(LogTemp, Warning, TEXT("Session was not created not successful"));
    }
    else
    {
        if (MainMenuWidget != nullptr)
        {
            MainMenuWidget->NativeDestruct();
        }

        UEngine *Engine = GetEngine();

        if (Engine)
        {
            Engine->AddOnScreenDebugMessage(0, 2, FColor::Green, TEXT("Hosting"));

            UWorld *World = GetWorld();
            if (World)
            {
                World->ServerTravel("/Game/ThirdPerson/Maps/ThirdPersonMap?listen");
            }
        }

        UE_LOG(LogTemp, Warning, TEXT("Session created!"));
    }
}

void UPuzzlePlatformGameInstance::OnDestroySessionComplete(FName SessionName, bool Success)
{
    if (Success)
    {
        CreateSessionThis();
    }
};

void UPuzzlePlatformGameInstance::OnFindSessionComplete(bool Success)
{
    if (Success)
    {

        if (SessionSearch == nullptr)
            return;

        //Store Sessions inside of a TArray for manipulation
        TArray<FOnlineSessionSearchResult> SearchResults = SessionSearch->SearchResults;

        // Call A Function From MainMenu Widget that stores a TArray<FOnlineSessionSearchResult> xxx
        MainMenuWidget->SetListOfSessions(SearchResults);

        if (SearchResults.Num() == 0)
        {
            UE_LOG(LogTemp, Warning, TEXT("No Search Results Found"));
        }

        for (int i = 0; i < SearchResults.Num(); i++)
        {
            UE_LOG(LogTemp, Warning, TEXT("Session #:%f, Session Id: %s"), i, *SearchResults[i].GetSessionIdStr());
        }

        //     for(const FOnlineSessionSearchResult& SearchResult : SearchResults)
        //     {
        //         UE_LOG(LogTemp, Warning, TEXT("Session: %s"), SearchResult.GetSessionIdStr());
        //     }

        UE_LOG(LogTemp, Warning, TEXT("Find Session Complete"));
    }
}

void UPuzzlePlatformGameInstance::PrintSessions()
{
    //If SessionSearch Exists then Find Sessions
    if (SessionSearch)
    {
        SessionSearch->MaxSearchResults = 100; //Steam Requirement
        SessionSearch->QuerySettings.Set(SEARCH_PRESENCE, true, EOnlineComparisonOp::Equals); //Steam Requirement
        UE_LOG(LogTemp, Warning, TEXT("Finding Sessions"));
        SessionInterface->FindSessions(0, SessionSearch.ToSharedRef());
    }
    //Calls Event Delegate
}

void UPuzzlePlatformGameInstance::Join(uint32 Index)
{
    //Checkpoint
    if(!SessionInterface.IsValid()) 
        return;
    //Checkpoint
    if(!SessionSearch.IsValid())
        return;

    if (MainMenuWidget != nullptr)
    {
        MainMenuWidget->NativeDestruct();
    }

    SessionInterface->JoinSession(0, SESSION_NAME, SessionSearch->SearchResults[Index]);
}

void UPuzzlePlatformGameInstance::OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result)
{
    //Checkpoint
    if(!SessionInterface.IsValid())
        return;

    FString Address;
    if(!SessionInterface->GetResolvedConnectString(SessionName, Address))
    {
        UE_LOG(LogTemp, Warning, TEXT("Cannot Resolved Connection String"));
    };

    UEngine *Engine = GetEngine();

    if (Engine)
    {
        Engine->AddOnScreenDebugMessage(0, 2, FColor::Green, FString::Printf(TEXT("Joining, %s"), *Address));
    }

    APlayerController *PlayerController = GetFirstLocalPlayerController();
    APuzzlePlatformMPlayerController *PuzzleMeTuzzles = Cast<APuzzlePlatformMPlayerController>(PlayerController);

    if (PuzzleMeTuzzles)
    {
        UE_LOG(LogTemp, Warning, TEXT("PuzzlePlatformController Exists in Game Instance"));
    }

    if (PlayerController)
    {
        PlayerController->ClientTravel(Address, ETravelType::TRAVEL_Absolute);
    }
};

void UPuzzlePlatformGameInstance::LoadMenu()
{

    if (MainMenuWidgetClass)
    {
        MainMenuWidget = CreateWidget<UMainMenu>(this, MainMenuWidgetClass);

        // if errors look to caste first!
        if (MainMenuWidget == nullptr)
        {
            UE_LOG(LogTemp, Warning, TEXT("GGs"));
            return;
        }

        UE_LOG(LogTemp, Warning, TEXT("We Live"));
        MainMenuWidget->SetUp();
        MainMenuWidget->SetMenuInterface(this);
    }
}

void UPuzzlePlatformGameInstance::LeaveGame()
{
    UE_LOG(LogTemp, Warning, TEXT("Leave Game Called from Instance"));
    // Need to get a way to the Main Menu Level! Need to replace the address!

    APlayerController *PlayerController = GetFirstLocalPlayerController();
    APuzzlePlatformMPlayerController *PuzzleMeTuzzles = Cast<APuzzlePlatformMPlayerController>(PlayerController);
    UInGameMenu *InGameMenu = PuzzleMeTuzzles->GetInGameMenuWidget();

    if (InGameMenu != nullptr)
    {
        InGameMenu->NativeDestruct();
    }

    UEngine *Engine = GetEngine();

    if (Engine)
    {
        Engine->AddOnScreenDebugMessage(0, 2, FColor::Green, FString::Printf(TEXT("Leaving Back To Main Menu")));
    }

    if (PuzzleMeTuzzles)
    {
        UE_LOG(LogTemp, Warning, TEXT("PuzzlePlatformController Exists in Game Instance"));
    }

    if (PlayerController)
    {
        PlayerController->ClientTravel("/Game/MainMenuLobby", ETravelType::TRAVEL_Absolute);
    }
}

void UPuzzlePlatformGameInstance::SetInGameMenuWidgetInterface()
{
    APlayerController *PlayerController = GetFirstLocalPlayerController();
    UE_LOG(LogTemp, Warning, TEXT("1"));
    if (PlayerController == nullptr)
        return;
    APuzzlePlatformMPlayerController *PuzzleMeTuzzles = Cast<APuzzlePlatformMPlayerController>(PlayerController);
    UE_LOG(LogTemp, Warning, TEXT("2"));
    if (PuzzleMeTuzzles == nullptr)
        return;
    UInGameMenu *InGameMenu = PuzzleMeTuzzles->GetInGameMenuWidget();
    UE_LOG(LogTemp, Warning, TEXT("3"));
    if (InGameMenu == nullptr)
        return;
    UE_LOG(LogTemp, Warning, TEXT("4"));

    InGameMenu->SetMenuInterface(this);

    UE_LOG(LogTemp, Warning, TEXT("Game Instance Set for In Game Menu"));
};