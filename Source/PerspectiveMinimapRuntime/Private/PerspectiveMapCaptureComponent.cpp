// Fill out your copyright notice in the Description page of Project Settings.


#include "PerspectiveMapCaptureComponent.h"
#include "PerspectiveMapFunctionLibrary.h"
#include "MapActorClassifierComponent.h"

// Sets default values
UPerspectiveMapCaptureComponent::UPerspectiveMapCaptureComponent()
{
	PrimitiveRenderMode = ESceneCapturePrimitiveRenderMode::PRM_UseShowOnlyList;
}

// Called when the game starts or when spawned
void UPerspectiveMapCaptureComponent::BeginPlay()
{
	Super::BeginPlay();
	UMapActorClassifierComponent* MapActorClassifier = UPerspectiveMapFunctionLibrary::GetMapActorClassifier(this);
	if(!MapActorClassifier)
	{
		return;
	}

	MapActorClassifier->OnMapActorRegistered.AddDynamic(this, &UPerspectiveMapCaptureComponent::OnMapActorRegistered);
	MapActorClassifier->OnMapActorUnregistered.AddDynamic(this, &UPerspectiveMapCaptureComponent::OnMapActorUnregistered);

	TArray<FGameplayTag> CaptureTargetTags = CaptureTargetTagContainer.GetGameplayTagArray();
	for(FGameplayTag CategoryTag : CaptureTargetTags)
	{
		FMapActorCategory ActorCategory = MapActorClassifier->GetCategoryFromTag(CategoryTag);
		for(AActor* Actor : ActorCategory.Actors)
		{
			ShowOnlyActors.Add(Actor);
		}
	}
}

void UPerspectiveMapCaptureComponent::OnComponentDestroyed(bool bDestroyingHierarchy)
{
	Super::OnComponentDestroyed(bDestroyingHierarchy);
	
	if(!bDestroyingHierarchy)
	{
		UMapActorClassifierComponent* MapActorClassifier = UPerspectiveMapFunctionLibrary::GetMapActorClassifier(this);
		if(!MapActorClassifier)
		{
			return;
		}

		MapActorClassifier->OnMapActorRegistered.RemoveDynamic(this, &UPerspectiveMapCaptureComponent::OnMapActorRegistered);
		MapActorClassifier->OnMapActorUnregistered.RemoveDynamic(this, &UPerspectiveMapCaptureComponent::OnMapActorUnregistered);
	}
}


void UPerspectiveMapCaptureComponent::OnMapActorRegistered(FGameplayTag CategoryTag, AActor* Actor)
{
	if(!CaptureTargetTagContainer.HasTag(CategoryTag))
	{
		return;
	}

	ShowOnlyActors.Add(Actor);
}

void UPerspectiveMapCaptureComponent::OnMapActorUnregistered(FGameplayTag CategoryTag, AActor* Actor)
{
	if(!CaptureTargetTagContainer.HasTag(CategoryTag))
	{
		return;
	}

	ShowOnlyActors.Remove(Actor);
}