// Fill out your copyright notice in the Description page of Project Settings.


#include "SystemPopupWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/GridPanel.h"
#include "Components/GridSlot.h"


void USystemPopupWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	
}

void USystemPopupWidget::AddRow(int32 RowIndex, const TArray<FString>& RowData)
{
    if (!AlarmTableGird) return;

    for (int32 ColIndex = 0; ColIndex < RowData.Num(); ++ColIndex)
    {
        // 새 TextBlock 생성
        UTextBlock* NewTextBlock = NewObject<UTextBlock>(this);
        if (NewTextBlock)
        {
            NewTextBlock->SetText(FText::FromString(RowData[ColIndex]));

            // GridSlot에 배치
            UGridSlot* GridSlot = AlarmTableGird->AddChildToGrid(NewTextBlock, RowIndex, ColIndex);
            if (GridSlot)
            {
                GridSlot->SetPadding(FMargin(5.0f)); // 패딩 설정
            }
        }
    }

}
