// Fill out your copyright notice in the Description page of Project Settings.


#include "TopDownHUD.h"
#include "DrawDebugHelpers.h"
#include "PuzzleComponent.h"

void ATopDownHUD::DrawHUD()
{
	Super::DrawHUD();
	DrawText(TEXT("Ray Hsiao 2026"), FLinearColor::Red, 0, 0, GEngine->GetSubtitleFont());
	
#if ENABLE_DRAW_DEBUG
	for (TObjectIterator<UPuzzleComponent> Itr; Itr; ++Itr)
	{
		Itr->DebugDrawOutput();
	}
#endif
}
