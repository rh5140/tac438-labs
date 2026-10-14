// Ray Hsiao 2026


#include "CombatTextWidget.h"

#include "Components/TextBlock.h"

void UCombatTextWidget::ShowDamage(int DamageAmount)
{
	PlayAnimation(TextFly);
	
	if (DamageAmount < 0)
	{
		CombatTextBlock->SetColorAndOpacity(PositiveColor);
	}
	if (DamageAmount > 0)
	{
		CombatTextBlock->SetColorAndOpacity(NegativeColor);
	}
	
	FString FormattedNumber = FString::Printf(TEXT("%d"),FMath::Abs(DamageAmount));
	CombatTextBlock->SetText(FText::FromString(FormattedNumber));
}
