// Fill out your copyright notice in the Description page of Project Settings.

#include "AlarmWidgetComponent.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include <Kismet/GameplayStatics.h>
#include "SystemPopupWidget.h"
#include <Components/VerticalBox.h>
#include <Components/VerticalBoxSlot.h>
#include "ChangeAlarmWidget.h"
#include "Maker.h"


void UAlarmWidgetComponent::NativeConstruct()
{
	Super::NativeConstruct();

    UE_LOG(LogTemp, Warning, TEXT("alarmwidgetcomponent native"));

	//ModifyButton = Cast<UButton>(GetWidgetFromName(TEXT("ModifyButton")));

    if (IsValid(ModifyButton))
    {
        ModifyButton->OnClicked.AddDynamic(this, &UAlarmWidgetComponent::ModifyButtonCallBack);
    }

    if (IsValid(ExecuteButton))
    {
        ExecuteButton->OnClicked.AddDynamic(this, &UAlarmWidgetComponent::ExecuteButtonCallBack);
    }
}

void UAlarmWidgetComponent::AddRow(const FEachAlarmChildDataStruct& FilteredData)
{
    if (IsValid(AlarmNo))
    {
        AlarmNo->SetText(FText::AsNumber(FilteredData.AlarmNo));

        MCName->SetText(FText::FromString(FilteredData.MCName));

        Contents->SetText(FText::FromString(FilteredData.Contents));

        dataType->SetText(FText::FromString(FilteredData.dataType));

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
    UChangeAlarmWidget* ChangeAlarmWidget = CreateWidget<UChangeAlarmWidget>(this, ChangeAlarm);

    if(IsValid(ChangeAlarmWidget))
    {
        ChangeAlarmWidget->AddToViewport();
    }
}

void UAlarmWidgetComponent::ExecuteButtonCallBack()
{
    AFactoryPlayerController* FactoryPlayerController = Cast<AFactoryPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));

    AlarmMaker =  FactoryPlayerController->MakerArray[0];

    if (bIsMakerSee == false)
    {
        if (IsValid(AlarmMaker))
        {
            AMaker* Maker = Cast<AMaker>(AlarmMaker);
            Maker->MakerMesh->SetVisibility(true);
            UE_LOG(LogTemp, Warning, TEXT("AlarmMaker false"));
            bIsMakerSee = true;
        }
    }
    else
    {
        if (IsValid(AlarmMaker))
        {
            AMaker* Maker = Cast<AMaker>(AlarmMaker);
            Maker->MakerMesh->SetVisibility(false);
            UE_LOG(LogTemp, Warning, TEXT("AlarmMaker true"));
            bIsMakerSee = false;
        }
    }
    
}
