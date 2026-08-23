// Fill out your copyright notice in the Description page of Project Settings.


#include "TopDownHUD.h"
#include "DrawDebugHelpers.h"
#include "InteractComponent.h"
#include "PuzzleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TopDownBPLibrary.h"
#include "TopDownCharacter.h"
#include "TopDownGameMode.h"
#include "TopDownPlayerController.h"

static TAutoConsoleVariable<int32> CVarDebugPuzzles(
	TEXT("DebugPuzzles"), // Console command
	0, // Default value
	TEXT("Turns puzzle debug view on/off (off by default)"), // Help text
	ECVF_Default); // Flags

void ATopDownHUD::BeginPlay()
{
	Super::BeginPlay();
	Subsystem = GetWorld()->GetSubsystem<UInteractSubsystem>();
	PlayerController = UGameplayStatics::GetPlayerController(this, 0);
}

void ATopDownHUD::DrawHUD()
{
	Super::DrawHUD();
	DrawText(TEXT("Ray Hsiao 2026"), FLinearColor::Red, 0, 0, GEngine->GetSubtitleFont());
	
	// Display interact hint pop-up
	TWeakObjectPtr<class UInteractComponent> WeakPtr = Subsystem->GetBestCandidate();
	if (UInteractComponent* Component = WeakPtr.Get())
	{
		FVector2D CandidateScreenPos;
		UGameplayStatics::ProjectWorldToScreen(PlayerController, Component->GetOwner()->GetActorLocation(), CandidateScreenPos);
		
		FString InteractText = TEXT("[E] - Interact");
		float TextWidth, TextHeight;
		GetTextSize(InteractText, TextWidth, TextHeight, nullptr, 3.0);
		
		DrawText(InteractText, FLinearColor::Red, CandidateScreenPos.X - TextWidth/2, CandidateScreenPos.Y - TextHeight/2, nullptr, 3.0f);
	}
	
	// Test BPLibrary functions
	if (ATopDownCharacter* Char = UTopDownBPLibrary::GetTopDownCharacter(this, 0))
	{
		DrawText(Char->GetName(), FLinearColor::Green, 20, 100, nullptr, 2.0f);
	}
	if (ATopDownPlayerController* Controller = UTopDownBPLibrary::GetTopDownController(this, 0))
	{
		DrawText(Controller->GetName(), FLinearColor::Green, 20, 130, nullptr, 2.0f);
	}
	if (ATopDownGameMode* GameMode = UTopDownBPLibrary::GetTopDownGameMode(this))
	{
		DrawText(GameMode->GetName(), FLinearColor::Green, 20, 160, nullptr, 2.0f);
	}

	
#if ENABLE_DRAW_DEBUG
	if (CVarDebugPuzzles.GetValueOnGameThread() != 0)
	{
		for (TObjectIterator<UPuzzleComponent> Itr; Itr; ++Itr)
		{
			Itr->DebugDrawOutput();
		}
	}
#endif
}
