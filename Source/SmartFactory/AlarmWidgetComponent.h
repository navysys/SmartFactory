// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FactoryPlayerController.h"
#include "AlarmWidgetComponent.generated.h"


class UTextBlock;
class UButton;

/**
 * 
 */
UCLASS()
class SMARTFACTORY_API UAlarmWidgetComponent : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* AlarmNo;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* MCName;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Contents;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* ThresholdMax;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* ThresholdMin;

	UPROPERTY(meta = (BindWidget))
	UButton* ExecuteButton;

	UPROPERTY(meta = (BindWidget))
	UButton* ModifyButton;

	UPROPERTY(meta = (BindWidget))
	UButton* DeleteButton;

	void AddRow(const FAllAlarmChildDataStruct& FilteredData);

	UFUNCTION(BlueprintCallable)
	void ModifyButtonCallBack();
};
