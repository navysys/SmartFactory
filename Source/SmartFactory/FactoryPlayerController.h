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

//SLITTER
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

//VCM
USTRUCT(BlueprintType)
struct FVCMChildDataStruct
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(BlueprintReadWrite)
	FString VCMNodeId = "";

	UPROPERTY(BlueprintReadWrite)
	FString VCMParentId = "";

	UPROPERTY(BlueprintReadWrite)
	FString VCMNodeName = "";

	UPROPERTY(BlueprintReadWrite)
	int VCMType = 0;
};

USTRUCT(BlueprintType)
struct FVCMMainDataStruct
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(BlueprintReadWrite)
	FString VCMNodeId = "";

	UPROPERTY(BlueprintReadWrite)
	FString VCMParentId = "";

	UPROPERTY(BlueprintReadWrite)
	FString VCMNodeName = "";

	UPROPERTY(BlueprintReadWrite)
	int VCMType = 0;

	UPROPERTY(BlueprintReadWrite)
	FVCMChildDataStruct VCMchild;
};

//실시간 데이터
USTRUCT(BlueprintType)
struct FRealTimeVCMChildDataStruct
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(BlueprintReadWrite)
	FString ItemId = "";

	UPROPERTY(BlueprintReadWrite)
	FString DataName = "";

	UPROPERTY(BlueprintReadWrite)
	FString VCID = "";

	UPROPERTY(BlueprintReadWrite)
	FString VCName = "";

	UPROPERTY(BlueprintReadWrite)
	int DataValue = 0;
};

USTRUCT(BlueprintType)
struct FRealTimeVCMMainDataStruct
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(BlueprintReadWrite)
	FString MachineId = "";

	UPROPERTY(BlueprintReadWrite)
	FRealTimeVCMChildDataStruct Data;
};

//전체 알람
USTRUCT(BlueprintType)
struct FAllAlarmChildDataStruct
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(BlueprintReadWrite)
	int AlarmNo = 0;

	UPROPERTY(BlueprintReadWrite)
	FString MCName = "";

	UPROPERTY(BlueprintReadWrite)
	FString Contents = "";

	UPROPERTY(BlueprintReadWrite)
	FString regdate = "";

	UPROPERTY(BlueprintReadWrite)
	FString dataType = "";

	UPROPERTY(BlueprintReadWrite)
	FString dataType2 = "";

	UPROPERTY(BlueprintReadWrite)
	FString alarmStatus = "";
};

USTRUCT(BlueprintType)
struct FAllAlarmMainDataStruct
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(BlueprintReadWrite)
	int Result = 0;

	UPROPERTY(BlueprintReadWrite)
	int ItemCount = 0;

	UPROPERTY(BlueprintReadWrite)
	FAllAlarmChildDataStruct AllAlarmChild;
};

//개별 알람
USTRUCT(BlueprintType)
struct FEachAlarmChildDataStruct
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(BlueprintReadWrite)
	int AlarmNo = 0;

	UPROPERTY(BlueprintReadWrite)
	FString MCName = "";

	UPROPERTY(BlueprintReadWrite)
	FString Contents = "";

	UPROPERTY(BlueprintReadWrite)
	FString dataType = "";

	UPROPERTY(BlueprintReadWrite)
	double ThresholdMax = 0;

	UPROPERTY(BlueprintReadWrite)
	int ThresholdMin = 0;
};

USTRUCT(BlueprintType)
struct FEachAlarmMainDataStruct
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(BlueprintReadWrite)
	int Result = 0;

	UPROPERTY(BlueprintReadWrite)
	int ItemCount = 0;

	UPROPERTY(BlueprintReadWrite)
	FEachAlarmChildDataStruct EachAlarmChild;
};


UCLASS()
class SMARTFACTORY_API AFactoryPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	virtual void SetupInputComponent() override;

	TObjectPtr<UMainWidget> MainWidget;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> MainWidgetClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class USystemPopupWidget> SystemPopupWidget;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UInputMappingContext> IMC;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UInputAction> IA_MoveStart;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UInputAction> IA_MoveEnd;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UInputAction> IA_RotationStart;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UInputAction> IA_RotationEnd;

	UPROPERTY(EditAnywhere)
	TArray<class AFactorySourceActor*> FactorySource;

	UPROPERTY(EditAnywhere)
	TArray<FAllAlarmChildDataStruct> AllDataArray;

	UPROPERTY(EditAnywhere)
	TArray<FEachAlarmChildDataStruct> EachDataArray;

	UPROPERTY(EditAnywhere)
	TArray<AActor*> MakerArray;

	TObjectPtr<AActor> TargetActor;

	FTimerHandle TimerHandle;

	USystemPopupWidget* Systempopup;

	FTimerHandle SendMainTimerHandle;

	FTimerDelegate TimerDelegate;


	void EachAlarmTimer(FString FacilityNodeID);

	void MoveStart(const FInputActionValue& Value);
	void MoveEnd(const FInputActionValue& Value);
	void RotationStart(const FInputActionValue& Value);
	void RotationEnd(const FInputActionValue& Value);

	void CreateTreeItem(FString NodeID, FString ParentID);

	bool IsMove;
	bool IsRotation;

	float PosX = 0;
	float PosY = 0;

	FVector TargetPos;
	float TargetYaw;

public:
	//설비 SLITTER
	void SendSLITTERHttpRequest();

	void GetSLITTERDataCallBack(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);

	//설비 VCM
	void SendVCMHttpRequest();

	void GetVCMDataCallBack(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);

	//실시간 데이터 
	void SendVCMMainHttpRequest();

	void GetVCMMainDataCallBack(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);

	//전체 알람
	void SendAllAlarmHttpRequest();

	void GetAllAlarmDataCallBack(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);



	//개별 알람
	UFUNCTION()
	void SendEachAlarmHttpRequest(FString FacilityNodeID);

	void GetEachAlarmDataCallBack(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);
};
