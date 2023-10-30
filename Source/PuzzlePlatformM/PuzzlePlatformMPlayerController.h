// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PuzzlePlatformMPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEPLATFORMM_API APuzzlePlatformMPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:

	virtual void BeginPlay() override;

public:

	void OpenMenuFromController();

	class UInGameMenu* GetInGameMenuWidget();

	UFUNCTION(BlueprintCallable)
	void SetUpInGameMenuWidget();

private:

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UInGameMenu> InGameMenuClass;

	UPROPERTY()
	class UInGameMenu* InGameMenu;
	
};
