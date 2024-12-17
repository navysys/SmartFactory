// Fill out your copyright notice in the Description page of Project Settings.


#include "AllAlarmWidgetComponent.h"
#include "AlarmWidgetComponent.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include <Kismet/GameplayStatics.h>
#include "SystemPopupWidget.h"
#include <Components/VerticalBox.h>
#include <Components/VerticalBoxSlot.h>

void UAllAlarmWidgetComponent::NativeConstruct()
{

}

void UAllAlarmWidgetComponent::AddRow(const FAllAlarmChildDataStruct& FilteredData)
{
    if (IsValid(AlarmNo))
    {
        AlarmNo->SetText(FText::AsNumber(FilteredData.AlarmNo));

        MCName->SetText(FText::FromString(FilteredData.MCName));

        Contents->SetText(FText::FromString(FilteredData.Contents));

        regdate->SetText(FText::FromString(FilteredData.regdate));

        DataType1->SetText(FText::FromString(FilteredData.dataType));

        DataType2->SetText(FText::FromString(FilteredData.dataType2));

        alarmStatus->SetText(FText::FromString(FilteredData.alarmStatus));
    }
}

void UAllAlarmWidgetComponent::AlarmDataButtonCallBack()
{

}
