// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "MenuInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UMenuInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class PUZZLEPLATFORMM_API IMenuInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	//This tells c++ that there is no implementaion in the c++ file. We actually want to pull the 
	//instance of this function call from the class below it, the class that inherits from it (GameInstance in this case)
	//This is called a pure virtual function
	//This has an "Empty" implementation
	
	virtual void Host() = 0;

	virtual void Join(uint32 Index) = 0;

	virtual void LeaveGame() = 0;

	virtual void PrintSessions() = 0;
};
