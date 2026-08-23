// Ray Hsiao 2026

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "TopDownCharacter.h"
#include "TopDownPlayerController.h"
#include "TopDownGameMode.h"
#include "TopDownBPLibrary.generated.h"

/**
 * 
 */
UCLASS()
class TOPDOWN_API UTopDownBPLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	/**
	 * Returns the player character cast to a TopDownCharacter
	 *
	 * @param PlayerIndex	Index in the player controller list, starting first with local players and then available remote ones
	 */
	UFUNCTION(BlueprintPure, Category="Game", meta=(WorldContext="WorldContextObject", UnsafeDuringActorConstruction="true"))
	static class ATopDownCharacter* GetTopDownCharacter(const UObject* WorldContextObject, int32 PlayerIndex);
	
	/** 
	 * Returns the player controller cast to a TopDownPlayerController
	 *
	 * @param PlayerIndex	Index in the player controller list, starting first with local players and then available remote ones
	 */
	UFUNCTION(BlueprintPure, Category="Game", meta=(WorldContext="WorldContextObject", UnsafeDuringActorConstruction="true"))
	static class ATopDownPlayerController* GetTopDownController(const UObject* WorldContextObject, int32 PlayerIndex);
	
	/** Returns the current game mode cast to a TopDownGameMMode */
	UFUNCTION(BlueprintPure, Category="Game", meta=(WorldContext="WorldContextObject"))
	static class ATopDownGameMode* GetTopDownGameMode(const UObject* WorldContextObject);
};
