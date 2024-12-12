// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "HttpModule.h"
#include "Interfaces/IHttpRequest.h"
#include "Interfaces/IHttpResponse.h"
#include "InputActionValue.h"
#include "FactoryPlayerController.generated.h"



class UMainWidget;
class UInputMappingContext;
class UInputAction;


USTRUCT(BlueprintType)
struct FSLITTERChildDataStruct
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(BlueprintReadWrite)
	FString node_id = "";

	UPROPERTY(BlueprintReadWrite)
	FString parent_id = "";

	UPROPERTY(BlueprintReadWrite)
	FString node_name = "";

	UPROPERTY(BlueprintReadWrite)
	int type = 0;
};


USTRUCT(BlueprintType)
struct FSLITTERMainDataStruct
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(BlueprintReadWrite)
	FString node_id = "";

	UPROPERTY(BlueprintReadWrite)
	FString parent_id = "";

	UPROPERTY(BlueprintReadWrite)
	FString node_name = "";

	UPROPERTY(BlueprintReadWrite)
	int type = 0;

	UPROPERTY(BlueprintReadWrite)
	FSLITTERChildDataStruct child;
};

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

	UPROPERTY(EditAnywhere)
	TArray<class AFactorySourceActor*> FactorySource;

	void Move(const FInputActionValue& Value);

	void Rotation(const FInputActionValue& Value);
	
	void CreateTreeItem(FString NodeID, FString ParentID);

	int Index1= 0;
	int Index2;

public:
	void SendHttpRequest();

	void GetDataCallBack(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);

	
};
