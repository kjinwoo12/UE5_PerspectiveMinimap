// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameplayTagContainer.h"
#include "MapActorClassifierComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FMapActorRegisteredSignature, FGameplayTag, CategoryTag, AActor*, Actor);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FMapActorUnregisteredSignature, FGameplayTag, CategoryTag, AActor*, Actor);

USTRUCT(BlueprintType)
struct FMapActorCategory
{
	GENERATED_BODY()

	FMapActorCategory()
	{
		Actors.Init(nullptr, 0);
	};

	TArray<AActor*> Actors;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PERSPECTIVEMINIMAPRUNTIME_API UMapActorClassifierComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMapActorClassifierComponent();

	UFUNCTION(BlueprintCallable, Category = "Perspective Minimap")
	void RegisterActor(FGameplayTag CategoryTag, AActor* Actor);

	UFUNCTION(BlueprintCallable, Category = "Perspective Minimap")
	void UnregisterActor(FGameplayTag CategoryTag, AActor* Actor);

	UFUNCTION(BlueprintCallable, Category = "Perspective Minimap")
	FMapActorCategory GetCategoryFromTag(FGameplayTag CategoryTag) const;
public:
	UPROPERTY(BlueprintAssignable, Category = "Perspective Minimap")
	FMapActorRegisteredSignature OnMapActorRegistered;

	UPROPERTY(BlueprintAssignable, Category = "Perspective Minimap")
	FMapActorUnregisteredSignature OnMapActorUnregistered;
	
private:
	TMap<FGameplayTag, FMapActorCategory> ActorCategories;
};
