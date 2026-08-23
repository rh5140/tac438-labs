// Ray Hsiao 2026


#include "TopDownBPLibrary.h"
#include "Kismet/GameplayStatics.h"

class ATopDownCharacter* UTopDownBPLibrary::GetTopDownCharacter(const UObject* WorldContextObject, int32 PlayerIndex)
{
	return Cast<ATopDownCharacter>(UGameplayStatics::GetPlayerCharacter(WorldContextObject, PlayerIndex));
}

class ATopDownPlayerController* UTopDownBPLibrary::GetTopDownController(const UObject* WorldContextObject,
	int32 PlayerIndex)
{
	return Cast<ATopDownPlayerController>(UGameplayStatics::GetPlayerController(WorldContextObject, PlayerIndex));
}

class ATopDownGameMode* UTopDownBPLibrary::GetTopDownGameMode(const UObject* WorldContextObject)
{
	return Cast<ATopDownGameMode>(UGameplayStatics::GetGameMode(WorldContextObject));
}
