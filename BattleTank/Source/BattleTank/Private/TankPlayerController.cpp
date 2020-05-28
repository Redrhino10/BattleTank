// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay()
{
    Super::BeginPlay(); //Run the original BeginPlay code first

    UE_LOG(LogTemp, Warning, TEXT("PlayerController BeginPlay()"));

    ATank* ControlledTank = GetControlledTank();

    if(!ControlledTank)
    {
        UE_LOG(LogTemp, Warning, TEXT("No Player controller on %s"), *(ControlledTank->GetName()));
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("A Player controller on %s"), *(ControlledTank->GetName()));
    }
}

void ATankPlayerController::Tick(float Deltatime) 
{
    Super::Tick(Deltatime);

    UE_LOG(LogTemp, Warning, TEXT("Tick working"));
}

ATank* ATankPlayerController::GetControlledTank() const
{
    return Cast<ATank>(GetPawn());
}