// Fill out your copyright notice in the Description page of Project Settings.


#include "FactoryPawn.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/FloatingPawnMovement.h"


// Sets default values
AFactoryPawn::AFactoryPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComp = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = RootComp;

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArmComp->SetupAttachment(RootComponent);

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComp->SetupAttachment(SpringArmComp);

	PawnMovementComp = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("PawnMovement"));
}

// Called when the game starts or when spawned
void AFactoryPawn::BeginPlay()
{
	Super::BeginPlay();
	
	StartPos = GetActorLocation();
}

// Called every frame
void AFactoryPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (IsValid(SpringArmComp))
	{
		
		float ArmLength = SpringArmComp->TargetArmLength;
		if (SpeedValue > 0.1f)
		{
			if (ArmLength < 400.0f)
			{
				Speed = Speed + 50.0f * DeltaTime;
				if (Speed > 200.0f)
				{
					Speed = 200.0f;
				}
			}
			else
			{
				SpeedValue = 0;
			}
		}
		else if (SpeedValue < -0.1f)
		{
			if (ArmLength > 100.0f)
			{
				Speed = Speed - 50.0f * DeltaTime;
				if (Speed < -200.0f)
				{
					Speed = -200.0f;
				}
			}
			else
			{
				SpeedValue = 0;
			}
		}

		if(SpeedValue == 0)
		{
			Speed = Speed - 300.0f * DeltaTime;
			if (Speed < 0)
			{
				Speed = 0;
			}
		}
		SpringArmComp->TargetArmLength -= Speed;
	}

}

// Called to bind functionality to input
void AFactoryPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);



}

void AFactoryPawn::IncreaseSpringArmLength(bool Value)
{
	SpeedValue = Value;
}

void AFactoryPawn::DecreaseSpringArmLength(bool Value)
{
}

void AFactoryPawn::SetStartPos()
{
	SetActorLocation(StartPos);
	SetActorRotation(StartRot);
}

