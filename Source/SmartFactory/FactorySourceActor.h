// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FactorySourceActor.generated.h"

class UStaticMeshComponent;


UCLASS()
class SMARTFACTORY_API AFactorySourceActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFactorySourceActor();

public:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	virtual void ResourceHighLightOnOff(bool HighLightState);

	UFUNCTION()
	void CreateWidget();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


public:
	UPROPERTY(EditAnywhere)
	TObjectPtr<UMeshComponent> MeshComp;

	UPROPERTY(EditAnywhere)
	TObjectPtr<USceneComponent> CameraPosition;

};
