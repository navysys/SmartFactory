// Fill out your copyright notice in the Description page of Project Settings.


#include "SystemPopupWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/GridPanel.h"
#include "Components/GridSlot.h"
#include <Kismet/GameplayStatics.h>


void USystemPopupWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
    
    AFactoryPlayerController* FactoryPlayerController = Cast<AFactoryPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));

    AddRow(FactoryPlayerController->FullDataArray);
	
}

void USystemPopupWidget::AddRow(const TArray<FAllAlarmChildDataStruct>& FilteredData)
{
    if (!AlarmTableGird) return;

    int32 RowIndex = 0;

    for (const FAllAlarmChildDataStruct& alarm : FilteredData)
    {
        // 각 데이터를 TextBlock으로 변환
        UTextBlock* AlarmNo = NewObject<UTextBlock>(this);
        AlarmNo->SetText(FText::AsNumber(alarm.AlarmNo));

        UTextBlock* MCName = NewObject<UTextBlock>(this);
        MCName->SetText(FText::FromString(alarm.MCName));

        UTextBlock* Contents = NewObject<UTextBlock>(this);
        Contents->SetText(FText::FromString(alarm.Contents));

        UTextBlock* ThresholdMax = NewObject<UTextBlock>(this);
        ThresholdMax->SetText(FText::AsNumber(alarm.ThresholdMax));

        UTextBlock* ThresholdMin = NewObject<UTextBlock>(this);
        ThresholdMin->SetText(FText::AsNumber(alarm.ThresholdMin));

        // Grid Panel에 추가
        AlarmTableGird->AddChildToGrid(AlarmNo)->SetRow(RowIndex);
        AlarmTableGird->AddChildToGrid(AlarmNo)->SetColumn(0);
        AlarmTableGird->AddChildToGrid(MCName)->SetRow(RowIndex);
        AlarmTableGird->AddChildToGrid(MCName)->SetColumn(1);
        AlarmTableGird->AddChildToGrid(Contents)->SetRow(RowIndex);
        AlarmTableGird->AddChildToGrid(Contents)->SetColumn(2);
        AlarmTableGird->AddChildToGrid(ThresholdMax)->SetRow(RowIndex);
        AlarmTableGird->AddChildToGrid(ThresholdMax)->SetColumn(3);
        AlarmTableGird->AddChildToGrid(ThresholdMin)->SetRow(RowIndex);
        AlarmTableGird->AddChildToGrid(ThresholdMin)->SetColumn(4);

        RowIndex++;
    }
}
