// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "FactoryPawn.generated.h"


class UCameraComponent;
class USpringArmComponent;
class UFloatingPawnMovement;

UCLASS()
class SMARTFACTORY_API AFactoryPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AFactoryPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void ChangeSpringArmLength(float Value);

	void SetStartPos();
public:
	UPROPERTY(EditAnywhere)
	TObjectPtr<USceneComponent> RootComp;

	UPROPERTY(EditAnywhere)
	TObjectPtr<USpringArmComponent> SpringArmComp;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UCameraComponent> CameraComp;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UFloatingPawnMovement> PawnMovementComp;

	UPROPERTY(EditAnywhere)
	FVector StartPos;
	FRotator StartRot;

	float SpeedValue = 0;
	float Speed = 0;

	float TargetLength;
};
