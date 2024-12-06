// Fill out your copyright notice in the Description page of Project Settings.


#include "FactoryPlayerController.h"
#include "MainWidget.h"

void AFactoryPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (IsValid(MainWidgetClass))
	{
		MainWidget = CreateWidget<UMainWidget>(this, MainWidgetClass);
		if (IsValid(MainWidget))
		{
			MainWidget->AddToViewport();
			SetShowMouseCursor(true);
		}
	}
}
