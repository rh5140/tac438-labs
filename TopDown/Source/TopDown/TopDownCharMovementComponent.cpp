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
	return TopDownChar->DefaultAttributeSet->GetMoveSpeed();
}
