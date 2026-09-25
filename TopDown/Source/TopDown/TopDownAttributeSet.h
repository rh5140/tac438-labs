// Ray Hsiao 2026

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "TopDownAbilitySystemComponent.h"
#include "TopDownAttributeSet.generated.h"

/**
 * 
 */
UCLASS()
class TOPDOWN_API UTopDownAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
	
public:
	UTopDownAttributeSet();
	
	// Current health
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FGameplayAttributeData Health;

	// Maximum health
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FGameplayAttributeData MaxHealth;
	
	// Movement speed
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FGameplayAttributeData MoveSpeed;
	
	// Define getters/setters
	ATTRIBUTE_ACCESSORS_BASIC(UTopDownAttributeSet, Health);
	ATTRIBUTE_ACCESSORS_BASIC(UTopDownAttributeSet, MaxHealth);
	ATTRIBUTE_ACCESSORS_BASIC(UTopDownAttributeSet, MoveSpeed);
};
