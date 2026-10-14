// Ray Hsiao 2026

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CombatTextWidget.generated.h"

/**
 * 
 */
UCLASS()
class TOPDOWN_API UCombatTextWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void ShowDamage(int DamageAmount);
	
private:
	// Actual text block widget
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<class UTextBlock> CombatTextBlock;
	
	// Text block animation
	UPROPERTY(Transient, meta=(BindWidgetAnim))
	TObjectPtr<class UWidgetAnimation> TextFly;
	
	// Text colors
	FLinearColor PositiveColor = FLinearColor::Green;
	FLinearColor NegativeColor = FLinearColor::Red;
	
};
