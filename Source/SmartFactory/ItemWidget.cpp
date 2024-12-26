// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemWidget.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "FactorySourceActor.h"
#include "FactoryPlayerController.h"
#include "Components/TreeView.h"


void UItemWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (IsValid(ListButton))
	{
		ListButton->OnClicked.AddDynamic(this, &UItemWidget::ListButtonClicked);
	}
}

void UItemWidget::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	
	UItemWidget* Item = Cast<UItemWidget>(ListItemObject);
	RootItem = Item;
	ItemName->SetText(FText::FromString(Item->NodeID));

	//

	if (Item->Children.Num() == 0)
	{
		this->SetPadding(FMargin(20.0f, 0, 0, 0));
	}

	TArray<AFactorySourceActor*> AllActor;
	AllActor = Cast<AFactoryPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0))->FactorySource;

	for (AFactorySourceActor* FindActor : AllActor)
	{
		/*UE_LOG(LogTemp, Warning, TEXT("FInd Actor %s"), *FindActor->GetActorNameOrLabel());*/
		FString ActorName = FindActor->GetActorNameOrLabel();
		if (ActorName == Item->NodeID)
		{
			Item->Actor = FindActor;
		}
	}
}

void UItemWidget::ListButtonClicked()
{
	UTreeView* TreeView = Cast<UTreeView>(GetOwningListView());
	if (IsValid(TreeView))
	{
		
		if (IsExpansion)
		{
			TreeView->SetItemExpansion(RootItem, false);
			IsExpansion = false;
		}
		else
		{
			TreeView->SetItemExpansion(RootItem, true);
			IsExpansion = true;
		}
	}
}
