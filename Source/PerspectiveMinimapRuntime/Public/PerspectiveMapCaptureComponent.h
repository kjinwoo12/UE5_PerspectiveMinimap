// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneCaptureComponent2D.h"
#include "GameFramework/Actor.h"
#include "GameplayTagContainer.h"
#include "PerspectiveMapCaptureComponent.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType, meta = (BlueprintSpawnableComponent))
class PERSPECTIVEMINIMAPRUNTIME_API UPerspectiveMapCaptureComponent : public USceneCaptureComponent2D
{
	GENERATED_BODY()

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void OnComponentDestroyed(bool bDestroyingHierarchy) override;

public:
	UPerspectiveMapCaptureComponent();

	UFUNCTION()
	void OnMapActorRegistered(FGameplayTag CategoryTag, AActor* Actor);

	UFUNCTION()
	void OnMapActorUnregistered(FGameplayTag CategoryTag, AActor* Actor);

public:
	UPROPERTY(EditAnywhere, Category = "Perspective Minimap")
	FGameplayTagContainer CaptureTargetTagContainer;
};
