// Ray Hsiao 2026

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TopDownButton.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTopDownButtonDelegate);

UCLASS()
class TOPDOWN_API UTopDownButton : public UUserWidget
{
	GENERATED_BODY()
	
public:
	// Called when button is selected or unselected
	virtual void NativeSetSelection(bool bIsSelected = true);
	
	// Called when button is activated
	virtual void NativeActivated();
	
	// Text on button
	UPROPERTY(EditAnywhere)
	FText ButtonText;
	
	// Triggered when button is activated
	UPROPERTY(BlueprintAssignable)
	FTopDownButtonDelegate OnActivated;
	
protected:
	// UUserWidget interface
	// Called once both in editor and in-game when about to be constructed
	virtual void NativePreConstruct() override;
	// ~ End UUserWidget interface
	
	// Color of font when not selected
	UPROPERTY(EditAnywhere)
	FLinearColor DefaultFontColor = FLinearColor::White;
	
	// Color of font when selected
	UPROPERTY(EditAnywhere)
	FLinearColor SelectedFontColor = FLinearColor::Blue;
	
private:
	// Actual text block widget
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<class UTextBlock> ButtonTextBlock;
};
