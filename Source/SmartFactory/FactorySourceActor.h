// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FactorySourceActor.generated.h"

class UStaticMeshComponent;

UENUM(BlueprintType)
enum class ESelectionTree : uint8
{
	Tree0 UMETA(DisplayName = "Tree0"),
	Tree1 UMETA(DisplayName = "Tree1"),
	Tree2 UMETA(DisplayName = "Tree2")
};

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
	void ResourceHighLightOn();

	UFUNCTION(BlueprintCallable)
	void ResourceHighLightOff();

	UFUNCTION(BlueprintCallable)
	void ResourceHighLightOnOff(bool HighLightState);

	UFUNCTION()
	void CreateWidget();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


public:
	UPROPERTY(EditAnywhere)
	TObjectPtr<USceneComponent> Root;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* FactorySource;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ESelectionTree Tree;

	

};
