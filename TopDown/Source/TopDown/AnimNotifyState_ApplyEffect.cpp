// Ray Hsiao 2026


#include "AnimNotifyState_ApplyEffect.h"
#include "GameplayEffectTypes.h"
#include "TopDownAbilitySystemComponent.h"
#include "TopDownCharacter.h"

void UAnimNotifyState_ApplyEffect::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);
	
	if (ATopDownCharacter* Character = MeshComp->GetOwner<ATopDownCharacter>())
	{
		FGameplayEffectContextHandle ContextHandle;
		EffectHandle = Character->AbilitySystemComponent->BP_ApplyGameplayEffectToSelf(EffectToApply, 0.0f, ContextHandle);
	}
}

void UAnimNotifyState_ApplyEffect::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);
	
	if (ATopDownCharacter* Character = MeshComp->GetOwner<ATopDownCharacter>())
	{
		Character->AbilitySystemComponent->RemoveActiveGameplayEffect(EffectHandle);
		EffectHandle.Invalidate();
	}
}
