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
	//해상도 리스트
	TArray<FIntPoint> Resolutions;

	//ComboBox 초기화
	void PopulateResolutionOptions();

	//해상도 적용
	UFUNCTION()
	void OnResolutionSelected(FString SelectedOption, ESelectInfo::Type SelectionType);

	//해상도 변경
	void ApplyResolution(FIntPoint Resolution);

private:
	//콤보박스에서 창모드 선택
	UFUNCTION()
	void OnWindowModeSelected(FString SelectedOption, ESelectInfo::Type SelectionType);

	//선택한 창모드 게임 세팅 값으로 적용
	void SetWindowMode(EWindowMode::Type WindowMode);

	//콤보박스 요소 추가(콤보박스 생성자 느낌)
	void PopulateWindowModeOption();


};
