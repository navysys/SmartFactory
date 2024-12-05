// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "SystemPopupWidget.generated.h"

class UButton;
class UTextBlock;
/**
 * 
 */
UCLASS()
class SMARTFACTORY_API USystemPopupWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UButton* TestButton;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UTextBlock* TestTextBlock;

protected:
	virtual void NativeOnInitialized();

private:
	UFUNCTION(BlueprintCallable)
	void TestButtonCallback();

	
};
