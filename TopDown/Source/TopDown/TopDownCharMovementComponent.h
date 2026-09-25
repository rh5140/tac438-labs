// Ray Hsiao 2026

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "TopDownCharMovementComponent.generated.h"

/**
 * 
 */
UCLASS()
class TOPDOWN_API UTopDownCharMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;

	virtual float GetMaxSpeed() const override;
	
private:
	TObjectPtr<class ATopDownCharacter> TopDownChar;
};
