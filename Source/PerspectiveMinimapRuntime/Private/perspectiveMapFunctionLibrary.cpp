// Fill out your copyright notice in the Description page of Project Settings.


#include "PerspectiveMapFunctionLibrary.h"
#include "MapActorClassifierComponent.h"

#include "GameFramework/GameState.h"


UMapActorClassifierComponent* UPerspectiveMapFunctionLibrary::GetMapActorClassifier(const UObject* WorldContextObject)
{
	// Retrieve the world from the context object
#if ENGINE_MAJOR_VERSION == 4 && ENGINE_MINOR_VERSION <= 16
	UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject);
#else
	UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::ReturnNull);
#endif
	if(!World)
		return nullptr;

	// Minimap is pointless on dedicated server, so don't do any classifying
	if(World->GetNetMode() == ENetMode::NM_DedicatedServer)
		return nullptr;

	// Retrieve the game state actor
#if ENGINE_MAJOR_VERSION == 4 && ENGINE_MINOR_VERSION <= 13
	AGameState* GS = World->GetGameState();
#else
	AGameStateBase* GS = World->GetGameState();
#endif

	// Game state not found, assuming gameplay is not in progress
	if(!GS)
		return nullptr;

	// Attempt to find a SceneCaptureClassifierComponent as component of the GameState actor
	UMapActorClassifierComponent* SceneCaptureClassifier = Cast<UMapActorClassifierComponent>(GS->GetComponentByClass(UMapActorClassifierComponent::StaticClass()));
	if(SceneCaptureClassifier)
	{
		// Found it, so return it
		return SceneCaptureClassifier;
	}
	else
	{
		// Wasn't found, so create it once. Subsequent calls will find this one.
		SceneCaptureClassifier = NewObject<UMapActorClassifierComponent>(GS, TEXT("SceneCaptureClassifierComponent"));
		return SceneCaptureClassifier;
	}
}