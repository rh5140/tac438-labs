// Ray Hsiao 2026


#include "PuzzleRotate.h"
#include "Components/BillboardComponent.h"

// Sets default values
APuzzleRotate::APuzzleRotate()
{
	RootComponent = CreateDefaultSubobject<UBillboardComponent>("Root");
	PuzzleComponent = CreateDefaultSubobject<UPuzzleComponent>("Puzzle");
}

void APuzzleRotate::OnRotateTimer()
{
	if (InputActors.Num() == 0)
	{
		return;
	}
	
	PuzzleComponent->PuzzleReset();
	SetAllOutputActorsNull();
	
	UPuzzleComponent* PuzzleComp = InputActors[CurrentIndex]->FindComponentByClass<UPuzzleComponent>();
	PuzzleComp->ChangeOutputActor(this);
	
	CurrentIndex = (CurrentIndex + 1) % InputActors.Num();
}

// Called when the game starts or when spawned
void APuzzleRotate::BeginPlay()
{
	Super::BeginPlay();
	GetWorldTimerManager().SetTimer(TimerHandle, this, &APuzzleRotate::OnRotateTimer, TimerDuration, true);
	PuzzleComponent->OnReceiveInput.AddDynamic(this, &APuzzleRotate::OnReceiveInput);
	
	SetAllOutputActorsNull();
}

void APuzzleRotate::OnReceiveInput(class AActor* InputActor, bool bValue)
{	
	PuzzleComponent->SetOutputActive(bValue);
}

void APuzzleRotate::SetAllOutputActorsNull()
{
	for (const auto& WeakPtr : InputActors)
	{
		if (AActor* InputActor = WeakPtr.Get())
		{
			UPuzzleComponent* PuzzleComp = InputActor->FindComponentByClass<UPuzzleComponent>();
			PuzzleComp->ChangeOutputActor(nullptr);
		}
	}
}

