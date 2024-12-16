// Fill out your copyright notice in the Description page of Project Settings.

#include "AlarmWidgetComponent.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include <Kismet/GameplayStatics.h>
#include "SystemPopupWidget.h"
#include <Components/VerticalBox.h>
#include <Components/VerticalBoxSlot.h>


void UAlarmWidgetComponent::NativeConstruct()
{
	Super::NativeConstruct();

	//ModifyButton = Cast<UButton>(GetWidgetFromName(TEXT("ModifyButton")));

    if (IsValid(ModifyButton))
    {
        ModifyButton->OnClicked.AddDynamic(this, &UAlarmWidgetComponent::ModifyButtonCallBack);
    }

	/*AFactoryPlayerController* FactoryPlayerController = Cast<AFactoryPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));

	AddRow(FactoryPlayerController->FullDataArray);*/
}

void UAlarmWidgetComponent::AddRow(const FAllAlarmChildDataStruct& FilteredData)
{
    if (IsValid(AlarmNo))
    {
        AlarmNo->SetText(FText::AsNumber(FilteredData.AlarmNo));

        MCName->SetText(FText::FromString(FilteredData.MCName));

        Contents->SetText(FText::FromString(FilteredData.Contents));

        ThresholdMax->SetText(FText::AsNumber(FilteredData.ThresholdMax));

        ThresholdMin->SetText(FText::AsNumber(FilteredData.ThresholdMin));
    }

        //USystemPopupWidget* SystemPopup = CreateWidget<USystemPopupWidget>(this, SystemPopupWidget);

        //// 부모 VerticalBox에 추가
        //UVerticalBoxSlot* NewSlot = SystemPopup->ContentVerticalBox->AddChildToVerticalBox(this);
        //if (NewSlot)
        //{
        //    // 레이아웃 조정 가능
        //    NewSlot->SetPadding(FMargin(5.f));
        //    NewSlot->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Center);
        //}
}

void UAlarmWidgetComponent::ModifyButtonCallBack()
{

}
