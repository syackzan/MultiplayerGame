// Fill out your copyright notice in the Description page of Project Settings.


#include "PuzzlePlatformMPlayerController.h"
#include "InGameMenu.h"
#include "GameFramework/PlayerState.h"
#include "BPFL_Steam.h"
#include "Math/UnrealMathUtility.h"


void APuzzlePlatformMPlayerController::BeginPlay()
{
    Super::BeginPlay();

    //Get Unique Steam ID and print it to the console log!
    UE_LOG(LogTemp, Warning, TEXT("Player ID: %s"), *UBPFL_Steam::GetSteamIDByString());

    //Search Database for Unique ID

    //If UniqueID Exists
        //Load Data
    //Else
        //Store Unique ID
        //Create Row
        //Autopopulate with Standard Data
        //Load Data

        int RoundedDown = FMath::DivideAndRoundDown<int>(10, 5);

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