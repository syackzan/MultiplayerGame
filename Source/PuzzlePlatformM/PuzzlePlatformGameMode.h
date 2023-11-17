// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "Http.h"
#include "PuzzlePlatformGameMode.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEPLATFORMM_API APuzzlePlatformGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	APuzzlePlatformGameMode();

	virtual void StartPlay() override;

private:
	void OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully);

	void CustomHTTPRequest();
	
};
