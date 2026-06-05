// Ray Hsiao 2026


#include "PuzzleComponent.h"

// Sets default values for this component's properties
UPuzzleComponent::UPuzzleComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UPuzzleComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UPuzzleComponent::SetOutputActive(bool bNewOutputActive)
{
	if (bNewOutputActive == bIsOutputActive)
		return;
	
	bIsOutputActive = bNewOutputActive;
	
	if (AActor* OutActor = OutputActor.Get())
	{
		UPuzzleComponent* PuzzleComp = OutActor->FindComponentByClass<UPuzzleComponent>();
		PuzzleComp->NativeReceiveInput(GetOwner(), bNewOutputActive);
	}
}

void UPuzzleComponent::NativeReceiveInput(TObjectPtr<AActor> Sender, bool bNewIncomingValue)
{
	OnReceiveInput.Broadcast(Sender, bNewIncomingValue);
}

void UPuzzleComponent::PuzzleReset()
{
	SetOutputActive(false);
	OnPuzzleReset.Broadcast();
}


