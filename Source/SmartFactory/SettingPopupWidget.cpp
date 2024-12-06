// Fill out your copyright notice in the Description page of Project Settings.


#include "SettingPopupWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/ComboBoxString.h"
#include "GameFramework/GameUserSettings.h"

void USettingPopupWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	CloseButton = Cast<UButton>(GetWidgetFromName(TEXT("CloseButton")));

	CloseButton->OnClicked.AddDynamic(this, &USettingPopupWidget::CloseButtonCallback);

	ResetButton = Cast<UButton>(GetWidgetFromName(TEXT("ResetButton")));

	ResetButton->OnClicked.AddDynamic(this, &USettingPopupWidget::ResetButtonCallback);

	if (ResolutionComboBox)
	{
		PopulateResolutionOptions();

		ResolutionComboBox->OnSelectionChanged.AddDynamic(this, &USettingPopupWidget::OnResolutionSelected);
	}

	if (WindowComboBox)
	{
		PopulateWindowModeOption();

		WindowComboBox->OnSelectionChanged.AddDynamic(this, &USettingPopupWidget::OnWindowModeSelected);
	}
}

void USettingPopupWidget::CloseButtonCallback()
{
	RemoveFromParent();

}

void USettingPopupWidget::ResetButtonCallback()
{
	SetWindowMode(EWindowMode::Windowed);
	WindowComboBox->SetSelectedOption(TEXT("Windowed"));

	ApplyResolution(FIntPoint(1280, 720));
	FString CurrentResolutionString = FString::Printf(TEXT( "1280 x 720"));
	ResolutionComboBox->SetSelectedOption(CurrentResolutionString);
}

void USettingPopupWidget::PopulateResolutionOptions()
{
	UGameUserSettings* UserSettings = UGameUserSettings::GetGameUserSettings();
	if (!UserSettings)
	{
		return;
	}

	//콤보박스에 넣을 해상도 입력
	TArray<FIntPoint> SupportedResolutions = {
		FIntPoint(1280, 720),
		FIntPoint(1920, 1080),
		FIntPoint(2560, 1440),
		FIntPoint(3840, 2160)
	};

	//내 해상도 리스트에 넣음
	Resolutions = SupportedResolutions;

	//해상도 리스트 개수만큼 반복
	for (const FIntPoint& Resolution : Resolutions)
	{
		//콤보박스에 해상도 리스트 추가
		FString ResolutionString = FString::Printf(TEXT("%d x %d"), Resolution.X, Resolution.Y);
		ResolutionComboBox->AddOption(ResolutionString);
	}
	//현재 유저 화면 해상도 저장
	FIntPoint CurrentResolution = UserSettings->GetScreenResolution();
	FString CurrentResolutionString = FString::Printf(TEXT("%d x %d"), CurrentResolution.X, CurrentResolution.Y);

	//콤보박스 옵션 선택하면 현재 해상도를 출력
	ResolutionComboBox->SetSelectedOption(CurrentResolutionString);
}

void USettingPopupWidget::OnResolutionSelected(FString SelectedOption, ESelectInfo::Type SelectionType)
{
	for (const FIntPoint& Resolution : Resolutions)
	{
		FString ResolutionString = FString::Printf(TEXT("%d x %d"), Resolution.X, Resolution.Y);

		if (ResolutionString == SelectedOption)
		{
			ApplyResolution(Resolution);
			break;
		}
	}
}

void USettingPopupWidget::ApplyResolution(FIntPoint Resolution)
{
	//현재 게임 유저 세팅
	UGameUserSettings* UserSettings = UGameUserSettings::GetGameUserSettings();

	if (!UserSettings)
	{
		return;
	}

	//해상도 세팅 함수에 현재 해상도 넣음
	UserSettings->SetScreenResolution(Resolution);
	UserSettings->ApplySettings(false);
	UserSettings->SaveSettings();
}

void USettingPopupWidget::PopulateWindowModeOption()
{
	if (WindowComboBox)
	{
		WindowComboBox->AddOption(TEXT("FullScreen"));							//전체화면
		WindowComboBox->AddOption(TEXT("Windowed"));							//창모드
		WindowComboBox->AddOption(TEXT("WindowedFullScreen"));		//창모드(전체화면)

		UGameUserSettings* UserSettings = UGameUserSettings::GetGameUserSettings();
		if (UserSettings)
		{
			EWindowMode::Type CurrentWindowMode = UserSettings->GetFullscreenMode();
			switch (CurrentWindowMode)
			{
			case EWindowMode::Fullscreen:
				WindowComboBox->SetSelectedOption(TEXT("FullScreen"));
				break;

			case EWindowMode::WindowedFullscreen:
				WindowComboBox->SetSelectedOption(TEXT("WindowedFullScreen"));
				break;

			case EWindowMode::Windowed:
				WindowComboBox->SetSelectedOption(TEXT("Windowed"));
				break;

			default:
				break;
			}
		}

	}
}

void USettingPopupWidget::OnWindowModeSelected(FString SelectedOption, ESelectInfo::Type SelectionType)
{
	if (SelectedOption == TEXT("FullScreen"))
	{
		SetWindowMode(EWindowMode::Fullscreen);
	}
	else if (SelectedOption == TEXT("WindowedFullScreen"))
	{
		SetWindowMode(EWindowMode::WindowedFullscreen);
	}
	else if (SelectedOption == TEXT("Windowed"))
	{
		SetWindowMode(EWindowMode::Windowed);
	}
}

void USettingPopupWidget::SetWindowMode(EWindowMode::Type WindowMode)
{
	UGameUserSettings* UserSettings = UGameUserSettings::GetGameUserSettings();
	if (UserSettings)
	{
		UserSettings->SetFullscreenMode(WindowMode);
		UserSettings->ApplySettings(false);
		UserSettings->SaveSettings();
	}
}


