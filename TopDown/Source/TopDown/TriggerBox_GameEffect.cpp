// Ray Hsiao 2026


#include "TriggerBox_GameEffect.h"

#include "TopDownAbilitySystemComponent.h"
#include "TopDownCharacter.h"
#include "Components/ShapeComponent.h"

void ATriggerBox_GameEffect::BeginPlay()
{
	Super::BeginPlay();
	GetCollisionComponent()->OnComponentBeginOverlap.AddDynamic(this, &ATriggerBox_GameEffect::HandleOnBeginOverlap);
	GetCollisionComponent()->OnComponentEndOverlap.AddDynamic(this, &ATriggerBox_GameEffect::HandleOnEndOverlap);
}

void ATriggerBox_GameEffect::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	GetCollisionComponent()->OnComponentBeginOverlap.RemoveAll(this);
	GetCollisionComponent()->OnComponentEndOverlap.RemoveAll(this);

}

void ATriggerBox_GameEffect::HandleOnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Apply gameplay effect to TopDownChar on overlap
	if (ATopDownCharacter* TopDownChar = Cast<ATopDownCharacter>(OtherActor))
	{
		FGameplayEffectContextHandle ContextHandle;
		FActiveGameplayEffectHandle EffectHandle = TopDownChar->AbilitySystemComponent->BP_ApplyGameplayEffectToSelf(GameplayEffect, 0.0f, ContextHandle);
		GameplayEffectHandles.Emplace(TopDownChar, EffectHandle);
	}
}

void ATriggerBox_GameEffect::HandleOnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (ATopDownCharacter* TopDownChar = Cast<ATopDownCharacter>(OtherActor))
	{
		if (GameplayEffectHandles.Contains(TopDownChar))
		{
			FActiveGameplayEffectHandle EffectHandle = GameplayEffectHandles[TopDownChar];
			TopDownChar->AbilitySystemComponent->RemoveActiveGameplayEffect(EffectHandle);
			EffectHandle.Invalidate();
			GameplayEffectHandles.Remove(TopDownChar);
		}
	}
}
