// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemWidget.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "FactorySourceActor.h"
#include "FactoryPlayerController.h"

void UItemWidget::NativeConstruct()
{
	Super::NativeConstruct();

	ItemName->Text = FText::FromString(ItemText);
	TArray<AFactorySourceActor*> AllActor;
	AllActor = Cast<AFactoryPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0))->FactorySource;
	for (AFactorySourceActor* FindActor : AllActor)
	{
		FString ActorName;
		FindActor->GetName(ActorName);
		if (ActorName == ItemText)
		{
			Actor = FindActor;
		}
	}
}

void UItemWidget::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	
}
