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
		// Enhanced Input Subsystem�� �����ɴϴ�
		//UEnhancedInputSubsystem* InputSubsystem = LocalPlayer->GetSubsystem<UEnhancedInputSubsystem>();
		//if (InputSubsystem)
		//{
		//	// �����Ϳ��� ������ InputMappingContext�� ���⿡ �Ҵ��մϴ�.
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
