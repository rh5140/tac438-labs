# tac438-labs
Following along with USC's course on [Advanced Gameplay Programming in Unreal Engine](https://tac438-20253.github.io/)

## Lab 2 - Puzzles
- Implemented extensible Puzzle Actor in C++ using delegates ([PuzzleComponent.h](https://github.com/rh5140/tac438-labs/blob/main/TopDown/Source/TopDown/PuzzleComponent.h), [PuzzleComponent.cpp](https://github.com/rh5140/tac438-labs/blob/main/TopDown/Source/TopDown/PuzzleComponent.cpp))
- Scripted Blueprint Puzzle extensions (AND, OR, Sequence, Frequency)
- [Demo video](https://youtu.be/4yjlN7vv5L0)
```cpp
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
```

## Lab 1 - Unreal Basics
- Created HUD with watermark ([TopDown.h](https://github.com/rh5140/tac438-labs/blob/main/TopDown/Source/TopDown/TopDown.h), [TopDown.cpp](https://github.com/rh5140/tac438-labs/blob/main/TopDown/Source/TopDown/TopDown.cpp))
- Modified top-down controller to use WASD controls with Enhanced Input Plugin ([TopDownPlayerController.h](https://github.com/rh5140/tac438-labs/blob/main/TopDown/Source/TopDown/TopDownPlayerController.h), [TopDownPlayerController.cpp](https://github.com/rh5140/tac438-labs/blob/main/TopDown/Source/TopDown/TopDown.cpp))
- Implemented box trigger that changes the character's color ([TopDownCharacter.cpp](https://github.com/rh5140/tac438-labs/blob/main/TopDown/Source/TopDown/TopDownCharacter.cpp))
- [Demo video](https://youtu.be/lmENJEfiMaA)
```cpp
void ATopDownCharacter::OnBlueTriggerEnter()
{
	NumBlueTriggers++;
	if (NumBlueTriggers == 1)
	{
		FVector NewColor(BlueTriggerColor.R, BlueTriggerColor.G, BlueTriggerColor.B);
		GetMesh()->SetVectorParameterValueOnMaterials(BodyColorParameter, NewColor);
	}
}

void ATopDownCharacter::OnBlueTriggerExit()
{
	NumBlueTriggers--;
	if (NumBlueTriggers == 0)
	{
		FVector NewColor(DefaultColor.R, DefaultColor.G, DefaultColor.B);
		GetMesh()->SetVectorParameterValueOnMaterials(BodyColorParameter, NewColor);
	}
}
```
