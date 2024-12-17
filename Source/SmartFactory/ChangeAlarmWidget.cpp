// Fill out your copyright notice in the Description page of Project Settings.


#include "ChangeAlarmWidget.h"
#include "Components/Button.h"

void UChangeAlarmWidget::NativeConstruct()
{
	CloseButton = Cast<UButton>(GetWidgetFromName(TEXT("CloseButton")));

	CloseButton->OnClicked.AddDynamic(this, &UChangeAlarmWidget::CloseButtonCallBack);
}

void UChangeAlarmWidget::CloseButtonCallBack()
{
	RemoveFromParent();
}
