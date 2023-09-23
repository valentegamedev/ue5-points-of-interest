// Fill out your copyright notice in the Description page of Project Settings.


#include "VPOISystemFunctionLibrary.h"

FVector UVPOISystemFunctionLibrary::ClampLookAtVector(FVector ForwardVector, FVector LookAtVector, float ClampAngle)
{
	FVector ClampedLookAt = LookAtVector;
	
	float RadAngle = FMath::Acos(FVector::DotProduct(ForwardVector, LookAtVector));
	float Angle = FMath::RadiansToDegrees(RadAngle);

	if (Angle > ClampAngle)
	{
		FVector DiffVector = LookAtVector - ForwardVector;
		DiffVector *= ClampAngle/Angle;
		ClampedLookAt = ForwardVector + DiffVector;
	}

	return ClampedLookAt;
}