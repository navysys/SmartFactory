// Fill out your copyright notice in the Description page of Project Settings.


#include "FactoryStaticActor.h"



AFactoryStaticActor::AFactoryStaticActor()
{
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	RootComponent = MeshComp;

	CameraPosition->SetupAttachment(RootComponent);
}