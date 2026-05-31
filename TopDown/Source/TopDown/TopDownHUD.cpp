// Fill out your copyright notice in the Description page of Project Settings.


#include "TopDownHUD.h"

void ATopDownHUD::DrawHUD()
{
	Super::DrawHUD();
	DrawText(TEXT("Ray Hsiao 2026"), FLinearColor::Red, 0, 0, GEngine->GetSubtitleFont());
}
