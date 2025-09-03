// Fill out your copyright notice in the Description page of Project Settings.


#include "VPOITrackerComponent.h"
#include "VPOIItemInterface.h"

void UVPOITrackerComponent::BeginPlay()
{
	Super::BeginPlay();
	//Disable ticking for this component
	SetComponentTickEnabled(false);
	 
	//Listen to the overlap events
	OnComponentBeginOverlap.AddDynamic(this, &UVPOITrackerComponent::OnBeginOverlap);
	OnComponentEndOverlap.AddDynamic(this,  &UVPOITrackerComponent::OnEndOverlap);
}

void UVPOITrackerComponent::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
	//Check if the overlapping actor implements the POI Item interface
	if(OtherActor->Implements<UVPOIItemInterface>()) {
		POIList.AddUnique(OtherActor);
	}
		
}
	 
void UVPOITrackerComponent::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	//Check if the overlapping actor implements the POI Item interface
	if(OtherActor->Implements<UVPOIItemInterface>())
	{
		POIList.Remove(OtherActor);
	}
}