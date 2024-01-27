// Fill out your copyright notice in the Description page of Project Settings.


#include "MovieLobbyMenu.h"

#include "PuzzlePlatformMPlayerController.h"
#include "MovieLobbyGameMode.h"

bool UMovieLobbyMenu::Initialize()
{
    bool Success = Super::Initialize();
    if (!Success)
        return false;

    // TODO: Setup

    // if (Host)
    // {
    //     Host->OnClicked.AddDynamic(this, &UMainMenu::OpenHostServerWidget);
    // }

    return true;
};

void UMovieLobbyMenu::SetMenuInterface(IMenuInterface *SpecificMenuInterface)
{
    // Set Internal MenuInteface by calling this!
    MenuInterface = SpecificMenuInterface;
};

void UMovieLobbyMenu::SetUp()
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


    AMovieLobbyGameMode* MovieLobbyGameMode = Cast<AMovieLobbyGameMode>(World->GetAuthGameMode());

    //MovieLobbyGameMode->SetWidgetToEdit(this);

    UE_LOG(LogTemp, Warning, TEXT("World Exists"));

    APlayerController *PlayerController = World->GetFirstPlayerController();

    APuzzlePlatformMPlayerController *PuzzleMeTuzzles = Cast<APuzzlePlatformMPlayerController>(PlayerController);

    if (PuzzleMeTuzzles)
    {
        UE_LOG(LogTemp, Warning, TEXT("PuzzlePlatformController Exists in Game Instance of main menu widget"));
    }

    FInputModeUIOnly InputModeData;
    InputModeData.SetWidgetToFocus(this->TakeWidget());
    InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);

    if (PlayerController)
    {
        UE_LOG(LogTemp, Warning, TEXT("PlayerControllerExists"));
        PlayerController->SetInputMode(InputModeData);
        PlayerController->bShowMouseCursor = true;
    } else 
    {
        UE_LOG(LogTemp, Error, TEXT("Player Controller does not exist!"));
    }
};