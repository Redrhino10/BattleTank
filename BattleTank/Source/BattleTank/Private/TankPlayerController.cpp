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

    UE_LOG(LogTemp, Error, TEXT("LineTraceRange = %f"), LineTraceRange);
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
        // UE_LOG(LogTemp, Warning, TEXT("Hit Location: %s"), *HitLocation.ToString());

        //AimAT
        GetControlledTank()->AimAt(HitLocation);
    }


    // 
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
    
    FVector LookDirection;
    if (GetLookDirection(ScreenLocation, LookDirection))
    {
        GetLookVectorHitLocation(LookDirection, OutHitLocation);
        //UE_LOG(LogTemp, Warning, TEXT("Look direction: %s"), *LookDirection.ToString());
    }

    return true;
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const
{
    FHitResult HitResult;
    FVector StartLocation = PlayerCameraManager->GetCameraLocation();
    FVector EndLocation = StartLocation + (LookDirection * LineTraceRange);

    // Experimental line
    FCollisionQueryParams CollisionParams;
    CollisionParams.AddIgnoredActor(Cast<AActor>(GetPawn()));


    if(GetWorld()->LineTraceSingleByChannel(
        HitResult,
        StartLocation,
        EndLocation,
        ECollisionChannel::ECC_Visibility,
        CollisionParams)
        )
    {
        HitLocation = HitResult.Location;
        //UE_LOG(LogTemp, Warning, TEXT("HIT"));
        return true;
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("%s\n, %s\n, %s\n, %s\n, %s\n"),
        *HitResult.ToString(),
        *HitResult.Location.ToString(),
        *StartLocation.ToString(),
        *EndLocation.ToString(),
        *LookDirection.ToString());

        HitLocation = FVector(0);
    }

    return false;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const
{
    FVector CameraWorldLocation;    //To be discarded, apparently?
    return DeprojectScreenPositionToWorld(
        ScreenLocation.X,
        ScreenLocation.Y,
        CameraWorldLocation,
        LookDirection
    );
}