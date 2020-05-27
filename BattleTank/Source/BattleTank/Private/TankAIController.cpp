// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAIController.h"

void ATankAIController::BeginPlay()
{
    Super::BeginPlay(); //Run the original BeginPlay code first

    UE_LOG(LogTemp, Warning, TEXT("PlayerController BeginPlay()"));

    ATank* ControlledTank = GetControlledTank();

    if(!ControlledTank)
    {
        UE_LOG(LogTemp, Warning, TEXT("NO"));
        // UE_LOG(LogTemp, Warning, TEXT("Playercontroller not on a tank"));
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("YES"));
        // UE_LOG(LogTemp, Warning, TEXT("Playercontroller: %S"), *(ControlledTank->GetName()));
    }
}

ATank* ATankAIController::GetControlledTank() const
{
    return Cast<ATank>(GetPawn());
}