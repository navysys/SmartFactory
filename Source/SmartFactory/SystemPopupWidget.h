// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SystemPopupWidget.generated.h"

class UButton;
class UTextBlock;
class UGridPanel;
/**
 * 
 */
UCLASS()
class SMARTFACTORY_API USystemPopupWidget : public UUserWidget
{
	GENERATED_BODY()


protected:
	virtual void NativeOnInitialized();

public:
	UPROPERTY(meta = (BindWidget))
	UGridPanel*  AlarmTableGird;

	void AddRow(int32 RowIndex, const TArray<FString>& RowData);


};
