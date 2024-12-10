// Fill out your copyright notice in the Description page of Project Settings.


#include "MainWidget.h"
#include "Components/Button.h"
#include "Kismet/KismetSystemLibrary.h"
#include "PopupModuleWidget.h"
#include "ItemWidget.h"
#include "Components/TreeView.h"


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

	//if (IsValid(AlarmButton))
	//{
	//	AlarmButton->OnClicked.AddDynamic(this, &UMainWidget::AlarmButtonClicked);
	//}

	TreeView->SetOnGetItemChildren(this, &UMainWidget::GetChildrenForItem);

	UItemWidget* RootItem = NewObject<UItemWidget>();
	RootItem->ItemText = TEXT("Root");

	UItemWidget* ChildItem1 = NewObject<UItemWidget>();
	ChildItem1->ItemText = TEXT("Child 1");

	UItemWidget* ChildItem2 = NewObject<UItemWidget>();
	ChildItem2->ItemText = TEXT("Child 2");

	/*RootItem->Children.Add(ChildItem1);
	RootItem->Children.Add(ChildItem2);*/

	AddChildToItem(RootItem, ChildItem1);
	AddChildToItem(RootItem, ChildItem2);

	// Tree View에 루트 항목 설정
	TArray<UItemWidget*> Items = {RootItem};
	TreeView->SetListItems( Items);

	TreeView->OnItemClicked().AddUObject(this, &UMainWidget::OnTreeViewItemClicked);
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
	// 카메라 위치 초기화
}

void UMainWidget::AlarmButtonClicked()
{
}

void UMainWidget::CreateEntryWidget(int Index, int ChildIndex)
{
	UItemWidget* ItemWidget = CreateWidget<UItemWidget>(this);
	TreeView->AddItem(ItemWidget);
	UItemWidget* ItemWidget2 = CreateWidget<UItemWidget>(this);
	
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
		TreeView->SetItemExpansion(ParentItem, true); // 부모 노드를 확장
		TreeView->RequestRefresh();
	}
}

void UMainWidget::OnTreeViewItemClicked(UObject* ClickedItem)
{
	if (UItemWidget* TreeItem = Cast<UItemWidget>(ClickedItem))
	{
		// 항목 클릭 시 실행할 동작
		UE_LOG(LogTemp, Log, TEXT("Clicked Item: %s"), *TreeItem->ItemText);
	}
}
