// Fill out your copyright notice in the Description page of Project Settings.


#include "FactorySkeletalActor.h"

AFactorySkeletalActor::AFactorySkeletalActor()
{
	MeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
	RootComponent = MeshComp;

	CameraPosition->SetupAttachment(RootComponent);
}
