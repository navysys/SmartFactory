// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemWidget.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "FactorySourceActor.h"
#include "FactoryPlayerController.h"


void UItemWidget::NativeConstruct()
{
	Super::NativeConstruct();

}

void UItemWidget::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	
	UItemWidget* Item = Cast<UItemWidget>(ListItemObject);
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
		FString ActorName = FindActor->GetActorLabel();
		if (ActorName == Item->NodeID)
		{
			UE_LOG(LogTemp, Warning, TEXT("Find Actor"));
			Item->Actor = FindActor;
		}
	}
}
