// Fill out your copyright notice in the Description page of Project Settings.

#include "MainMenu.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "Components/EditableTextBox.h"
#include "PuzzlePlatformMPlayerController.h"
#include "Components/ScrollBox.h"
#include "OnlineSessionSettings.h"
#include "Components/TextBlock.h"
#include "Components/EditableText.h"
#include "ServerRow.h"

bool UMainMenu::Initialize()
{
    bool Success = Super::Initialize();
    if (!Success)
        return false;

    // TODO: Setup

    if (Host)
    {
        Host->OnClicked.AddDynamic(this, &UMainMenu::OpenHostServerWidget);
    }

    if (Join)
    {
        Join->OnClicked.AddDynamic(this, &UMainMenu::JoinGame);
    }

    if (EnterGame)
    {
        EnterGame->OnClicked.AddDynamic(this, &UMainMenu::EnterGameMethod);
    }

    if (Cancel)
    {
        Cancel->OnClicked.AddDynamic(this, &UMainMenu::BackToMainMenu);
    }

    if(HostBackToMenu){
        HostBackToMenu->OnClicked.AddDynamic(this, &UMainMenu::BackToMainMenuFromHost);
    }

    if(StartServer)
    {
        //TODO:: Add button to create Server name in Create Session
        StartServer->OnClicked.AddDynamic(this, &UMainMenu::HostServer);
    }

    if (ExitGameButton)
    {
        ExitGameButton->OnClicked.AddDynamic(this, &UMainMenu::ExitGame);
    }

    return true;
};

void UMainMenu::SetMenuInterface(IMenuInterface *SpecificMenuInterface)
{
    // Set Internal MenuInteface by calling this!
    MenuInterface = SpecificMenuInterface;
};

void UMainMenu::SetUp()
{
    UE_LOG(LogTemp, Warning, TEXT("Name of Widget: %s"), *this->GetName());
    AddToViewport();
    SetVisibility(ESlateVisibility::Visible);

    UWorld *World = GetWorld();
    if (World == nullptr)
    {
        UE_LOG(LogTemp, Warning, TEXT("No World"));
        return;
    }

    UE_LOG(LogTemp, Warning, TEXT("World Exists"));

    APlayerController *PlayerController = World->GetFirstPlayerController();

    APuzzlePlatformMPlayerController *PuzzleMeTuzzles = Cast<APuzzlePlatformMPlayerController>(PlayerController);

    if (PuzzleMeTuzzles)
    {
        UE_LOG(LogTemp, Warning, TEXT("PuzzlePlatformController Exists in Game Instance of Main Lobby widget"));
    }

    FInputModeUIOnly InputModeData;
    InputModeData.SetWidgetToFocus(this->TakeWidget());
    InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);

    if (PlayerController == nullptr)
    {
        UE_LOG(LogTemp, Warning, TEXT("No PlayerController"));
    }

    if (PlayerController)
    {
        UE_LOG(LogTemp, Warning, TEXT("PlayerControllerExists"));
        PlayerController->SetInputMode(InputModeData);
        PlayerController->bShowMouseCursor = true;
    }
};

void UMainMenu::HostServer()
{
    if (MenuInterface)
    {
        FString ServerNameInString = UserServerNameText->GetText().ToString();
        MenuInterface->Host(ServerNameInString);
    }
};

void UMainMenu::OpenHostServerWidget()
{
    UE_LOG(LogTemp, Warning, TEXT("From Host Server!"));

    if (WidgetSwitcher1)
    {
        WidgetSwitcher1->SetActiveWidgetIndex(2);
    }
}

void UMainMenu::JoinGame()
{
    UE_LOG(LogTemp, Warning, TEXT("From Join Game!"));

    if (WidgetSwitcher1)
    {
        // Store Any Sessions into a TArray
        MenuInterface->PrintSessions();

        // Set the Main Menu to Join Main Menu Widget
        WidgetSwitcher1->SetActiveWidgetIndex(1);
    }
};

void UMainMenu::SelectIndex(uint32 Index)
{
    SelectedIndex = Index;
}

// This function is called from Game Interface
void UMainMenu::SetListOfSessions(TArray<FServerData> ListOfServers)
{
    UWorld *ThisWorld = this->GetWorld();

    if (ThisWorld == nullptr)
        return;
    FName TextRowName = TEXT("ServerID");

    ListOfSessionsWidget->ClearChildren();

    uint32 index = 0;
    // Create ServerRowWidget + Change Name of Text
    for (int i = 0; i < ListOfServers.Num(); i++)
    {
        ServerRowWidget = CreateWidget<UServerRow>(ThisWorld, ServerRowWidgetClass);
        if (ServerRowWidget == nullptr)
            return;
        UE_LOG(LogTemp, Warning, TEXT("ServerWidgetCreated"));

        ServerRowWidget->ServerID->SetText(FText::FromString(ListOfServers[i].Name)); 
        ServerRowWidget->HostUserName->SetText(FText::FromString(ListOfServers[i].HostUserName));
        //Can use the commented out lines of code instead of binding two separate widgets for CurrentPlayers and MaxPlayers!
        //FString FractionText = FString::Printf(TEXT("%d/%d"), ServerData.CurrentPlayers, ServerData.MaxPlayers)
        //ServerRowWidget->ConnectionFraction->SetText(FractionText);
        ServerRowWidget->CurrentPlayers->SetText(FText::AsNumber(ListOfServers[i].CurrentPlayers));
        ServerRowWidget->MaxPlayers->SetText(FText::AsNumber(ListOfServers[i].MaxPlayers));

        ServerRowWidget->Setup(this, index);
        index++;
        UE_LOG(LogTemp, Warning, TEXT("Set Text"));

        ListOfSessionsWidget->AddChild(ServerRowWidget);
    }
};

void UMainMenu::NativeDestruct()
{
    Super::NativeDestruct();

    UWorld *World = GetWorld();
    if (World == nullptr)
        return;

    APlayerController *PlayerController = World->GetFirstPlayerController();

    this->RemoveFromParent();
    this->SetVisibility(ESlateVisibility::Hidden);

    // Possible variable that is not required - can be deleted?
    // It is currently not being called anywhere
    FInputModeGameOnly InputModeData;

    if (PlayerController)
    {
        PlayerController->SetInputMode(FInputModeGameOnly());
        PlayerController->bShowMouseCursor = false;
    }
}

void UMainMenu::EnterGameMethod()
{
    //FString IPAddress = UserInputIP->GetText().ToString();

    UE_LOG(LogTemp, Warning, TEXT("From EnterGameMethod"));

    if(SelectedIndex.IsSet() && MenuInterface != nullptr)
    {
        UE_LOG(LogTemp, Warning, TEXT("Selected Index %d"), SelectedIndex.GetValue());
        MenuInterface->Join(SelectedIndex.GetValue());
    } else{
        UE_LOG(LogTemp, Warning, TEXT("Selected Index not set."));
    }
}

void UMainMenu::BackToMainMenu()
{
    if (WidgetSwitcher1)
    {
        WidgetSwitcher1->SetActiveWidgetIndex(0);
    }
}

void UMainMenu::BackToMainMenuFromHost()
{
    if (WidgetSwitcher1)
    {
        WidgetSwitcher1->SetActiveWidgetIndex(0);
    }
};

void UMainMenu::ExitGame()
{
    if (ExitGameButton)
    {
        APlayerController *PlayerController = GetWorld()->GetFirstPlayerController();

        PlayerController->ConsoleCommand(TEXT("Quit"));
    }
}
