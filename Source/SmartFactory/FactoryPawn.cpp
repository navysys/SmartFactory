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
	TargetLength = 0.0f;
}

// Called every frame
void AFactoryPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (TargetLength >= 0.1 || TargetLength <= -0.1f)
	{
		float Value = FMath::FInterpTo(0, TargetLength, DeltaTime, 5.0f);
		//UE_LOG(LogTemp, Warning, TEXT("%f"), Value);
		SpringArmComp->TargetArmLength += Value;
		TargetLength -= Value;
	}
}

// Called to bind functionality to input
void AFactoryPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);



}

void AFactoryPawn::ChangeSpringArmLength(float Value)
{
	TargetLength -= Value * 50.0f;
}


void AFactoryPawn::SetStartPos()
{
	SetActorLocation(StartPos);
	SetActorRotation(StartRot);

}

