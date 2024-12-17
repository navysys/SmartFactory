// Fill out your copyright notice in the Description page of Project Settings.


#include "SystemPopupWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/GridPanel.h"
#include "Components/GridSlot.h"
#include "AlarmWidgetComponent.h"
#include <Kismet/GameplayStatics.h>
#include <Components/VerticalBox.h>
#include <Components/VerticalBoxSlot.h>

void USystemPopupWidget::NativeConstruct()
{
	Super::NativeConstruct();

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
