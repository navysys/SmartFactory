// Fill out your copyright notice in the Description page of Project Settings.


#include "FactoryPlayerController.h"
#include "MainWidget.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "FactorySourceActor.h"
#include "JsonUtilities.h"


void AFactoryPlayerController::BeginPlay()
{
	Super::BeginPlay();

	SendSLITTERHttpRequest();

	SendVCMHttpRequest();

	/*SendVCMMainHttpRequest();

	SendAllAlarmHttpRequest();

	SendEachAlarmHttpRequest();*/

	ULocalPlayer* LocalPlayer = GetLocalPlayer();
	if (LocalPlayer)
	{
		UEnhancedInputLocalPlayerSubsystem* InputSubsystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
		if (InputSubsystem)
		{
			InputSubsystem->AddMappingContext(IMC, 0);
		}
	}


	if (IsValid(MainWidgetClass))
	{
		MainWidget = CreateWidget<UMainWidget>(this, MainWidgetClass);
		if (IsValid(MainWidget))
		{
			MainWidget->AddToViewport();
			SetShowMouseCursor(true);
		}
	}
}

void AFactoryPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInputComponent->BindAction(IA_Move, ETriggerEvent::Triggered, this, &AFactoryPlayerController::Move);
		EnhancedInputComponent->BindAction(IA_Rotation, ETriggerEvent::Triggered, this, &AFactoryPlayerController::Rotation);
	}
}


void AFactoryPlayerController::Move(const FInputActionValue& Value)
{
	if (Value.Get<bool>())
	{
		GetPawn()->AddMovementInput(GetPawn()->GetActorRightVector() + GetPawn()->GetActorUpVector());
	}
}

void AFactoryPlayerController::Rotation(const FInputActionValue& Value)
{
	float YawInput = Value.Get<float>();
	UE_LOG(LogTemp, Warning, TEXT("YawInput : %f"), YawInput);
	AddYawInput(YawInput);
}

void AFactoryPlayerController::CreateTreeItem(FString NodeID, FString ParentID)
{
	if (IsValid(MainWidget))
	{
		MainWidget->CreateTreeItem(NodeID, ParentID);
	}
}

void AFactoryPlayerController::SendSLITTERHttpRequest()
{
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe>  HttpRequest = FHttpModule::Get().CreateRequest(); 
	HttpRequest->SetURL("http://210.222.227.95/api/vcmdata/gethierarchy/SLITTER/");
	HttpRequest->SetVerb("GET");

	//  &AWebApi::GetDataCallBack �κ� ���� (�������� �޾ƿ� Json �Ľ� �Լ�)
	HttpRequest->OnProcessRequestComplete().BindUObject(this, &AFactoryPlayerController::GetSLITTERDataCallBack);

	// ��û ����
	if (!HttpRequest->ProcessRequest())
	{
		UE_LOG(LogTemp, Error, TEXT("HTTP ��û�� ó���ϴ� �� �����߽��ϴ�."));
	}
}

void AFactoryPlayerController::GetSLITTERDataCallBack(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
	FSLITTERMainDataStruct MainCallbackStruct; 
	FString NodeIdResult;
	FString ParentIdResult; 
	FString NodeNameResult; 
	TSharedPtr<FJsonValue> Child;
	int TypeResult;

	// ������ ���������� ����� �Ϸ�Ǿ����� �˻�
	if (!bWasSuccessful || !Response.IsValid())
	{
		UE_LOG(LogTemp, Error, TEXT("HTTP ��û ����."));
		return;
	}

	//string���� api ����
	FString ContentString = Response->GetContentAsString();
	
	//Json �����͸� �����ϱ� ���� �迭
	TArray<TSharedPtr<FJsonValue>> JsonArray;
	TSharedRef<TJsonReader<TCHAR>> Reader = TJsonReaderFactory<TCHAR>::Create(ContentString);
	
	if (FJsonSerializer::Deserialize(Reader, JsonArray))
	{
		UE_LOG(LogTemp, Log, TEXT("JSON  Parse Successed: %s"), *ContentString);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("JSON Parse Failed: %s"), *ContentString);
	}

	for (TSharedPtr<FJsonValue> RootData : JsonArray)
	{
		RootData.Get()->AsObject()->TryGetStringField(TEXT("node_id"), NodeIdResult);
		RootData.Get()->AsObject()->TryGetStringField(TEXT("parent_id"), ParentIdResult);
		RootData.Get()->AsObject()->TryGetStringField(TEXT("node_name"), NodeNameResult);
		RootData.Get()->AsObject()->TryGetNumberField(TEXT("type"), TypeResult);
		Child = RootData.Get()->AsObject()->TryGetField(TEXT("child"));

		TArray<TSharedPtr<FJsonValue>> ChildArray = Child.Get()->AsArray();

		FString ChildNodeId;
		FString ChildParentId;
		FString ChildNodeNameId;
		int ChildType;

		for (TSharedPtr<FJsonValue> ChildData : ChildArray)
		{
			ChildData.Get()->AsObject()->TryGetStringField(TEXT("node_id"), ChildNodeId);
			ChildData.Get()->AsObject()->TryGetStringField(TEXT("parent_id"), ChildParentId);
			ChildData.Get()->AsObject()->TryGetStringField(TEXT("node_name"), ChildNodeNameId);
			ChildData.Get()->AsObject()->TryGetNumberField(TEXT("type"), ChildType);

			UE_LOG(LogTemp, Warning, TEXT("ChildNode : %s,  ChildParentId : %s, ChildNodeNameId : %s, ChildType : %d,"), *ChildNodeId, *ChildParentId, *ChildNodeNameId, ChildType);
		}
	}
		// �Ľ� ������ ��� (�ش� �Լ������� ��������Ʈ ���, �ٸ� ������� ��� ����)
		//OnGetFruits.Broadcast(CallbackStruct);
}

void AFactoryPlayerController::SendVCMHttpRequest()
{
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe>  VCMHttpRequest = FHttpModule::Get().CreateRequest(); 
	VCMHttpRequest->SetURL("http://210.222.227.95/api/vcmdata/gethierarchy/VCM/");
	VCMHttpRequest->SetVerb("GET");

	//  &AWebApi::GetDataCallBack �κ� ���� (�������� �޾ƿ� Json �Ľ� �Լ�)
	VCMHttpRequest->OnProcessRequestComplete().BindUObject(this, &AFactoryPlayerController::GetVCMDataCallBack);

	// ��û ����
	if (!VCMHttpRequest->ProcessRequest())
	{
		UE_LOG(LogTemp, Error, TEXT("HTTP Request Failed"));
	}
}

void AFactoryPlayerController::GetVCMDataCallBack(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
	FVCMMainDataStruct MainCallbackStruct;
	FString VCMNodeIdResult;
	FString VCMParentIdResult;
	FString VCMNodeNameResult;
	TSharedPtr<FJsonValue> VCMChild;
	int VCMTypeResult;

	// ������ ���������� ����� �Ϸ�Ǿ����� �˻�
	if (!bWasSuccessful || !Response.IsValid())
	{
		UE_LOG(LogTemp, Error, TEXT("HTTP Response Failed."));
		return;
	}

	//string���� api ����
	FString ContentString = Response->GetContentAsString();

	//Json �����͸� �����ϱ� ���� �迭
	TArray<TSharedPtr<FJsonValue>> JsonArray;
	TSharedRef<TJsonReader<TCHAR>> Reader = TJsonReaderFactory<TCHAR>::Create(ContentString);

	if (FJsonSerializer::Deserialize(Reader, JsonArray))
	{
		UE_LOG(LogTemp, Log, TEXT("JSON  Parse Successed: %s"), *ContentString);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("JSON Parse Failed: %s"), *ContentString);
	}

	for (TSharedPtr<FJsonValue> RootData : JsonArray)
	{
		RootData.Get()->AsObject()->TryGetStringField(TEXT("node_id"), VCMNodeIdResult);
		RootData.Get()->AsObject()->TryGetStringField(TEXT("parent_id"), VCMParentIdResult);
		RootData.Get()->AsObject()->TryGetStringField(TEXT("node_name"), VCMNodeNameResult);
		RootData.Get()->AsObject()->TryGetNumberField(TEXT("type"), VCMTypeResult);
		VCMChild = RootData.Get()->AsObject()->TryGetField(TEXT("child"));

		TArray<TSharedPtr<FJsonValue>> VCMChildArray = VCMChild.Get()->AsArray();

		FString VCMChildNodeId;
		FString VCMChildParentId;
		FString VCMChildNodeNameId;
		int VCMChildType;

		for (TSharedPtr<FJsonValue> VCMChildData : VCMChildArray)
		{
			VCMChildData.Get()->AsObject()->TryGetStringField(TEXT("node_id"), VCMChildNodeId);
			VCMChildData.Get()->AsObject()->TryGetStringField(TEXT("parent_id"), VCMChildParentId);
			VCMChildData.Get()->AsObject()->TryGetStringField(TEXT("node_name"), VCMChildNodeNameId);
			VCMChildData.Get()->AsObject()->TryGetNumberField(TEXT("type"), VCMChildType);

			UE_LOG(LogTemp, Warning, TEXT("VCMChildNode : %s,  VCMChildParentId : %s, VCMChildNodeNameId : %s, VCMChildType : %d,"), *VCMChildNodeId, *VCMChildParentId, *VCMChildNodeNameId, VCMChildType);
		}
	}
	// �Ľ� ������ ��� (�ش� �Լ������� ��������Ʈ ���, �ٸ� ������� ��� ����)
	//OnGetFruits.Broadcast(CallbackStruct);
}

//void AFactoryPlayerController::SendVCMMainHttpRequest()
//{
//	TSharedRef<IHttpRequest, ESPMode::ThreadSafe>  VCMMainHttpRequest = FHttpModule::Get().CreateRequest();
//	VCMMainHttpRequest->SetURL("http://210.222.227.95/api/vcmdata/getmain");
//	VCMMainHttpRequest->SetVerb("GET");
//
//	//  &AWebApi::GetDataCallBack �κ� ���� (�������� �޾ƿ� Json �Ľ� �Լ�)
//	VCMMainHttpRequest->OnProcessRequestComplete().BindUObject(this, &AFactoryPlayerController::GetVCMMainDataCallBack);
//
//	// ��û ����
//	if (!VCMMainHttpRequest->ProcessRequest())
//	{
//		UE_LOG(LogTemp, Error, TEXT("HTTP Request Failed"));
//	}
//}
//
//void AFactoryPlayerController::GetVCMMainDataCallBack(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
//{
//	FRealTimeVCMMainDataStruct MainCallbackStruct;
//	FString ItemIdResult;
//	FString DataNameResult;
//	FString VCIDResult;
//	FString VCNameResult;
//	int DataValueResult;
//
//	// ������ ���������� ����� �Ϸ�Ǿ����� �˻�
//	if (!bWasSuccessful || !Response.IsValid())
//	{
//		UE_LOG(LogTemp, Error, TEXT("HTTP Response Failed."));
//		return;
//	}
//
//	//string���� api ����
//	FString ContentString = Response->GetContentAsString();
//
//	//Json �����͸� �����ϱ� ���� �迭
//	TArray<TSharedPtr<FJsonValue>> JsonArray;
//	TSharedRef<TJsonReader<TCHAR>> Reader = TJsonReaderFactory<TCHAR>::Create(ContentString);
//
//	if (FJsonSerializer::Deserialize(Reader, JsonArray))
//	{
//		UE_LOG(LogTemp, Log, TEXT("JSON  Parse Successed: %s"), *ContentString);
//	}
//	else
//	{
//		UE_LOG(LogTemp, Error, TEXT("JSON Parse Failed: %s"), *ContentString);
//	}
//
//	for (TSharedPtr<FJsonValue> RootData : JsonArray)
//	{
//		RootData.Get()->AsObject()->TryGetStringField(TEXT("ItemId"), ItemIdResult);
//		RootData.Get()->AsObject()->TryGetStringField(TEXT("DataName"), DataNameResult);
//		RootData.Get()->AsObject()->TryGetStringField(TEXT("VCID"), VCIDResult);
//		RootData.Get()->AsObject()->TryGetStringField(TEXT("VCName"), VCNameResult);
//		RootData.Get()->AsObject()->TryGetNumberField(TEXT("DataValue"), DataValueResult);
//
//		UE_LOG(LogTemp, Warning, TEXT("ItemId : %s,  DataName : %s, VCID : %s, VCName : %s, DataValue : %d"), *ItemIdResult, *DataNameResult, *VCIDResult, *VCNameResult, DataValueResult);
//	}
//	// �Ľ� ������ ��� (�ش� �Լ������� ��������Ʈ ���, �ٸ� ������� ��� ����)
//	//OnGetFruits.Broadcast(CallbackStruct);
//}
//
//void AFactoryPlayerController::SendAllAlarmHttpRequest()
//{
//	TSharedRef<IHttpRequest, ESPMode::ThreadSafe>  AllAlarmHttpRequest = FHttpModule::Get().CreateRequest(); 
//	AllAlarmHttpRequest->SetURL("http://210.222.227.95/api/vcmdata/getalarm/ALL");
//	AllAlarmHttpRequest->SetVerb("GET");
//
//	//  &AWebApi::GetDataCallBack �κ� ���� (�������� �޾ƿ� Json �Ľ� �Լ�)
//	AllAlarmHttpRequest->OnProcessRequestComplete().BindUObject(this, &AFactoryPlayerController::GetAllAlarmDataCallBack);
//
//	// ��û ����
//	if (!AllAlarmHttpRequest->ProcessRequest())
//	{
//		UE_LOG(LogTemp, Error, TEXT("HTTP Request Failed"));
//	}
//}
//
//void AFactoryPlayerController::GetAllAlarmDataCallBack(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
//{
//	FAllAlarmMainDataStruct MainCallbackStruct;
//	int AlarmNoResult;
//	FString MCNameResult;
//	FString ContentsResult;
//	double ThresholdMaxResult;
//	int ThresholdMinResult;
//
//	// ������ ���������� ����� �Ϸ�Ǿ����� �˻�
//	if (!bWasSuccessful || !Response.IsValid())
//	{
//		UE_LOG(LogTemp, Error, TEXT("HTTP Response Failed."));
//		return;
//	}
//
//	//string���� api ����
//	FString ContentString = Response->GetContentAsString();
//
//	//Json �����͸� �����ϱ� ���� �迭
//	TArray<TSharedPtr<FJsonValue>> JsonArray;
//	TSharedRef<TJsonReader<TCHAR>> Reader = TJsonReaderFactory<TCHAR>::Create(ContentString);
//
//	if (FJsonSerializer::Deserialize(Reader, JsonArray))
//	{
//		UE_LOG(LogTemp, Log, TEXT("JSON  Parse Successed: %s"), *ContentString);
//	}
//	else
//	{
//		UE_LOG(LogTemp, Error, TEXT("JSON Parse Failed: %s"), *ContentString);
//	}
//
//	for (TSharedPtr<FJsonValue> RootData : JsonArray)
//	{
//		RootData.Get()->AsObject()->TryGetNumberField(TEXT("AllAlarmNo"), AlarmNoResult);
//		RootData.Get()->AsObject()->TryGetStringField(TEXT("AllAlarmMCName"), MCNameResult);
//		RootData.Get()->AsObject()->TryGetStringField(TEXT("AllAlarmContents"), ContentsResult);
//		RootData.Get()->AsObject()->TryGetNumberField(TEXT("AllAlarmThresholdMax"), ThresholdMaxResult);
//		RootData.Get()->AsObject()->TryGetNumberField(TEXT("AllAlarmThresholdMin"), ThresholdMinResult);
//
//		UE_LOG(LogTemp, Warning, TEXT("AllAlarmAlarmNo : %d,  AllAlarmMCName : %s, AllAlarmContents : %s, AllAlarmThresholdMax : %f, AllAlarmThresholdMin : %d"), AlarmNoResult, *MCNameResult, *ContentsResult, ThresholdMaxResult, ThresholdMinResult);
//	}
//	// �Ľ� ������ ��� (�ش� �Լ������� ��������Ʈ ���, �ٸ� ������� ��� ����)
//	//OnGetFruits.Broadcast(CallbackStruct);
//}
//
//void AFactoryPlayerController::SendEachAlarmHttpRequest()
//{
//	TSharedRef<IHttpRequest, ESPMode::ThreadSafe>  EachAlarmHttpRequest = FHttpModule::Get().CreateRequest(); 
//	EachAlarmHttpRequest->SetURL("http://210.222.227.95/api/vcmdata/getalarm/ALL");
//	EachAlarmHttpRequest->SetVerb("GET");
//
//	//  &AWebApi::GetDataCallBack �κ� ���� (�������� �޾ƿ� Json �Ľ� �Լ�)
//	EachAlarmHttpRequest->OnProcessRequestComplete().BindUObject(this, &AFactoryPlayerController::GetEachAlarmDataCallBack);
//
//	// ��û ����
//	if (!EachAlarmHttpRequest->ProcessRequest())
//	{
//		UE_LOG(LogTemp, Error, TEXT("HTTP Request Failed"));
//	}
//}
//
//void AFactoryPlayerController::GetEachAlarmDataCallBack(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
//{
//	FEachAlarmMainDataStruct MainCallbackStruct;
//	int AlarmNoResult;
//	FString MCNameResult;
//	FString ContentsResult;
//	double ThresholdMaxResult;
//	int ThresholdMinResult;
//
//	// ������ ���������� ����� �Ϸ�Ǿ����� �˻�
//	if (!bWasSuccessful || !Response.IsValid())
//	{
//		UE_LOG(LogTemp, Error, TEXT("HTTP Response Failed."));
//		return;
//	}
//
//	//string���� api ����
//	FString ContentString = Response->GetContentAsString();
//
//	//Json �����͸� �����ϱ� ���� �迭
//	TArray<TSharedPtr<FJsonValue>> JsonArray;
//	TSharedRef<TJsonReader<TCHAR>> Reader = TJsonReaderFactory<TCHAR>::Create(ContentString);
//
//	if (FJsonSerializer::Deserialize(Reader, JsonArray))
//	{
//		UE_LOG(LogTemp, Log, TEXT("JSON  Parse Successed: %s"), *ContentString);
//	}
//	else
//	{
//		UE_LOG(LogTemp, Error, TEXT("JSON Parse Failed: %s"), *ContentString);
//	}
//
//	for (TSharedPtr<FJsonValue> RootData : JsonArray)
//	{
//		RootData.Get()->AsObject()->TryGetNumberField(TEXT("AlarmNo"), AlarmNoResult);
//		RootData.Get()->AsObject()->TryGetStringField(TEXT("MCName"), MCNameResult);
//		RootData.Get()->AsObject()->TryGetStringField(TEXT("Contents"), ContentsResult);
//		RootData.Get()->AsObject()->TryGetNumberField(TEXT("ThresholdMax"), ThresholdMaxResult);
//		RootData.Get()->AsObject()->TryGetNumberField(TEXT("ThresholdMin"), ThresholdMinResult);
//
//		UE_LOG(LogTemp, Warning, TEXT("EachAlarmAlarmNo : %d,  EachAlarmMCName : %s, EachAlarmContents : %s, EachAlarmThresholdMax : %f, EachAlarmThresholdMin : %d"), AlarmNoResult, *MCNameResult, *ContentsResult, ThresholdMaxResult, ThresholdMinResult);
//	}
//	// �Ľ� ������ ��� (�ش� �Լ������� ��������Ʈ ���, �ٸ� ������� ��� ����)
//	//OnGetFruits.Broadcast(CallbackStruct);
//}
