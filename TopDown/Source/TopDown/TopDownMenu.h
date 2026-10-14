// Ray Hsiao 2026

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TopDownMenu.generated.h"

/**
 * 
 */
UCLASS()
class TOPDOWN_API UTopDownMenu : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UTopDownMenu(const FObjectInitializer& ObjectInitializer);
	
protected:
	// UUserInterface
	// Called when widget is created in game (can happen multiple times)
	virtual void NativeConstruct() override;
	// Called when key is pressed
	virtual FReply NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;
	// ~ End UUserWidget interface
	
	// Called when changing selection index
	void SetSelectedIndex(int InSelectedIndex);
	
	virtual FReply NativeOnMouseMove(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	
private:
	int SelectedIndex = 0;
	TArray<TWeakObjectPtr<class UTopDownButton>> Buttons;
};
