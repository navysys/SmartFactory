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

	if (ResolutionComboBox)
	{
		PopulateResolutionOptions();

		ResolutionComboBox->OnSelectionChanged.AddDynamic(this, &USettingPopupWidget::OnResolutionSelected);

	}
}

void USettingPopupWidget::CloseButtonCallback()
{
	RemoveFromParent();

}

void USettingPopupWidget::PopulateResolutionOptions()
{
	UGameUserSettings* UserSettings = UGameUserSettings::GetGameUserSettings();
	if (!UserSettings)
	{
		return;
	}

	TArray<FIntPoint> SupportedResolutions = {
		FIntPoint(1280, 720),
		FIntPoint(1920, 1080),
		FIntPoint(2560, 1440),
		FIntPoint(3840, 2160)
	};

	Resolutions = SupportedResolutions;

	for (const FIntPoint& Resolution : Resolutions)
	{
		FString ResolutionString = FString::Printf(TEXT("%d x %d"), Resolution.X, Resolution.Y);
		ResolutionComboBox->AddOption(ResolutionString);
	}

	FIntPoint CurrentResolution = UserSettings->GetScreenResolution();
	FString CurrentResolutionString = FString::Printf(TEXT("%d x %d"), CurrentResolution.X, CurrentResolution.Y);
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
	UGameUserSettings* UserSettings = UGameUserSettings::GetGameUserSettings();
	if (!UserSettings)
	{
		return;
	}
	UserSettings->SetScreenResolution(Resolution);
	UserSettings->ApplySettings(false);
}
