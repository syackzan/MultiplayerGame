// Fill out your copyright notice in the Description page of Project Settings.


#include "InGameMenu.h"
#include "Components/Button.h"
#include "MenuInterface.h"

bool UInGameMenu::Initialize()
{
    bool Success = Super::Initialize();

    if(!Success) return false;

    if(LeaveGame)
    {
        LeaveGame->OnClicked.AddDynamic(this, &UInGameMenu::LeaveToMainMenu);
    }

    if(Cancel)
    {
        Cancel->OnClicked.AddDynamic(this, &UInGameMenu::CloseInGameMenu);
    }

    return true;
}

void UInGameMenu::LeaveToMainMenu()
{   

    if(MenuInterface)
    {
        UE_LOG(LogTemp, Warning, TEXT("Menu Interface exists on InGameMenu.cpp"));
        MenuInterface->LeaveGame();
    }
    
}

void UInGameMenu::NativeDestruct()
{
    Super::NativeDestruct();

    UWorld* World = GetWorld();
    if(World == nullptr) return;

    APlayerController *PlayerController = World->GetFirstPlayerController();

    this->RemoveFromParent();
    this->SetVisibility(ESlateVisibility::Hidden);

    //Possible variable that is not required - can be deleted?
    //It is currently not being called anywhere
    FInputModeGameOnly InputModeData;

    if (PlayerController)
    {
        PlayerController->SetInputMode(FInputModeGameOnly());
        PlayerController->bShowMouseCursor = false;
    }
}

void UInGameMenu::CloseInGameMenu()
{
    UWorld* World = GetWorld();
    if(World == nullptr) return;

    APlayerController *PlayerController = World->GetFirstPlayerController();

    this->SetVisibility(ESlateVisibility::Hidden);

    //Possible variable that is not required - can be deleted?
    //It is currently not being called anywhere
    FInputModeGameOnly InputModeData;

    if (PlayerController)
    {
        PlayerController->SetInputMode(FInputModeGameOnly());
        PlayerController->bShowMouseCursor = false;
    }
}

void UInGameMenu::SetMenuInterface(IMenuInterface* SpecificMenuInterface)
{
    MenuInterface = SpecificMenuInterface;
};
