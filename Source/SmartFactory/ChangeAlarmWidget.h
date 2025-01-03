// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ChangeAlarmWidget.generated.h"

class UButton;
/**
 * 
 */
UCLASS()
class SMARTFACTORY_API UChangeAlarmWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
	UButton* CloseButton;

	UFUNCTION(BlueprintCallable)
	void CloseButtonCallBack();
};
