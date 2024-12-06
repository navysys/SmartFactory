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

	//�޺��ڽ��� ���� �ػ� �Է�
	TArray<FIntPoint> SupportedResolutions = {
		FIntPoint(1280, 720),
		FIntPoint(1920, 1080),
		FIntPoint(2560, 1440),
		FIntPoint(3840, 2160)
	};

	//�� �ػ� ����Ʈ�� ����
	Resolutions = SupportedResolutions;

	//�ػ� ����Ʈ ������ŭ �ݺ�
	for (const FIntPoint& Resolution : Resolutions)
	{
		//�޺��ڽ��� �ػ� ����Ʈ �߰�
		FString ResolutionString = FString::Printf(TEXT("%d x %d"), Resolution.X, Resolution.Y);
		ResolutionComboBox->AddOption(ResolutionString);
	}
	//���� ���� ȭ�� �ػ� ����
	FIntPoint CurrentResolution = UserSettings->GetScreenResolution();
	FString CurrentResolutionString = FString::Printf(TEXT("%d x %d"), CurrentResolution.X, CurrentResolution.Y);

	//�޺��ڽ� �ɼ� �����ϸ� ���� �ػ󵵸� ���
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
	//���� ���� ���� ����
	UGameUserSettings* UserSettings = UGameUserSettings::GetGameUserSettings();

	if (!UserSettings)
	{
		return;
	}

	//�ػ� ���� �Լ��� ���� �ػ� ����
	UserSettings->SetScreenResolution(Resolution);
	UserSettings->ApplySettings(false);
	UserSettings->SaveSettings();
}

void USettingPopupWidget::PopulateWindowModeOption()
{
	if (WindowComboBox)
	{
		WindowComboBox->AddOption(TEXT("FullScreen"));							//��üȭ��
		WindowComboBox->AddOption(TEXT("Windowed"));							//â���
		WindowComboBox->AddOption(TEXT("WindowedFullScreen"));		//â���(��üȭ��)

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


