// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MenuInterface.h"
#include "InGameMenu.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEPLATFORMM_API UInGameMenu : public UUserWidget
{
	GENERATED_BODY()

protected:

	virtual bool Initialize();

public:

	virtual void NativeDestruct() override;

	UFUNCTION()
	void LeaveToMainMenu();

	UFUNCTION()
	void CloseInGameMenu();

	void SetMenuInterface(IMenuInterface* SpecificMenuInterface);

private:

	UPROPERTY(meta = (BindWidget))
	class UButton* LeaveGame;

	UPROPERTY(meta = (BindWidget))
	class UButton* Cancel;

	IMenuInterface* MenuInterface;
	
};
