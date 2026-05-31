// Copyright Epic Games, Inc. All Rights Reserved.

#include "TopDownPlayerController.h"
#include "GameFramework/Pawn.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "TopDownCharacter.h"
#include "Engine/World.h"
#include "EnhancedInputComponent.h"
#include "Navigation/PathFollowingComponent.h"
#include "InputActionValue.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"
#include "TopDown.h"

ATopDownPlayerController::ATopDownPlayerController()
{
	bShowMouseCursor = false;
}

void ATopDownPlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	// Only set up input on local player controllers
	if (IsLocalPlayerController())
	{
		// Add Input Mapping Context
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}

		// Set up action bindings
		if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
		{
			EnhancedInputComponent->BindAction(MoveForwardAction, ETriggerEvent::Triggered, this, &ATopDownPlayerController::OnMoveForward);
			EnhancedInputComponent->BindAction(MoveRightAction, ETriggerEvent::Triggered, this, &ATopDownPlayerController::OnMoveRight);
			EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ATopDownPlayerController::OnJumpAction);
		}
		else
		{
			UE_LOG(LogTopDown, Error, TEXT("'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
		}
	}
}

void ATopDownPlayerController::OnJumpAction()
{
	if (ACharacter* MyCharacter = GetCharacter())
	{
		MyCharacter->Jump();
	}
}

void ATopDownPlayerController::OnMoveForward(const FInputActionInstance& Instance)
{
	if (APawn* MyPawn = GetPawn())
	{
		float AxisValue = Instance.GetValue().Get<float>();
		MyPawn->AddMovementInput(FVector::ForwardVector, AxisValue);
	}
}

void ATopDownPlayerController::OnMoveRight(const FInputActionInstance& Instance)
{
	if (APawn* MyPawn = GetPawn())
	{
		float AxisValue = Instance.GetValue().Get<float>();
		MyPawn->AddMovementInput(FVector::RightVector, AxisValue);
	}
}
