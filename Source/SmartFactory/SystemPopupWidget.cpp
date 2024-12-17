// Fill out your copyright notice in the Description page of Project Settings.


#include "SystemPopupWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "AlarmWidgetComponent.h"
#include <Kismet/GameplayStatics.h>
#include <Components/VerticalBox.h>
#include <Components/VerticalBoxSlot.h>
#include "CreateAlarmWidget.h"
#include "SystemAllPopupWidget.h"

void USystemPopupWidget::NativeConstruct()
{
	Super::NativeConstruct();

	CloseButton = Cast<UButton>(GetWidgetFromName(TEXT("CloseButton")));

	CloseButton->OnClicked.AddDynamic(this, &USystemPopupWidget::CloseButtonCallback);

	CreateButton = Cast<UButton>(GetWidgetFromName(TEXT("CreateButton")));

	CreateButton->OnClicked.AddDynamic(this, &USystemPopupWidget::CreateButtonCallback);

	ModelCategoryButton = Cast<UButton>(GetWidgetFromName(TEXT("ModelCategoryButton")));

	ModelCategoryButton->OnClicked.AddDynamic(this, &USystemPopupWidget::ModelCategoryButtonCallback);

	AFactoryPlayerController* FactoryPlayerController = Cast<AFactoryPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	UE_LOG(LogTemp, Warning, TEXT("destination"));

	for (FEachAlarmChildDataStruct childstruct : FactoryPlayerController->EachDataArray)
	{
		UE_LOG(LogTemp, Warning, TEXT("destination"));

		UAlarmWidgetComponent* Alarm = CreateWidget<UAlarmWidgetComponent>(this, AlarmComponent);

		Alarm->AddRow(childstruct);

		ContentVerticalBox->AddChildToVerticalBox(Alarm);
	}
}

void USystemPopupWidget::CloseButtonCallback()
{
	AFactoryPlayerController* FactoryPlayerController = Cast<AFactoryPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	FactoryPlayerController->EachDataArray.Empty();
	RemoveFromParent();

}

void USystemPopupWidget::CreateButtonCallback()
{
	UCreateAlarmWidget* CreateAlarmWidget = CreateWidget<UCreateAlarmWidget>(this, CreateAlarm);

	if (IsValid(CreateAlarmWidget))
	{
		CreateAlarmWidget->AddToViewport();
	}
}

void USystemPopupWidget::ModelCategoryButtonCallback()
{
	USystemAllPopupWidget* AllPopupWidget = CreateWidget<USystemAllPopupWidget>(this, AllAlarm);

	if (IsValid(AllPopupWidget))
	{
		AllPopupWidget->AddToViewport();
	}
}
