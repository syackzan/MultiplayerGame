// Fill out your copyright notice in the Description page of Project Settings.

#include "ServerRow.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "MainMenu.h"

// UServerRow::UServerRow(const FObjectInitializer &ObjectInitializer) :Super(ObjectInitializer)
// {
//     UE_LOG(LogTemp, Warning, TEXT("From Server From Contrusctor"));

//      if (JoinServerButton)
//     {
//         UE_LOG(LogTemp, Warning, TEXT("Join Server Button Initialized"));
//         //JoinServerButton->OnClicked.AddDynamic(this, &UServerRow::JoinTheServerSession);
//     } else {
//         UE_LOG(LogTemp, Warning, TEXT("No Server Button Initialized"));
//     }
// }

void UServerRow::NativeConstruct()
{
   Super::NativeConstruct();

    if (JoinServerButton)
    {
        UE_LOG(LogTemp, Warning, TEXT("Join Server Button Initialized"));
        //JoinServerButton->OnClicked.AddDynamic(this, &UServerRow::JoinTheServerSession);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("No Server Button Initialized"));
    }
};

void UServerRow::NativeOnInitialized()
{

    Super::NativeOnInitialized();

    
}

bool UServerRow::Initialize()
{

    bool Success = Super::Initialize();
    if (!Success)
        return false;

    return true;
}

void UServerRow::JoinTheServerSession()
{
    if(ServerID)
    {
          // Call Reference Join Session from Interface
        UE_LOG(LogTemp, Warning, TEXT("Server ID: %s"), *ServerID->GetText().ToString());
    } 
  
}

void UServerRow::Setup(class UMainMenu* InParent, uint32 InIndex)
{   
    Parent = InParent;
    Index = InIndex;
    JoinServerButton->OnClicked.AddDynamic(this, &UServerRow::OnClicked);
};

void UServerRow::OnClicked()
{
    Parent->SelectIndex(Index);
}
