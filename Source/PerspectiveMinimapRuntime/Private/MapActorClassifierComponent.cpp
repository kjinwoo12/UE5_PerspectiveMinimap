// Fill out your copyright notice in the Description page of Project Settings.


#include "MapActorClassifierComponent.h"

// Sets default values for this component's properties
UMapActorClassifierComponent::UMapActorClassifierComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

void UMapActorClassifierComponent::RegisterActor(FGameplayTag CategoryTag, AActor* Actor)
{
	FMapActorCategory* Category = ActorCategories.Find(CategoryTag);
	if(!Category)
	{
		FMapActorCategory NewCategory = FMapActorCategory();
		NewCategory.Actors.Add(Actor);
		ActorCategories.Add(CategoryTag, NewCategory);
	}
	else
	{
		Category->Actors.Add(Actor);
	}

	OnMapActorRegistered.Broadcast(CategoryTag, Actor);
}

void UMapActorClassifierComponent::UnregisterActor(FGameplayTag CategoryTag, AActor* Actor)
{
	FMapActorCategory* Category = ActorCategories.Find(CategoryTag);
	if(Category)
	{
		Category->Actors.Remove(Actor);
	}
	OnMapActorUnregistered.Broadcast(CategoryTag, Actor);
}


FMapActorCategory UMapActorClassifierComponent::GetCategoryFromTag(FGameplayTag CategoryTag) const
{
	const FMapActorCategory* FoundCategory = ActorCategories.Find(CategoryTag);
	if(FoundCategory)
	{
		return *FoundCategory;
	}
	else
	{
		// Return a default constructed FMapActorCategory if the tag is not found
		return FMapActorCategory();
	}
}