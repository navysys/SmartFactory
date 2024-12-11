// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FactorySourceActor.h"
#include "FactoryStaticActor.generated.h"

/**
 * 
 */
UCLASS()
class SMARTFACTORY_API AFactoryStaticActor : public AFactorySourceActor
{
	GENERATED_BODY()
	

public:
	AFactoryStaticActor();

public:
	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//UStaticMeshComponent* FactorySource;
};
