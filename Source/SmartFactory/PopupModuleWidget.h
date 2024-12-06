// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PopupModuleWidget.generated.h"

class UButton;
class UTextBlock;

/**
 * 
 */
UCLASS()
class SMARTFACTORY_API UPopupModuleWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeOnInitialized();

protected:
	UPROPERTY(meta = (BindWidget))
	UTextBlock* Title_TextBlock;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Content_TextBlock;

	UPROPERTY(meta = (BindWidget))
	UButton* Quit_Button;

	UPROPERTY(meta = (BindWidget))
	UButton* Cancel_Button;

private:
	UFUNCTION(BlueprintCallable)
	void QuitProgram();

	UFUNCTION(BlueprintCallable)
	void CancelButtonCallBack();


public:
	UFUNCTION(BlueprintCallable)
	void SetPopupTitleText(const FText& NewText);

	UFUNCTION(BlueprintCallable)
	void SetPopupContentText(const FText& NewText);
	
};
