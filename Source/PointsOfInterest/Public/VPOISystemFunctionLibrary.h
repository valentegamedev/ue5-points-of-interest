#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "VPOISystemFunctionLibrary.generated.h"

UCLASS()
class POINTSOFINTEREST_API UVPOISystemFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	UFUNCTION(BlueprintPure, meta = (BlueprintThreadSafe))
	static FVector ClampLookAtVector(FVector ForwardVector, FVector LookAtVector, float ClampAngle);
};