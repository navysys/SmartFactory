// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FactoryPlayerController.h"
#include "AllAlarmWidgetComponent.generated.h"


class UTextBlock;
class UButton;
/**
 * 
 */
UCLASS()
class SMARTFACTORY_API UAllAlarmWidgetComponent : public UUserWidget
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
	UTextBlock* regdate;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* DataType1;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* DataType2;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* alarmStatus;

	UPROPERTY(meta = (BindWidget))
	UButton* AlarmData;

	void AddRow(const FAllAlarmChildDataStruct& FilteredData);

	UFUNCTION(BlueprintCallable)
	void AlarmDataButtonCallBack();
};
