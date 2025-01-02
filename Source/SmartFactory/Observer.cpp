// Fill out your copyright notice in the Description page of Project Settings.


#include "Observer.h"
#include "Kismet/GameplayStatics.h"
#include "FactoryPlayerController.h"
#include "MainWidget.h"

UObserver* UObserver::Instance = nullptr;	

UObserver::~UObserver()
{
	if (Instance && Instance->IsRooted())
	{
		Instance->RemoveFromRoot();
	}
}

UObserver* UObserver::GetObserver()
{
	if (!IsValid(Instance))
	{
		Instance = NewObject<UObserver>();
		Instance->AddToRoot();
	}

	return Instance;
}

void UObserver::subscribe()
{
	// widget 의 델리게이트
	//OnWidgetClicked.AddDynamic(this, &UObserver::Callback);
}

void UObserver::Callback(UUserWidget* InWidget)
{
	/*UMainWidget* MainWidget =Cast<UMainWidget>(InWidget);

	if (IsValid(MainWidget))
	{
		MainWidget->ExitButtonClicked();
	}*/
	OnWidgetClicked.Broadcast(InWidget);
}
