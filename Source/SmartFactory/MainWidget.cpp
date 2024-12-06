// Fill out your copyright notice in the Description page of Project Settings.


#include "MainWidget.h"
#include "Components/Button.h"
#include "Kismet/KismetSystemLibrary.h"

void UMainWidget::NativeConstruct()
{
	Super::NativeConstruct();
	if (IsValid(SettingButton))
	{
		SettingButton->OnClicked.AddDynamic(this, &UMainWidget::SettingButtonClicked);
	}

	if (IsValid(ExitButton))
	{
		ExitButton->OnClicked.AddDynamic(this, &UMainWidget::ExitButtonClicked);
	}

	if (IsValid(HomeButton))
	{
		HomeButton->OnClicked.AddDynamic(this, &UMainWidget::HomeButtonClicked);
	}

	//if (IsValid(AlarmButton))
	//{
	//	AlarmButton->OnClicked.AddDynamic(this, &UMainWidget::AlarmButtonClicked);
	//}

}

void UMainWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{

}

void UMainWidget::SettingButtonClicked()
{
	if (IsValid(SettingPopup))
	{
		UUserWidget* SPopup = CreateWidget<UUserWidget>(this, SettingPopup);
		if (IsValid(SPopup))
		{
			SPopup->AddToViewport();
		}
	}
}

void UMainWidget::ExitButtonClicked()
{
	if (IsValid(ExitPopup))
	{
		UUserWidget* EPopup = CreateWidget<UUserWidget>(this, ExitPopup);
		if (IsValid(EPopup))
		{
			EPopup->AddToViewport();
		}
	}
}

void UMainWidget::HomeButtonClicked()
{
	// 카메라 위치 초기화
}

void UMainWidget::AlarmButtonClicked()
{
	UKismetSystemLibrary::QuitGame(this, 0, EQuitPreference::Quit, false);
}
