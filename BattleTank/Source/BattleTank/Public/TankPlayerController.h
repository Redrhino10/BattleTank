// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Tank.h"

#include "TankPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
private:
	ATank* GetControlledTank() const;

	// The below two could be virtual, but not nessecary. 
	// They are already virtual
	void BeginPlay() override;
	void Tick(float DeltaTime) override;

	void AimTowardsCrosshair();

	bool GetSightRayHitLocation(FVector& OutHitLocation) const; 

	UPROPERTY(EditAnywhere)
	float CrosshairXLocation = 0.5;

	UPROPERTY(EditAnywhere)
	float CrosshairYLocation = 0.3333;
};
