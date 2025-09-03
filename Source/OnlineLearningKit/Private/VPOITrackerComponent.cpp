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
			GetWorld()->GetTimerManager().SetTimer(TimerHandler, this, &UVPOITrackerComponent::UpdatePointsOfInterest, .01f, true);
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
			//Make sure that we clear the ClosestPOI when the list is empty
			ClosestPOI = nullptr;
			GetWorld()->GetTimerManager().ClearTimer(TimerHandler);
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
		
	ClosestPOI = POIList[0];
}