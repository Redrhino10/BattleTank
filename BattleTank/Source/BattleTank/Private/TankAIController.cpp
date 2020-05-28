// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAIController.h"

void ATankAIController::BeginPlay()
{
    Super::BeginPlay(); //Run the original BeginPlay code first

    UE_LOG(LogTemp, Warning, TEXT("PlayerController BeginPlay()"));

    ATank* PlayerTank = GetPlayerTank();

    if(!PlayerTank)
    {
        // UE_LOG(LogTemp, Warning, TEXT("No AI controller on %s"), *(ControlledTank->GetName()));
        UE_LOG(LogTemp, Warning, TEXT("AIController cant find player"));
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("AIController found player: %s"), *(PlayerTank->GetName()));
    }
}

ATank* ATankAIController::GetControlledTank() const
{
    return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const
{
    APawn* X = GetWorld()->GetFirstPlayerController()->GetPawn();

    if(!X) {return nullptr;}

    return Cast<ATank>(X);
}