// Fill out your copyright notice in the Description page of Project Settings.


#include "MainWidget.h"
#include "Components/Button.h"

void UMainWidget::NativeConstruct()
{
	Super::NativeConstruct();
	if (IsValid(SettingButton))
	{
		SettingButton->OnClicked.AddDynamic(this, &UMainWidget::SettingButtonClicked);
	}
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
}
