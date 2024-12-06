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

	UPROPERTY(meta = (BindWidget))
	UComboBoxString* WindowComboBox;

	UPROPERTY(meta = (BindWidget))
	UButton* ResetButton;

public:

private:
	UFUNCTION(BlueprintCallable)
	void CloseButtonCallback();

	UFUNCTION(BlueprintCallable)
	void ResetButtonCallback();
	
private:
	//�ػ� ����Ʈ
	TArray<FIntPoint> Resolutions;

	//ComboBox �ʱ�ȭ
	void PopulateResolutionOptions();

	//�ػ� ����
	UFUNCTION()
	void OnResolutionSelected(FString SelectedOption, ESelectInfo::Type SelectionType);

	//�ػ� ����
	void ApplyResolution(FIntPoint Resolution);

private:
	//�޺��ڽ����� â��� ����
	UFUNCTION()
	void OnWindowModeSelected(FString SelectedOption, ESelectInfo::Type SelectionType);

	//������ â��� ���� ���� ������ ����
	void SetWindowMode(EWindowMode::Type WindowMode);

	//�޺��ڽ� ��� �߰�(�޺��ڽ� ������ ����)
	void PopulateWindowModeOption();


};
