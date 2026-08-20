// Fill out your copyright notice in the Description page of Project Settings.


#include "TopDownHUD.h"
#include "DrawDebugHelpers.h"
#include "InteractComponent.h"
#include "PuzzleComponent.h"
#include "Kismet/GameplayStatics.h"

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
		float TextWidth;
		float TextHeight;
		GetTextSize(InteractText, TextWidth, TextHeight, nullptr, 3.0);
		
		DrawText(InteractText, FLinearColor::Red, CandidateScreenPos.X - TextWidth/2, CandidateScreenPos.Y - TextHeight/2, nullptr, 3.0f);
	}
	
	
#if ENABLE_DRAW_DEBUG
	for (TObjectIterator<UPuzzleComponent> Itr; Itr; ++Itr)
	{
		Itr->DebugDrawOutput();
	}
#endif
}
