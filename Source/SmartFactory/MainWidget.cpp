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
<<<<<<< HEAD

=======
>>>>>>> aae9f8e9e4f9c8934a7954fd670409cfaf5d10f0
	if (IsValid(ExitButton))
	{
		ExitButton->OnClicked.AddDynamic(this, &UMainWidget::ExitButtonClicked);
	}
<<<<<<< HEAD

	if (IsValid(HomeButton))
	{
		HomeButton->OnClicked.AddDynamic(this, &UMainWidget::HomeButtonClicked);
	}

	//if (IsValid(AlarmButton))
	//{
	//	AlarmButton->OnClicked.AddDynamic(this, &UMainWidget::AlarmButtonClicked);
	//}
=======
>>>>>>> aae9f8e9e4f9c8934a7954fd670409cfaf5d10f0
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
<<<<<<< HEAD
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
	// ī�޶� ��ġ �ʱ�ȭ
}

void UMainWidget::AlarmButtonClicked()
{

=======
	UKismetSystemLibrary::QuitGame(this, 0, EQuitPreference::Quit, false);
>>>>>>> aae9f8e9e4f9c8934a7954fd670409cfaf5d10f0
}
