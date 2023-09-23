// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "VPOITrackerComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPointOfInterestFocused, AActor*, NewPOI);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPointsOfInterestCleared);

UCLASS(meta=(DisplayName="Points Of Interest Tracker Component", BlueprintSpawnableComponent))
class POINTSOFINTEREST_API UVPOITrackerComponent : public USphereComponent
{
	GENERATED_BODY()

	UPROPERTY()
	FTimerHandle TimerHandler;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<AActor> ClosestPOI;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TArray<AActor*> POIList;

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);

	UFUNCTION()
	void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION()
	void UpdatePointsOfInterest();

protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(BlueprintAssignable, Category = "Default")
	FOnPointOfInterestFocused OnPointOfInterestFocused;

	UPROPERTY(BlueprintAssignable, Category = "Default")
	FOnPointsOfInterestCleared OnPointsOfInterestCleared;
};
