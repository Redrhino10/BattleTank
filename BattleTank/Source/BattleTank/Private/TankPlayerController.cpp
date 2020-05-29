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
    AimTowardsCrosshair();

    // UE_LOG(LogTemp, Warning, TEXT("Tick working"));
}

ATank* ATankPlayerController::GetControlledTank() const
{
    return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair()
{
    if(!GetControlledTank()) {return;}

    FVector HitLocation;
    if(GetSightRayHitLocation(HitLocation))
    {

    }


    // UE_LOG(LogTemp, Warning, TEXT("Hit Location: %s"), *HitLocation.ToString());
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& OutHitLocation) const
{
    // OutHitLocation = FVector(1.0);
    // return true;

    //Find the crosshair position
    //Deprojcet the position into world direction
    //line trace along look direction

    int32 ViewportSizeX, ViewportSizeY;
    GetViewportSize(ViewportSizeX, ViewportSizeY);

    FVector2D ScreenLocation = FVector2D(
        ViewportSizeX * CrosshairXLocation,
        ViewportSizeY * CrosshairYLocation
    );
    // UE_LOG(LogTemp, Warning, TEXT("Screenlocation: %s"), *ScreenLocation.ToString());
    
    FVector CameraWorldLocation, CameraWorldDirection;
    if (DeprojectScreenPositionToWorld(
        ScreenLocation.X,
        ScreenLocation.Y,
        CameraWorldLocation,
        CameraWorldDirection
    ))
    {
        UE_LOG(LogTemp, Warning, TEXT("Look direction: %s"), *CameraWorldDirection.ToString());
    }


    return true;
}