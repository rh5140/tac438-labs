// Ray Hsiao 2026

#pragma once

#include "CoreMinimal.h"
#include "ActiveGameplayEffectHandle.h"
#include "Engine/TriggerBox.h"
#include "TriggerBox_GameEffect.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class TOPDOWN_API ATriggerBox_GameEffect : public ATriggerBox
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=Abilities)
	TSubclassOf<class UGameplayEffect> GameplayEffect;
	
	UPROPERTY(Transient)
	TMap<class ATopDownCharacter*, FActiveGameplayEffectHandle> GameplayEffectHandles;
	
	UFUNCTION()
	void HandleOnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UFUNCTION()
	void HandleOnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

};
