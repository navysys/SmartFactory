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

	bool IsClicked = false;

	MeshComp = CreateDefaultSubobject<UMeshComponent>(TEXT("FactorySource"));

	CameraPosition = CreateDefaultSubobject<USceneComponent>(TEXT("CameraPosition"));


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
}


void AFactorySourceActor::ResourceHighLightOnOff(bool HighLightState)
{
	if (IsValid(MeshComp))
	{
		if (HighLightState == true)
		{
			MeshComp->SetRenderCustomDepth(false);
		}
		else if (HighLightState == false)
		{
			MeshComp->SetRenderCustomDepth(true);
		}
	}
}

void AFactorySourceActor::CreateWidget()
{
	AFactoryPlayerController* PC = Cast<AFactoryPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (IsValid(PC))
	{
		PC->CreateTreeItem("Test", "Test");
	}
}

// Called every frame
void AFactorySourceActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

