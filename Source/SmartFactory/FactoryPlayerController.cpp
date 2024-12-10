// Fill out your copyright notice in the Description page of Project Settings.


#include "FactoryPlayerController.h"
#include "MainWidget.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"

void AFactoryPlayerController::BeginPlay()
{
	Super::BeginPlay();

	ULocalPlayer* LocalPlayer = GetLocalPlayer();
	if (LocalPlayer)
	{
		UEnhancedInputLocalPlayerSubsystem* InputSubsystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
		if (InputSubsystem)
		{
			InputSubsystem->AddMappingContext(IMC, 0);
		}
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

void AFactoryPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInputComponent->BindAction(IA_Move, ETriggerEvent::Triggered, this, &AFactoryPlayerController::Move);
		EnhancedInputComponent->BindAction(IA_Rotation, ETriggerEvent::Triggered, this, &AFactoryPlayerController::Rotation);
	}
}

void AFactoryPlayerController::Move(const FInputActionValue& Value)
{
	if (Value.Get<bool>())
	{
		GetPawn()->AddMovementInput(GetPawn()->GetActorRightVector() + GetPawn()->GetActorUpVector());
	}
}

void AFactoryPlayerController::Rotation(const FInputActionValue& Value)
{
	float YawInput = Value.Get<float>();
	UE_LOG(LogTemp, Warning, TEXT("YawInput : %f"), YawInput);
	AddYawInput(YawInput);
}

void AFactoryPlayerController::CreateTreeView(int Index, int ChildIndex)
{
	MainWidget->CreateEntryWidget(Index, ChildIndex);
}
