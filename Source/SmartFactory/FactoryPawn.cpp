// Fill out your copyright notice in the Description page of Project Settings.


#include "FactoryPawn.h"

// Sets default values
AFactoryPawn::AFactoryPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AFactoryPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFactoryPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AFactoryPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}
