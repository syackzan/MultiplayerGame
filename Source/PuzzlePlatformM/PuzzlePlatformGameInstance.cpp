// Fill out your copyright notice in the Description page of Project Settings.

#include "PuzzlePlatformGameInstance.h"
#include "Engine/Engine.h"
#include "Blueprint/UserWidget.h"
#include "MenuInterface.h"
#include "MainMenu.h"
#include "MovieLobbyMenu.h"
#include "PuzzlePlatformMPlayerController.h"
#include "InGameMenu.h"
#include "OnlineSubsystem.h"
#include "OnlineSessionSettings.h"
#include "UObject/UnrealNames.h"
#include "MovieLobbyGameMode.h"


const static FName SESSION_NAME = NAME_GameSession;
const static FName SERVER_NAME_SETTINGS = TEXT("ServerName");

UPuzzlePlatformGameInstance::UPuzzlePlatformGameInstance(const FObjectInitializer &ObjectInitializer)
{
    UE_LOG(LogTemp, Warning, TEXT("GameInstance"));
};

void UPuzzlePlatformGameInstance::Init()
{
    Super::Init();

    UE_LOG(LogTemp, Warning, TEXT("Init"));

    IOnlineSubsystem *Subsystem = IOnlineSubsystem::Get();

    if(Subsystem != nullptr)
    {
        UE_LOG(LogTemp, Warning, TEXT("Subsystem Found: %s"), *Subsystem->GetSubsystemName().ToString());
        SessionInterface = Subsystem->GetSessionInterface();

        if(SessionInterface.IsValid())
        {
            SessionInterface->OnCreateSessionCompleteDelegates.AddUObject(this, &UPuzzlePlatformGameInstance::OnCreateSessionComplete);
            SessionInterface->OnDestroySessionCompleteDelegates.AddUObject(this, &UPuzzlePlatformGameInstance::OnDestroySessionComplete);
            SessionInterface->OnFindSessionsCompleteDelegates.AddUObject(this, &UPuzzlePlatformGameInstance::OnFindSessionComplete);
            SessionInterface->OnJoinSessionCompleteDelegates.AddUObject(this, &UPuzzlePlatformGameInstance::OnJoinSessionComplete);
        } else
        {
            UE_LOG(LogTemp, Warning, TEXT("No Session Interface"));
        }
    } else {
        UE_LOG(LogTemp, Warning, TEXT("No Subsystem found"));
    }

    if(!GEngine) return;

    //Engine handles network failure
    GEngine->OnNetworkFailure().AddUObject(this, &UPuzzlePlatformGameInstance::OnNetworkFailure);
};

void UPuzzlePlatformGameInstance::Host(FString ServerName)
{
    DesiredServerName = ServerName;

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

        UE_LOG(LogTemp, Warning, TEXT("OnlinSubsystem: "), *IOnlineSubsystem::Get()->GetSubsystemName().ToString());

        //Subsystem will switch between STEAM and NULL - NULL is for testing purposes and requires a LAN connection
        if(IOnlineSubsystem::Get()->GetSubsystemName() == "NULL")
        {
            SessionSettings.bIsLANMatch = true; //LAN Setting
        } else {
            SessionSettings.bIsLANMatch = false; //Steam Setting
        };
        SessionSettings.NumPublicConnections = 5;
        SessionSettings.bShouldAdvertise = true;
        SessionSettings.bUsesPresence = true; //Steam Setting (Not required for LAN)
        SessionSettings.bUseLobbiesIfAvailable = true; //Steam Setting v>4.27 (Not required for LAN)
        SessionSettings.Set(SERVER_NAME_SETTINGS, DesiredServerName, EOnlineDataAdvertisementType::ViaOnlineServiceAndPing);

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
                //World->ServerTravel("/Game/ThirdPerson/Maps/ThirdPersonMap?listen");
                World->ServerTravel("/Game/ThirdPerson/Maps/MainLobby?listen");
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
        TArray<FServerData> ServerNames;
        for (const FOnlineSessionSearchResult&  SearchResult : SessionSearch->SearchResults)
        {
            FServerData Data;
            
            Data.MaxPlayers = SearchResult.Session.SessionSettings.NumPublicConnections;
            //NumOpenPublicConnections Gives you open slots left, not players in game. This is why we are subtracting
            Data.CurrentPlayers = Data.MaxPlayers - SearchResult.Session.NumOpenPublicConnections; 
            Data.HostUserName = SearchResult.Session.OwningUserName;
            FString ServerName;
            if(SearchResult.Session.SessionSettings.Get(SERVER_NAME_SETTINGS, ServerName))
            {
                Data.Name = ServerName;
            } else {
                Data.Name = "Could not find Server name.";
            }
            ServerNames.Add(Data);
        }

        // Call A Function From MainMenu Widget that stores a TArray<FOnlineSessionSearchResult> xxx
        MainMenuWidget->SetListOfSessions(ServerNames);

        if (ServerNames.Num() == 0)
        {
            UE_LOG(LogTemp, Warning, TEXT("No Search Results Found"));
        }

        UE_LOG(LogTemp, Warning, TEXT("Find Session Complete"));
    }
}

void UPuzzlePlatformGameInstance::OnNetworkFailure(UWorld* World, UNetDriver* NetDriver, ENetworkFailure::Type FailureType, const FString& ErrorString)
{
    LeaveGame();
};

void UPuzzlePlatformGameInstance::PrintSessions()
{
    //If SessionSearch Exists then Find Sessions
    SessionSearch = MakeShareable(new FOnlineSessionSearch());

    if (SessionSearch.IsValid())
    {
        SessionSearch->MaxSearchResults = 9999; //Steam Requirement
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

void UPuzzlePlatformGameInstance::LoadMovieLobbyMenu()
{

    if (MovieLobbyMenuWidgetClass)
    {
        MovieLobbyWidget = CreateWidget<UMovieLobbyMenu>(this, MovieLobbyMenuWidgetClass);

        // if errors look to caste first!
        if (MovieLobbyWidget == nullptr)
        {
            UE_LOG(LogTemp, Error, TEXT("Move lobby widget does not exist!"));
            return;
        } else 
        {
            UE_LOG(LogTemp, Warning, TEXT("Movie lobby widget exists"));

            MovieLobbyWidget->SetUp();
            MovieLobbyWidget->SetMenuInterface(this);
        }
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

void UPuzzlePlatformGameInstance::StartSession()
{
    if(SessionInterface.IsValid())
    {
        SessionInterface->StartSession(SESSION_NAME);
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