// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SettingPopupWidget.generated.h"


class UButton;
class UComboBoxString;
/**
 * 
 */
UCLASS()
class SMARTFACTORY_API USettingPopupWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeOnInitialized();

protected:
	UPROPERTY(meta = (BindWidget))
	UButton* CloseButton;

	UPROPERTY(meta = (BindWidget))
	UComboBoxString* ResolutionComboBox;


public:

private:
	UFUNCTION(BlueprintCallable)
	void CloseButtonCallback();
	
	//해상도 리스트
	TArray<FIntPoint> Resolutions;

	//ComboBox 초기화
	void PopulateResolutionOptions();

	//해상도 적용
	UFUNCTION()
	void OnResolutionSelected(FString SelectedOption, ESelectInfo::Type SelectionType);

	//해상도 변경
	void ApplyResolution(FIntPoint Resolution);

};
