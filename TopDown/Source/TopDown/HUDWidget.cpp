// Ray Hsiao 2026


#include "HUDWidget.h"

#include "TopDownBPLibrary.h"
#include "TopDownCharacter.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"

void UHUDWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	
	if (ATopDownCharacter* TopDownChar = UTopDownBPLibrary::GetTopDownCharacter(this, 0))
	{
		FString HealthStr = FString::FromInt(TopDownChar->GetCurrentHealth());
		HealthAmount->SetText(FText::FromString(HealthStr));
		
		float HealthPct = TopDownChar->GetHealthPct();
		HealthBar->SetPercent(HealthPct);
		
		if (HealthPct > 0.7f)
		{
			HealthBar->SetFillColorAndOpacity(DefaultHealthColor);
		}
		else if (HealthPct > 0.3f)
		{
			HealthBar->SetFillColorAndOpacity(DangerHealthColor);
		}
		else
		{
			HealthBar->SetFillColorAndOpacity(CriticalHealthColor);
		}
	}
}
