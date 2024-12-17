// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DataWidget.generated.h"


class UButton;
class UTextBlock;

UCLASS()
class SMARTFACTORY_API UDataWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> VisibleButton;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> DataNameText;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> DataValueText;

	FString DataName;
};
