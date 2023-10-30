// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ServerRow.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEPLATFORMM_API UServerRow : public UUserWidget
{
	GENERATED_BODY()

protected:

	virtual void NativeConstruct() override;
	virtual void NativeOnInitialized() override;

public:

	// UServerRow(const FObjectInitializer& ObjectInitializer);

	virtual bool Initialize();

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* ServerID;

	void Setup(class UMainMenu* InParent, uint32 InIndex);

private:

	UPROPERTY(meta = (BindWidget))
	class UButton* JoinServerButton;
	
	UFUNCTION()
	void JoinTheServerSession();

	UPROPERTY()
	class UMainMenu* Parent;

	uint32 Index;

	UFUNCTION()
	void OnClicked();
	
};
