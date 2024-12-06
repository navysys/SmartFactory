// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "FactoryPlayerController.generated.h"


class UMainWidget;


UCLASS()
class SMARTFACTORY_API AFactoryPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;


	TObjectPtr<UMainWidget> MainWidget;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> MainWidgetClass;
};
