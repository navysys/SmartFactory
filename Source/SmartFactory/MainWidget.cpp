// Fill out your copyright notice in the Description page of Project Settings.


#include "MainWidget.h"
#include "Components/Button.h"
#include "Kismet/KismetSystemLibrary.h"
#include "PopupModuleWidget.h"


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
	if (IsValid(PopupWidget))
	{
		UPopupModuleWidget* ExitPopup = CreateWidget<UPopupModuleWidget>(this, PopupWidget);
		if (IsValid(ExitPopup))
		{
			ExitPopup->SetPopupTitleText(FText::FromString(TEXT("SHUTTING DOWN")));
			ExitPopup->SetPopupContentText(FText::FromString(TEXT("Do you want Quit?")));
			ExitPopup->AddToViewport();
		}
	}
}

void UMainWidget::HomeButtonClicked()
{
	// 카메라 위치 초기화
}

void UMainWidget::AlarmButtonClicked()
{
}
