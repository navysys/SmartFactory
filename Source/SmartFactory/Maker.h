// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Maker.generated.h"

class UStaticMeshComponent;

UCLASS()
class SMARTFACTORY_API AMaker : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMaker();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* MakerMesh;

	UPROPERTY(EditAnywhere)
	UMaterial* Red;

	UPROPERTY(EditAnywhere)
	UMaterial* Green;

	UFUNCTION()
	void CheckData(float DataValue);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
