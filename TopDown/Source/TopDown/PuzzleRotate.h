// Ray Hsiao 2026

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PuzzleComponent.h"
#include "PuzzleRotate.generated.h"

UCLASS(Abstract)
class TOPDOWN_API APuzzleRotate : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APuzzleRotate();
	
	// List of input actors to rotate between
	UPROPERTY(EditInstanceOnly)
	TArray<TSoftObjectPtr<class AActor>> InputActors;
	
	// Repeating timer
	void OnRotateTimer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Puzzle Component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<class UPuzzleComponent> PuzzleComponent;
	
	UFUNCTION()
	void OnReceiveInput(class AActor* InputActor, bool bValue);
	
	// Timer duration
	UPROPERTY(EditAnywhere)
	float TimerDuration = 1.0f;
	
	// Timer handle
	FTimerHandle TimerHandle;

private:
	// Sets OutputActor of all InputActorsNull
	void SetAllOutputActorsNull();
	
	int CurrentIndex = 0;
};
