// Fill out your copyright notice in the Description page of Project Settings.


#include "PopupModuleWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Kismet/KismetSystemLibrary.h"
#include "FactorySourceActor.h"
#include "Kismet/GameplayStatics.h"

void UPopupModuleWidget::NativeOnInitialized()
{
	Title_TextBlock = Cast<UTextBlock>(GetWidgetFromName(TEXT("Title_TextBlock")));

	Content_TextBlock = Cast<UTextBlock>(GetWidgetFromName(TEXT("Content_TextBlock")));

	Quit_Button = Cast<UButton>(GetWidgetFromName(TEXT("Quit_Button")));

	Quit_Button->OnClicked.AddDynamic(this, &UPopupModuleWidget::QuitProgram);

	Cancel_Button = Cast<UButton>(GetWidgetFromName(TEXT("Cancel_Button")));

	Cancel_Button->OnClicked.AddDynamic(this, &UPopupModuleWidget::CancelButtonCallBack);
}

void UPopupModuleWidget::QuitProgram()
{
	UKismetSystemLibrary::QuitGame(this, 0, EQuitPreference::Quit, false);
}

void UPopupModuleWidget::CancelButtonCallBack()
{
	UWorld* World = GetWorld();

	AFactorySourceActor* TargetActor = Cast<AFactorySourceActor>(UGameplayStatics::GetActorOfClass(World, AFactorySourceActor::StaticClass()));
	if (TargetActor)
	{
		TargetActor->ResourceHighLightOn();
	}
	//RemoveFromParent();
}

void UPopupModuleWidget::SetPopupTitleText(const FText& NewText)
{
	if (IsValid(Title_TextBlock))
	{
		Title_TextBlock->SetText(NewText);
	}
	
}

void UPopupModuleWidget::SetPopupContentText(const FText& NewText)
{
	if (IsValid(Content_TextBlock))
	{
		Content_TextBlock->SetText(NewText);
	}
}

