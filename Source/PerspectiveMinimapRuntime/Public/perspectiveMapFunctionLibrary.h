// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "PerspectiveMapFunctionLibrary.generated.h"

class UMapActorClassifierComponent;

/**
 * 
 */
UCLASS()
class PERSPECTIVEMINIMAPRUNTIME_API UPerspectiveMapFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, Category = "Perspective Minimap", meta = (WorldContext = "WorldContextObject"))
	static UMapActorClassifierComponent* GetMapActorClassifier(const UObject* WorldContextObject);
};
