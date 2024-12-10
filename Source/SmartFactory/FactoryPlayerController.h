// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputActionValue.h"
#include "FactoryPlayerController.generated.h"


class UMainWidget;
class UInputMappingContext;
class UInputAction;

UCLASS()
class SMARTFACTORY_API AFactoryPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;

	virtual void SetupInputComponent() override;

	TObjectPtr<UMainWidget> MainWidget;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> MainWidgetClass;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UInputMappingContext> IMC;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UInputAction> IA_Move;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UInputAction> IA_Rotation;

	void Move(const FInputActionValue& Value);
	void Rotation(const FInputActionValue& Value);

	void CreateTreeView(int Index, int ChildIndex);
};
