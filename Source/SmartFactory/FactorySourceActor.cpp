// Fill out your copyright notice in the Description page of Project Settings.


#include "FactorySourceActor.h"
#include "Components/StaticMeshComponent.h"
#include "FactoryPlayerController.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AFactorySourceActor::AFactorySourceActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	FactorySource = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FactorySource"));
}

// Called when the game starts or when spawned
void AFactorySourceActor::BeginPlay()
{
	Super::BeginPlay();
	
	 AFactoryPlayerController* PC = Cast<AFactoryPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	 if (IsValid(PC))
	 {
		 PC->FactorySource.Emplace(this);
	 }

	 FTimerHandle Handle;
	 GetWorld()->GetTimerManager().SetTimer(Handle, this, &AFactorySourceActor::CreateWidget, 1.0f, false);

}

void AFactorySourceActor::ResourceHighLightOn()
{
	if (IsValid(FactorySource))
	{
		FactorySource->SetRenderCustomDepth(true);
	}
}

void AFactorySourceActor::ResourceHighLightOff()
{
	if (IsValid(FactorySource))
	{
		FactorySource->SetRenderCustomDepth(false);
	}
}

void AFactorySourceActor::CreateWidget()
{
	AFactoryPlayerController* PC = Cast<AFactoryPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (IsValid(PC))
	{
		PC->CreateTreeItem(0, 0, this);
	}
}

// Called every frame
void AFactorySourceActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

