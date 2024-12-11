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
	SendHttpRequest();

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

void AFactoryPlayerController::CreateTreeItem(FString NodeID, FString ParentID, AActor* OwningActor)
{
	if (IsValid(MainWidget))
	{
		MainWidget->CreateTreeItem(NodeID, ParentID, OwningActor);
	}
}

void AFactoryPlayerController::SendHttpRequest()
{
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe>  HttpRequest = FHttpModule::Get().CreateRequest(); //.CreateRequest();
	HttpRequest->SetURL("http://210.222.227.95/api/vcmdata/gethierarchy/SLITTER/");
	HttpRequest->SetVerb("GET");

	//  &AWebApi::GetDataCallBack �κ� ���� (�������� �޾ƿ� Json �Ľ� �Լ�)
	HttpRequest->OnProcessRequestComplete().BindUObject(this, &AFactoryPlayerController::GetDataCallBack);

	// ��û ����
	if (!HttpRequest->ProcessRequest())
	{
		UE_LOG(LogTemp, Error, TEXT("HTTP ��û�� ó���ϴ� �� �����߽��ϴ�."));
	}
}

void AFactoryPlayerController::GetDataCallBack(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
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

	FString ContentString = Response->GetContentAsString();
	

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

	for (TSharedPtr<FJsonValue> avalue : JsonArray)
	{
		avalue.Get()->AsObject()->TryGetStringField(TEXT("node_id"), NodeIdResult);
		avalue.Get()->AsObject()->TryGetStringField(TEXT("parent_id"), ParentIdResult);
		avalue.Get()->AsObject()->TryGetStringField(TEXT("node_name"), NodeNameResult);
		avalue.Get()->AsObject()->TryGetNumberField(TEXT("type"), TypeResult);
		Child = avalue.Get()->AsObject()->TryGetField(TEXT("child"));

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
		
		//UE_LOG(LogTemp, Warning, TEXT("node_id : %s, parent_id : %s, node_name : %s, type : %d"),*node_id_result, *parent_id_result, *node_name_result, TypeResult);
		
	}
		// �Ľ� ������ ��� (�ش� �Լ������� ��������Ʈ ���, �ٸ� ������� ��� ����)
		//OnGetFruits.Broadcast(CallbackStruct);
}
