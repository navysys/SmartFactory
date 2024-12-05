// Fill out your copyright notice in the Description page of Project Settings.


#include "SystemPopupWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"


void USystemPopupWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	TestButton = Cast<UButton>(GetWidgetFromName(TEXT("TestButton")));

	TestTextBlock = Cast<UTextBlock>(GetWidgetFromName(TEXT("TestTextBlock")));

	TestButton->OnClicked.AddDynamic(this, &USystemPopupWidget::TestButtonCallback);
}

void USystemPopupWidget::TestButtonCallback()
{
	
}
