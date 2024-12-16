// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FactoryPlayerController.h"
#include "SystemPopupWidget.generated.h"

class UButton;
class UTextBlock;
class UVerticalBox;
/**
 * 
 */
UCLASS()
class SMARTFACTORY_API USystemPopupWidget : public UUserWidget
{
	GENERATED_BODY()


protected:
	virtual void NativeConstruct() override;

public:
	UPROPERTY(meta = (BindWidget))
	UVerticalBox* ContentVerticalBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UUserWidget> AlarmComponent;
};
