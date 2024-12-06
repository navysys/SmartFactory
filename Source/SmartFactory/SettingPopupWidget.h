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
	
	//�ػ� ����Ʈ
	TArray<FIntPoint> Resolutions;

	//ComboBox �ʱ�ȭ
	void PopulateResolutionOptions();

	//�ػ� ����
	UFUNCTION()
	void OnResolutionSelected(FString SelectedOption, ESelectInfo::Type SelectionType);

	//�ػ� ����
	void ApplyResolution(FIntPoint Resolution);

};
