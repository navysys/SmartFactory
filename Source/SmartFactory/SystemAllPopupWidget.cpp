// Fill out your copyright notice in the Description page of Project Settings.


#include "SystemAllPopupWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "AllAlarmWidgetComponent.h"
#include <Kismet/GameplayStatics.h>
#include <Components/VerticalBox.h>
#include <Components/VerticalBoxSlot.h>

void USystemAllPopupWidget::NativeConstruct()
{
	Super::NativeConstruct();

	CloseButton = Cast<UButton>(GetWidgetFromName(TEXT("CloseButton")));

	CloseButton->OnClicked.AddDynamic(this, &USystemAllPopupWidget::CloseButtonCallback);

	AFactoryPlayerController* FactoryPlayerController = Cast<AFactoryPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	UE_LOG(LogTemp, Warning, TEXT("destination"));

	for (FAllAlarmChildDataStruct childstruct : FactoryPlayerController->AllDataArray)
	{
		UE_LOG(LogTemp, Warning, TEXT("destination"));

		UAllAlarmWidgetComponent* Alarm = CreateWidget<UAllAlarmWidgetComponent>(this, AllAlarmComponent);

		Alarm->AddRow(childstruct);

		ContentVerticalBox->AddChildToVerticalBox(Alarm);
	}

}

void USystemAllPopupWidget::CloseButtonCallback()
{
	RemoveFromParent();
}
