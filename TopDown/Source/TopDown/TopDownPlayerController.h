// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
//#include "Templates/SubclassOf.h"
#include "GameFramework/PlayerController.h"
#include "InputAction.h"
#include "TopDownPlayerController.generated.h"

class UNiagaraSystem;
class UInputMappingContext;
class UInputAction;
class UPathFollowingComponent;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

/**
 *  Player controller for a top-down perspective game.
 *  Implements point and click based controls
 */
UCLASS(abstract)
class ATopDownPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	/** MappingContext */
	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputMappingContext> DefaultMappingContext;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input)
	TObjectPtr<class UInputAction> JumpAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input)
	TObjectPtr<class UInputAction> MoveForwardAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input)
	TObjectPtr<class UInputAction> MoveRightAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input)
	TObjectPtr<class UInputAction> InteractAction;

public:

	/** Constructor */
	ATopDownPlayerController();

protected:

	/** Initialize input bindings */
	virtual void SetupInputComponent() override;
	
	void OnJumpAction();
	void OnMoveForward(const FInputActionInstance& Instance);
	void OnMoveRight(const FInputActionInstance& Instance);
	void OnInteractAction(const FInputActionInstance& Instance);
	
};


