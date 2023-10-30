// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MenuInterface.h"
#include "MainMenu.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEPLATFORMM_API UMainMenu : public UUserWidget
{
	GENERATED_BODY()

protected:

	virtual bool Initialize();

public:

	void SetMenuInterface(IMenuInterface* SpecificMenuInterface);

	void SetListOfSessions(TArray<FOnlineSessionSearchResult> ListOfSessionsFromInstance);

	void SetUp();

	void SelectIndex(uint32 Index);

	virtual void NativeDestruct() override;

private:

	UPROPERTY(meta = (BindWidget))
	class UButton* Host;

	UPROPERTY(meta = (BindWidget))
	class UButton* Join;

	UPROPERTY(meta = (BindWidget))
	class UButton* EnterGame;

	UPROPERTY(meta = (BindWidget))
	class UButton* Cancel;

	UPROPERTY(meta = (BindWidget))
	class UButton* ExitGameButton;

	UPROPERTY(meta = (BindWidget))
	class UScrollBox* ListOfSessionsWidget;

	UPROPERTY(meta = (BindWidget))
	class UWidgetSwitcher* WidgetSwitcher1;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UServerRow> ServerRowWidgetClass;

	UPROPERTY()
	class UServerRow* ServerRowWidget;

	UFUNCTION()
	void HostServer();

	UFUNCTION()
	void JoinGame();

	UFUNCTION()
	void EnterGameMethod();

	UFUNCTION()
	void BackToMainMenu();

	UFUNCTION()
	void ExitGame();

	TOptional<uint32> SelectedIndex;

	IMenuInterface* MenuInterface;
	
};
