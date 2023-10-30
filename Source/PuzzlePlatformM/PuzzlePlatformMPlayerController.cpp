// Fill out your copyright notice in the Description page of Project Settings.


#include "PuzzlePlatformMPlayerController.h"
#include "InGameMenu.h"

void APuzzlePlatformMPlayerController::BeginPlay()
{
    Super::BeginPlay();
}

void APuzzlePlatformMPlayerController::OpenMenuFromController()
{
    UE_LOG(LogTemp, Warning, TEXT("From Controller"));

    if(InGameMenu != nullptr)
    {
        InGameMenu->SetVisibility(ESlateVisibility::Visible);
        SetInputMode(FInputModeUIOnly());
        bShowMouseCursor = true;
    }
    
};

UInGameMenu* APuzzlePlatformMPlayerController::GetInGameMenuWidget()
{
    return InGameMenu;
}

void APuzzlePlatformMPlayerController::SetUpInGameMenuWidget()
{
    if(InGameMenuClass)
    {
        InGameMenu = CreateWidget<UInGameMenu>(this, InGameMenuClass);
        InGameMenu->AddToViewport();
        InGameMenu->SetVisibility(ESlateVisibility::Hidden);
    }
}