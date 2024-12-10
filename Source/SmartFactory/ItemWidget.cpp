// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemWidget.h"
#include "Components/TextBlock.h"

void UItemWidget::NativeConstruct()
{
	Super::NativeConstruct();

	ItemName->Text = FText::FromString(ItemText);
}

void UItemWidget::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	
}
