// Fill out your copyright notice in the Description page of Project Settings.


#include "FactoryPlayerController.h"
#include "MainWidget.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"

void AFactoryPlayerController::BeginPlay()
{
	Super::BeginPlay();

	ULocalPlayer* LocalPlayer = GetLocalPlayer();
	if (LocalPlayer)
	{
		// Enhanced Input Subsystem을 가져옵니다
		//UEnhancedInputSubsystem* InputSubsystem = LocalPlayer->GetSubsystem<UEnhancedInputSubsystem>();
		//if (InputSubsystem)
		//{
		//	// 에디터에서 만들어둔 InputMappingContext를 여기에 할당합니다.
		//	InputSubsystem->AddMappingContext(InputMappingContext, 0);
		//}
	}


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
