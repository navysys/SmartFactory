// Fill out your copyright notice in the Description page of Project Settings.


#include "Maker.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/MaterialInstanceDynamic.h"
#include <Kismet/GameplayStatics.h>
#include "FactoryPlayerController.h"

// Sets default values
AMaker::AMaker()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MakerMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));

	MakerMesh->SetupAttachment(RootComponent);

	MakerMesh->bHiddenInGame = true;
}

void AMaker::CheckData(float DataValue)
{
		// 값에 따라 색상 변경
		if (DataValue >= 0.0f && DataValue <= 2.0f)
		{
			MakerMesh->SetMaterial(0, Green);
		}
		else
		{
			MakerMesh->SetMaterial(0, Red);
		}
}

void AMaker::AttachActor(FVector ActorLocation)
{
	FVector AttachLocation = ActorLocation + FVector(0.0f, 0.0f, 30.0f);

	UE_LOG(LogTemp, Warning, TEXT("AttachActor"));

	SetActorLocation(AttachLocation);
}

// Called when the game starts or when spawned
void AMaker::BeginPlay()
{
	Super::BeginPlay();

	AFactoryPlayerController* FactoryPlayerController = Cast<AFactoryPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));

	FactoryPlayerController->MakerArray.Add(this);

	
}

// Called every frame
void AMaker::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

