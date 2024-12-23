// Fill out your copyright notice in the Description page of Project Settings.


#include "MainWidget.h"
#include "Components/Button.h"
#include "Kismet/KismetSystemLibrary.h"
#include "PopupModuleWidget.h"
#include "ItemWidget.h"
#include "Components/TreeView.h"
#include "FactorySourceActor.h"
#include "Components/TextBlock.h"
#include <Kismet/GameplayStatics.h>
#include "FactoryPlayerController.h"
#include "SystemPopupWidget.h"
#include "SystemAllPopupWidget.h"
#include "DataWidget.h"
#include "Components/ScrollBox.h"
#include "FactoryPawn.h"
#include "Blueprint/UserWidget.h"
#include "TimerManager.h"
#include "Maker.h"


void UMainWidget::NativeConstruct()
{
	Super::NativeConstruct();
	if (IsValid(SettingButton))
	{
		SettingButton->OnClicked.AddDynamic(this, &UMainWidget::SettingButtonClicked);
	}

	if (IsValid(ExitButton))
	{
		ExitButton->OnClicked.AddDynamic(this, &UMainWidget::ExitButtonClicked);
	}

	if (IsValid(HomeButton))
	{
		HomeButton->OnClicked.AddDynamic(this, &UMainWidget::HomeButtonClicked);
	}

	if (IsValid(HomeButton))
	{
		WebCamButton->OnClicked.AddDynamic(this, &UMainWidget::WebCamButtonClicked);
	}

	if (IsValid(AlarmButton))
	{
		AlarmButton->OnClicked.AddDynamic(this, &UMainWidget::AlarmButtonClicked);
	}

	if (IsValid(TreeView))
	{
		TreeView->SetOnGetItemChildren(this, &UMainWidget::GetChildrenForItem);
		TreeView->OnItemClicked().AddUObject(this, &UMainWidget::OnTreeViewItemClicked);
		//TreeView->
	}
	

	//UItemWidget* RootItem = NewObject<UItemWidget>();
	//RootItem->ItemText = TEXT("Root");

	//UItemWidget* ChildItem1 = NewObject<UItemWidget>();
	//ChildItem1->ItemText = TEXT("Child 1");

	//UItemWidget* ChildItem2 = NewObject<UItemWidget>();
	//ChildItem2->ItemText = TEXT("Child 2");

	/*RootItem->Children.Add(ChildItem1);
	RootItem->Children.Add(ChildItem2);*/

	//AddChildToItem(RootItem, ChildItem1);
	//AddChildToItem(RootItem, ChildItem2);

	//// Tree View에 루트 항목 설정
	//TArray<UItemWidget*> Items = { RootItem };
	//TreeView->SetListItems(Items);
}

void UMainWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{

}

void UMainWidget::SettingButtonClicked()
{
	if (IsValid(SettingPopup))
	{
		UUserWidget* SPopup = CreateWidget<UUserWidget>(this, SettingPopup);
		if (IsValid(SPopup))
		{
			SPopup->AddToViewport();
		}
	}
}

void UMainWidget::ExitButtonClicked()
{
	if (IsValid(PopupWidget))
	{
		UPopupModuleWidget* ExitPopup = CreateWidget<UPopupModuleWidget>(this, PopupWidget);
		if (IsValid(ExitPopup))
		{
			ExitPopup->SetPopupTitleText(FText::FromString(TEXT("SHUTTING DOWN")));
			ExitPopup->SetPopupContentText(FText::FromString(TEXT("Do you want Quit?")));
			ExitPopup->AddToViewport();
		}
	}
}

void UMainWidget::HomeButtonClicked()
{
	Cast<AFactoryPawn>(GetOwningPlayerPawn())->SetStartPos();

	AFactoryPlayerController* FPC = Cast<AFactoryPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (IsValid(FPC))
	{
		if (IsValid(FPC->TargetActor))
		{
			Cast<AFactorySourceActor>(FPC->TargetActor)->ResourceHighLightOnOff(true);
			FPC->TargetActor = nullptr;
		}
	}
}

void UMainWidget::WebCamButtonClicked()
{
	CreateWidget<UUserWidget>(this, WebCam)->AddToViewport();
	
}

void UMainWidget::AlarmButtonClicked()
{
	AFactoryPlayerController* PC = Cast<AFactoryPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (IsValid(PC))
	{
		if (IsValid(PC->TargetActor))
		{
			FString FacilityNodeID = Cast<AFactoryPlayerController>(GetOwningPlayer())->TargetActor->GetActorLabel();
			UE_LOG(LogTemp, Warning, TEXT("%s"), *FacilityNodeID);
			PC->EachAlarmTimer(FacilityNodeID);
		}

		
	}
}

void UMainWidget::SystemPopupView()
{
	
}

void UMainWidget::CreateTreeItem(FString NodeID, FString ParentID)
{
	//UE_LOG(LogTemp, Warning, TEXT("ParentID = %S , NodeID = %s"), *ParentID, *NodeID);
	if (ParentID == "")
	{
		UItemWidget* RootItem = NewObject<UItemWidget>();
		RootItem->NodeID = NodeID;

		Items.Add(RootItem);
	}
	else
	{
		UItemWidget* ChildItem = CreateWidget<UItemWidget>(this, UItemWidget::StaticClass());
		ChildItem->NodeID = NodeID;

		for (UItemWidget* ParentItem : Items)
		{
			if (ParentItem->NodeID == ParentID)
			{
				AddChildToItem(ParentItem, ChildItem);
			}
		}
	}
	TreeView->SetListItems(Items);
}

void UMainWidget::GetChildrenForItem(UObject* InItem, TArray<UObject*>& OutChildren)
{
	if (UItemWidget* TreeItem = Cast<UItemWidget>(InItem))
	{
		for (UItemWidget* Child : TreeItem->Children)
		{
			OutChildren.Add(Child);
		}
	}
}

void UMainWidget::AddChildToItem(UItemWidget* ParentItem, UItemWidget* NewChildItem)
{
	if (ParentItem)
	{
		// 부모 항목의 자식 배열에 새 항목 추가
		ParentItem->Children.Add(NewChildItem);

		// Tree View 갱신
		ParentItem->IsExpansion = true;
		TreeView->SetItemExpansion(ParentItem, true); // 부모 노드를 확장
		TreeView->RequestRefresh();
	}
}

void UMainWidget::OnTreeViewItemClicked(UObject* ClickedItem)
{
	
	

	if (UItemWidget* TreeItem = Cast<UItemWidget>(ClickedItem))
	{
		AFactoryPlayerController* PC = Cast<AFactoryPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));

		AFactorySourceActor* SourceActor = Cast<AFactorySourceActor>(TreeItem->Actor);

		FVector ActorLocation =  SourceActor->CameraPosition->GetComponentLocation();

		AMaker* Maker = Cast<AMaker>(PC->MakerArray[0]);

		if (IsValid(Maker))
		{
			UE_LOG(LogTemp, Warning, TEXT("Maker Casting Successed"));
			Maker->AttachActor(ActorLocation);
		}

		if (TreeItem->Children.Num() == 0)
		{
			if (IsValid(SourceActor))
			{
				TArray<AFactorySourceActor*> Source = Cast<AFactoryPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0))->FactorySource;
				for (AFactorySourceActor* FActor : Source)
				{
					FActor->ResourceHighLightOnOff(true);
				}
				SourceActor->ResourceHighLightOnOff(false);
				Cast<AFactoryPlayerController>(GetOwningPlayer())->TargetActor = SourceActor;

				Cast<AFactoryPlayerController>(GetOwningPlayer())->IsTracking = true;
			}
		}
		else
		{
			TArray<AFactorySourceActor*> Source = Cast<AFactoryPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0))->FactorySource;
			for (AFactorySourceActor* FActor : Source)
			{
				FActor->ResourceHighLightOnOff(true);
			}
			for (UItemWidget* ChildItem : TreeItem->Children)
			{
				AFactorySourceActor* ChildActor = Cast<AFactorySourceActor>(ChildItem->Actor);
				if (IsValid(ChildActor))
				{
					ChildActor->ResourceHighLightOnOff(false);
				}
			}
		}
		TreeItem->IsExpansion = true;
		TreeView->SetItemExpansion(ClickedItem, true);
	}
	
	
}

void UMainWidget::UpdateDataWidget(FString VCName, FString DataName, float DataValue)
{
	bool IsSpawned = false;
	for (UDataWidget* Data : Datas)
	{
		if (Data->DataName == DataName)
		{
			IsSpawned = true;
			Data->DataValueText->SetText(FText::AsNumber(DataValue));
		}
	}

	if (!IsSpawned)
	{
		bool IsRootSpawned = false;
		for (UDataWidget* Data : Datas)
		{
			if (Data->DataName == VCName)
			{
				IsRootSpawned = true;
			}
		}

		if (!IsRootSpawned)
		{
			if (IsValid(DataWidgetClass))
			{
				UDataWidget* SpawnedWidget = CreateWidget<UDataWidget>(this, DataWidgetClass);
				SpawnedWidget->DataName = VCName;
				SpawnedWidget->DataNameText->SetText(FText::FromString(VCName));
				//FSlateFontInfo FontInfo;
				//FontInfo.Size = 14;
				//SpawnedWidget->DataNameText->SetFont(FontInfo);
				SpawnedWidget->DataNameText->Font.Size = 14;
				SpawnedWidget->DataValueText->SetText(FText::FromString(TEXT(" ")));

				DataScrollBox->AddChild(SpawnedWidget);
				Datas.Add(SpawnedWidget);

				IsRootSpawned = true;
			}
		}

		if (IsRootSpawned)
		{
			UDataWidget* SpawnedWidget = CreateWidget<UDataWidget>(this, DataWidgetClass);
			SpawnedWidget->DataName = DataName;
			SpawnedWidget->DataValueText->SetText(FText::AsNumber(DataValue));
			FString DataText = FString("    ") + DataName;
			SpawnedWidget->DataNameText->SetText(FText::FromString(DataText));
			
			DataScrollBox->AddChild(SpawnedWidget);
			Datas.Add(SpawnedWidget);
		}
	}
}
