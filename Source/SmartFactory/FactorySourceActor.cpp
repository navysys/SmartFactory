// Fill out your copyright notice in the Description page of Project Settings.


#include "FactorySourceActor.h"
#include "Components/StaticMeshComponent.h"

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

// Called every frame
void AFactorySourceActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

