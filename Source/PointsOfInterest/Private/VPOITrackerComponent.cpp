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
	if(OtherActor->Implements<UVPOIItemInterface>()) {
		if(POIList.Num() == 0)
		{
			GetWorld()->GetTimerManager().SetTimer(TimerHandler, this, &UVPOITrackerComponent::UpdatePointsOfInterest, .1f, true);
		}
		POIList.AddUnique(OtherActor);
	}
	
}

void UVPOITrackerComponent::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if(OtherActor->Implements<UVPOIItemInterface>())
	{
		POIList.Remove(OtherActor);

		if(POIList.Num()==0)
		{
			//If the list is empty and we still have an item as ClosestPOI
			if(ClosestPOI)
			{
				//Notify the OnEndFocus in the item through the interface
				IVPOIItemInterface::Execute_OnEndFocus(ClosestPOI);
			}
			ClosestPOI = nullptr;
			GetWorld()->GetTimerManager().ClearTimer(TimerHandler);
			OnPointsOfInterestCleared.Broadcast();
		}
	}
}

void UVPOITrackerComponent::UpdatePointsOfInterest()
{
	Algo::Sort(POIList, [&](const AActor* A, const AActor* B)
	{
		FVector DistanceToA = A->GetActorLocation() - GetOwner()->GetActorLocation();
		FVector DistanceToB = B->GetActorLocation() - GetOwner()->GetActorLocation();
		
		return DistanceToA.Length() < DistanceToB.Length();
	});

	//If we have a new closest item
	if (ClosestPOI != POIList[0])
	{
		//If we already had a closest item before
		if(ClosestPOI) {
			//Notify the OnEndFocus in the old one
			IVPOIItemInterface::Execute_OnEndFocus(ClosestPOI);
		}
		
		ClosestPOI = POIList[0];
		//Notify the OnBeginFocus in the new one
		IVPOIItemInterface::Execute_OnBeginFocus(ClosestPOI);
		OnPointOfInterestFocused.Broadcast(ClosestPOI);
	}

	//Draw a line from the character to the closest POI Item
	//DrawDebugLine(GetWorld(), GetOwner()->GetActorLocation(), ClosestPOI->GetActorLocation(), FColor::Green, false, -1, 0, 2);
}