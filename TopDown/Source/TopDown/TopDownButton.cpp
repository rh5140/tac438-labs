// Ray Hsiao 2026


#include "TopDownButton.h"

#include "Components/TextBlock.h"

void UTopDownButton::NativeSetSelection(bool bIsSelected)
{
	ButtonTextBlock->SetColorAndOpacity(bIsSelected ? SelectedFontColor : DefaultFontColor);
}

void UTopDownButton::NativeActivated()
{
	OnActivated.Broadcast();
}

void UTopDownButton::NativePreConstruct()
{
	Super::NativePreConstruct();
	
	ButtonTextBlock->SetText(ButtonText);
	ButtonTextBlock->SetColorAndOpacity(DefaultFontColor);
}
