// Ray Hsiao 2026


#include "TopDownCharMovementComponent.h"
#include "TopDownAttributeSet.h"
#include "TopDownCharacter.h"

void UTopDownCharMovementComponent::BeginPlay()
{
	Super::BeginPlay();
	
	TopDownChar = GetOwner<ATopDownCharacter>();
}

float UTopDownCharMovementComponent::GetMaxSpeed() const
{
	const FGameplayTag ImmobileTag = FGameplayTag::RequestGameplayTag("Debuff.Immobile", false);
	if (TopDownChar->AbilitySystemComponent->HasMatchingGameplayTag(ImmobileTag))
		return 0.0f;
	else
		return TopDownChar->DefaultAttributeSet->GetMoveSpeed();
}

FRotator UTopDownCharMovementComponent::ComputeOrientToMovementRotation(const FRotator& CurrentRotation,
	float DeltaTime, FRotator& DeltaRotation) const
{
	const FGameplayTag ImmobileTag = FGameplayTag::RequestGameplayTag("Debuff.Immobile", false);
	if (TopDownChar->AbilitySystemComponent->HasMatchingGameplayTag(ImmobileTag))
		return CurrentRotation;
	else
		return Super::ComputeOrientToMovementRotation(CurrentRotation, DeltaTime, DeltaRotation);

}
