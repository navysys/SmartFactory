// Fill out your copyright notice in the Description page of Project Settings.


#include "FactoryPlayerController.h"
#include "MainWidget.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "FactorySourceActor.h"
#include "JsonUtilities.h"
#include "SystemPopupWidget.h"
#include "TimerManager.h"

void AFactoryPlayerController::BeginPlay()
{
	Super::BeginPlay();

	SendSLITTERHttpRequest();

	SendVCMHttpRequest();

	GetWorldTimerManager().SetTimer(SendMainTimerHandle, this, &AFactoryPlayerController::SendVCMMainHttpRequest, 1.0f, true);

	GetWorldTimerManager().SetTimer(TimerHandle, this, &AFactoryPlayerController::SendAllAlarmHttpRequest, 1.0f, true);

	//SendAllAlarmHttpRequest();

	//SendEachAlarmHttpRequest();

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

void AFactoryPlayerController::Tick(float DeltaTime)
{
	FVector2D CurrentPos(PosX, PosY);
	GetMousePosition(PosX, PosY);
	FVector2D MousePos(PosX, PosY);
	if (IsMove)
	{
		FVector2D Dir = (MousePos - CurrentPos).GetSafeNormal();
		float Dist = FVector2D::Distance(MousePos, CurrentPos) * 0.5f;
		if (Dir.X > 0.1f)
		{
			GetPawn()->SetActorLocation(GetPawn()->GetActorLocation() + Dist * GetPawn()->GetActorRightVector());
		}
		else if (Dir.X < -0.1f)
		{
			GetPawn()->SetActorLocation(GetPawn()->GetActorLocation() + -Dist * GetPawn()->GetActorRightVector());
		}
		
		if (Dir.Y > 0.1f)
		{
			GetPawn()->SetActorLocation(GetPawn()->GetActorLocation() + -Dist * GetPawn()->GetActorUpVector());
		}
		else if (Dir.Y < -0.1f)
		{
			GetPawn()->SetActorLocation(GetPawn()->GetActorLocation() + Dist * GetPawn()->GetActorUpVector());
		}
		
		if(IsValid(TargetActor))
		{
			Cast<AFactorySourceActor>(TargetActor)->ResourceHighLightOnOff(true);
			TargetActor = nullptr;
		}

	}
	else if (IsRotation)
	{
		float RotInput = (MousePos.X - CurrentPos.X) * 0.5f; //0.5f �� �ӵ� ����
		GetPawn()->SetActorRotation(FRotator(0, GetPawn()->GetActorRotation().Yaw + RotInput, 0));
	}
}

void AFactoryPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInputComponent->BindAction(IA_MoveStart, ETriggerEvent::Triggered, this, &AFactoryPlayerController::MoveStart);
		EnhancedInputComponent->BindAction(IA_MoveEnd, ETriggerEvent::Triggered, this, &AFactoryPlayerController::MoveEnd);
		EnhancedInputComponent->BindAction(IA_RotationStart, ETriggerEvent::Triggered, this, &AFactoryPlayerController::RotationStart);
		EnhancedInputComponent->BindAction(IA_RotationEnd, ETriggerEvent::Triggered, this, &AFactoryPlayerController::RotationEnd);
	}
}


void AFactoryPlayerController::EachAlarmTimer(FString FacilityNodeID)
{
	FString NodeID = FacilityNodeID;

	TimerDelegate.BindUFunction(this, FName("SendEachAlarmHttpRequest"), NodeID);

	GetWorldTimerManager().SetTimer(TimerHandle, 
		TimerDelegate,
		1.0f,
		true);
}

void AFactoryPlayerController::MoveStart(const FInputActionValue& Value)
{
	IsMove = true;
}

void AFactoryPlayerController::MoveEnd(const FInputActionValue& Value)
{
	IsMove = false;
}

void AFactoryPlayerController::RotationStart(const FInputActionValue& Value)
{
	IsRotation = true;
	
}

void AFactoryPlayerController::RotationEnd(const FInputActionValue& Value)
{
	IsRotation = false;
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

		CreateTreeItem(NodeIdResult, ParentIdResult);

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

			//UE_LOG(LogTemp, Warning, TEXT("ChildNode : %s,  ChildParentId : %s, ChildNodeNameId : %s, ChildType : %d,"), *ChildNodeId, *ChildParentId, *ChildNodeNameId, ChildType);

			CreateTreeItem(ChildNodeId, ChildParentId);
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

			//UE_LOG(LogTemp, Warning, TEXT("VCMChildNode : %s,  VCMChildParentId : %s, VCMChildNodeNameId : %s, VCMChildType : %d,"), *VCMChildNodeId, *VCMChildParentId, *VCMChildNodeNameId, VCMChildType);
		}
	}
	// �Ľ� ������ ��� (�ش� �Լ������� ��������Ʈ ���, �ٸ� ������� ��� ����)
	//OnGetFruits.Broadcast(CallbackStruct);
}

void AFactoryPlayerController::SendVCMMainHttpRequest()
{
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe>  VCMMainHttpRequest = FHttpModule::Get().CreateRequest();
	VCMMainHttpRequest->SetURL("http://210.222.227.95/api/vcmdata/getmain");
	VCMMainHttpRequest->SetVerb("GET");

	//  &AWebApi::GetDataCallBack �κ� ���� (�������� �޾ƿ� Json �Ľ� �Լ�)
	VCMMainHttpRequest->OnProcessRequestComplete().BindUObject(this, &AFactoryPlayerController::GetVCMMainDataCallBack);

	// ��û ����
	if (!VCMMainHttpRequest->ProcessRequest())
	{
		UE_LOG(LogTemp, Error, TEXT("HTTP Request Failed"));
	}
}

void AFactoryPlayerController::GetVCMMainDataCallBack(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
	FRealTimeVCMMainDataStruct MainCallbackStruct;
	FString MachineId;
	TSharedPtr<FJsonValue> Data;

	FString ItemIdResult;
	FString DataNameResult;
	FString VCIDResult;
	FString VCNameResult;
	int DataValueResult;

	// ������ ���������� ����� �Ϸ�Ǿ����� �˻�
	if (!bWasSuccessful || !Response.IsValid())
	{
		UE_LOG(LogTemp, Error, TEXT("HTTP Response Failed."));
		return;
	}

	//string���� api ����
	FString ContentString = Response->GetContentAsString();

	//Json �����͸� �����ϱ� ���� �迭
	TSharedPtr<FJsonValue> JsonData;
	TSharedRef<TJsonReader<TCHAR>> Reader = TJsonReaderFactory<TCHAR>::Create(ContentString);

	if (FJsonSerializer::Deserialize(Reader, JsonData))
	{
		UE_LOG(LogTemp, Log, TEXT("JSON  Parse Successed: %s"), *ContentString);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("JSON Parse Failed: %s"), *ContentString);
	}

	JsonData.Get()->AsObject()->TryGetStringField(TEXT("machineId"), MachineId);
	Data = JsonData.Get()->AsObject()->TryGetField(TEXT("data"));

	TArray<TSharedPtr<FJsonValue>> VCMChildArray = Data.Get()->AsArray();

	for (TSharedPtr<FJsonValue> VCMMainChild : VCMChildArray)
	{
		VCMMainChild.Get()->AsObject()->TryGetStringField(TEXT("itemId"), ItemIdResult);
		VCMMainChild.Get()->AsObject()->TryGetStringField(TEXT("dataName"), DataNameResult);
		VCMMainChild.Get()->AsObject()->TryGetStringField(TEXT("vcId"), VCIDResult);
		VCMMainChild.Get()->AsObject()->TryGetStringField(TEXT("vcName"), VCNameResult);
		VCMMainChild.Get()->AsObject()->TryGetNumberField(TEXT("dataValue"), DataValueResult);

		if (IsValid(MainWidget))
		{
			MainWidget->UpdateDataWidget(VCNameResult, DataNameResult, DataValueResult);
		}

		//UE_LOG(LogTemp, Warning, TEXT("ItemId : %s,  DataName : %s, VCID : %s, VCName : %s, DataValue : %d"), *ItemIdResult, *DataNameResult, *VCIDResult, *VCNameResult, DataValueResult);
	}
	// �Ľ� ������ ��� (�ش� �Լ������� ��������Ʈ ���, �ٸ� ������� ��� ����)
	//OnGetFruits.Broadcast(CallbackStruct);
}

void AFactoryPlayerController::SendAllAlarmHttpRequest()
{
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe>  AllAlarmHttpRequest = FHttpModule::Get().CreateRequest(); 
	AllAlarmHttpRequest->SetURL("http://210.222.227.95/api/vcmdata/getalarm/ALL");
	AllAlarmHttpRequest->SetVerb("GET");

	//  &AWebApi::GetDataCallBack �κ� ���� (�������� �޾ƿ� Json �Ľ� �Լ�)
	AllAlarmHttpRequest->OnProcessRequestComplete().BindUObject(this, &AFactoryPlayerController::GetAllAlarmDataCallBack);

	// ��û ����
	if (!AllAlarmHttpRequest->ProcessRequest())
	{
		UE_LOG(LogTemp, Error, TEXT("HTTP Request Failed"));
	}
}

void AFactoryPlayerController::GetAllAlarmDataCallBack(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
	AllDataArray.Empty();
	FAllAlarmMainDataStruct MainCallbackStruct;
	int Result;
	int ItemCount;
	TSharedPtr<FJsonValue> ChildData;

	// ������ ���������� ����� �Ϸ�Ǿ����� �˻�
	if (!bWasSuccessful || !Response.IsValid())
	{
		UE_LOG(LogTemp, Error, TEXT("HTTP Response Failed."));
		return;
	}

	//string���� api ����
	FString ContentString = Response->GetContentAsString();

	//Json �����͸� �����ϱ� ���� �迭
	TSharedPtr<FJsonValue> JsonData;
	TSharedRef<TJsonReader<TCHAR>> Reader = TJsonReaderFactory<TCHAR>::Create(ContentString);

	if (FJsonSerializer::Deserialize(Reader, JsonData))
	{
		UE_LOG(LogTemp, Log, TEXT("JSON  Parse Successed: %s"), *ContentString);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("JSON Parse Failed: %s"), *ContentString);
	}

	JsonData.Get()->AsObject()->TryGetNumberField(TEXT("result"), Result);
	JsonData.Get()->AsObject()->TryGetNumberField(TEXT("itemCount"), ItemCount);
	ChildData = JsonData.Get()->AsObject()->TryGetField(TEXT("data"));

	TArray<TSharedPtr<FJsonValue>> AlaramChildData = ChildData.Get()->AsArray();

	FAllAlarmChildDataStruct alarm;

	for (TSharedPtr<FJsonValue> RootData : AlaramChildData)
	{
		RootData.Get()->AsObject()->TryGetNumberField(TEXT("alarmNo"), alarm.AlarmNo);
		RootData.Get()->AsObject()->TryGetStringField(TEXT("mcName"), alarm.MCName);
		RootData.Get()->AsObject()->TryGetStringField(TEXT("contents"), alarm.Contents);
		RootData.Get()->AsObject()->TryGetStringField(TEXT("regdate"), alarm.regdate);
		RootData.Get()->AsObject()->TryGetStringField(TEXT("dataType"), alarm.dataType);
		RootData.Get()->AsObject()->TryGetStringField(TEXT("dataType_2"), alarm.dataType2);
		RootData.Get()->AsObject()->TryGetStringField(TEXT("alarmStatus"), alarm.alarmStatus);

		UE_LOG(LogTemp, Warning, TEXT("alarmno : %d"), alarm.AlarmNo);

		AllDataArray.Add(alarm);
	}
}

void AFactoryPlayerController::SendEachAlarmHttpRequest(FString FacilityNodeID)
{
	/*FString BaseURL = TEXT("http://210.222.227.95/api/vcmdata/getalarm/");*/

	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> EachAlarmHttpRequest = FHttpModule::Get().CreateRequest(); 
	/*EachAlarmHttpRequest->SetURL(BaseURL + FacilityNodeID);*/
	EachAlarmHttpRequest->SetURL("http://210.222.227.95/api/vcmdata/getalarm/VC0010");
	EachAlarmHttpRequest->SetVerb("GET");

	//&AWebApi::GetDataCallBack �κ� ���� (�������� �޾ƿ� Json �Ľ� �Լ�)
	EachAlarmHttpRequest->OnProcessRequestComplete().BindUObject(this, &AFactoryPlayerController::GetEachAlarmDataCallBack);

	// ��û ����
	if (!EachAlarmHttpRequest->ProcessRequest())
	{
		UE_LOG(LogTemp, Error, TEXT("HTTP Request Failed"));
	}
}

void AFactoryPlayerController::GetEachAlarmDataCallBack(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
	EachDataArray.Empty();
	int Result;
	int ItemCount;
	TSharedPtr<FJsonValue> ChildData;

	// ������ ���������� ����� �Ϸ�Ǿ����� �˻�
	if (!bWasSuccessful || !Response.IsValid())
	{
		UE_LOG(LogTemp, Error, TEXT("HTTP Response Failed."));
		return;
	}

	//string���� api ����
	FString ContentString = Response->GetContentAsString();

	//Json �����͸� �����ϱ� ���� �迭
	TSharedPtr<FJsonValue> JsonData;
	TSharedRef<TJsonReader<TCHAR>> Reader = TJsonReaderFactory<TCHAR>::Create(ContentString);

	if (FJsonSerializer::Deserialize(Reader, JsonData))
	{
		UE_LOG(LogTemp, Log, TEXT("JSON  Parse Successed: %s"), *ContentString);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("JSON Parse Failed: %s"), *ContentString);
	}

	JsonData.Get()->AsObject()->TryGetNumberField(TEXT("result"), Result);
	JsonData.Get()->AsObject()->TryGetNumberField(TEXT("itemCount"), ItemCount);
	ChildData = JsonData.Get()->AsObject()->TryGetField(TEXT("data"));

	TArray<TSharedPtr<FJsonValue>> AlaramChildData = ChildData.Get()->AsArray();

	FEachAlarmChildDataStruct alarm;

	for (TSharedPtr<FJsonValue> RootData : AlaramChildData)
	{
		RootData.Get()->AsObject()->TryGetNumberField(TEXT("alarmNo"), alarm.AlarmNo);
		RootData.Get()->AsObject()->TryGetStringField(TEXT("mcName"), alarm.MCName);
		RootData.Get()->AsObject()->TryGetStringField(TEXT("contents"), alarm.Contents);
		RootData.Get()->AsObject()->TryGetStringField(TEXT("dataType"), alarm.dataType);
		RootData.Get()->AsObject()->TryGetNumberField(TEXT("thresholdMax"), alarm.ThresholdMax);
		RootData.Get()->AsObject()->TryGetNumberField(TEXT("thresholdMin"), alarm.ThresholdMin);

		UE_LOG(LogTemp, Warning, TEXT("alarmno : %d"), alarm.AlarmNo);

		EachDataArray.Add(alarm);
		//UE_LOG(LogTemp, Warning, TEXT("AllAlarmAlarmNo : %d,  AllAlarmMCName : %s, AllAlarmContents : %s, AllAlarmThresholdMax : %f, AllAlarmThresholdMin : %d"), AlarmNoResult, *MCNameResult, *ContentsResult, ThresholdMaxResult, ThresholdMinResult);
	}

	//if (IsValid(MainWidget))
	//{
	//	MainWidget->SystemPopupView();
	//}
	// �Ľ� ������ ��� (�ش� �Լ������� ��������Ʈ ���, �ٸ� ������� ��� ����)
	//OnGetFruits.Broadcast(CallbackStruct);
}
