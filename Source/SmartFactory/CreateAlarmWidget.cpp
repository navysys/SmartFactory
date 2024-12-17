// Fill out your copyright notice in the Description page of Project Settings.


#include "CreateAlarmWidget.h"
#include "Components/Button.h"

void UCreateAlarmWidget::NativeConstruct()
{
	CloseButton = Cast<UButton>(GetWidgetFromName(TEXT("CloseButton")));

	CloseButton->OnClicked.AddDynamic(this, &UCreateAlarmWidget::CloseButtonCallBack);
}

void UCreateAlarmWidget::CloseButtonCallBack()
{
	RemoveFromParent();
}
