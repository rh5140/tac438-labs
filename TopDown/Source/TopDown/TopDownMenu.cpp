// Ray Hsiao 2026


#include "TopDownMenu.h"

#include "TopDownButton.h"
#include "Blueprint/WidgetTree.h"

UTopDownMenu::UTopDownMenu(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	
	SetIsFocusable(true);
}

void UTopDownMenu::NativeConstruct()
{
	Super::NativeConstruct();
	
	// Clear buttons
	Buttons.Empty();
	
	// Iterate all children in widget tree to find buttons
	WidgetTree->ForEachWidget([this](UWidget* Widget)
	{
		if (auto Button = Cast<UTopDownButton>(Widget))
		{
			Buttons.Add(Button);
		}
	});
	
	SetSelectedIndex(0);
}

FReply UTopDownMenu::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
	FKey Key = InKeyEvent.GetKey();
	if (Key == EKeys::Up || Key == EKeys::W)
	{
		SetSelectedIndex(SelectedIndex - 1);
	}
	else if (Key == EKeys::Down || Key == EKeys::S)
	{
		SetSelectedIndex(SelectedIndex + 1);
	}
	else if (Key == EKeys::Enter && Buttons.IsValidIndex(SelectedIndex))
	{
		Buttons[SelectedIndex].Get()->NativeActivated();
	}
	
	return FReply::Handled();
}

void UTopDownMenu::SetSelectedIndex(int InSelectedIndex)
{
	// Deselect old button
	if (Buttons.IsValidIndex(SelectedIndex))
	{
		Buttons[SelectedIndex].Get()->NativeSetSelection(false);
	}
	
	// Wrap around selected index
	SelectedIndex = FMath::WrapExclusive(InSelectedIndex, 0, Buttons.Num());
	
	// Select new button
	if (Buttons.IsValidIndex(SelectedIndex))
	{
		Buttons[SelectedIndex].Get()->NativeSetSelection(true);
	}
}
