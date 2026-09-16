# tac438-labs
Following along with USC's course on [Advanced Gameplay Programming in Unreal Engine](https://tac438-20263.github.io/)

## Lab 4 - Physics and Sequences
- Script pressure plate and swing in Blueprints
- Implement Fire Component to allow objects to catch on fire with C++ ([FireComponent.h](https://github.com/rh5140/tac438-labs/blob/main/TopDown/Source/TopDown/FireComponent.h), [FireComponent.cpp](https://github.com/rh5140/tac438-labs/blob/main/TopDown/Source/TopDown/FireComponent.cpp))
- Create physics-based puzzles that require spreading fire to solve
- [Demo video](https://youtu.be/KJaGJk-F92Y)

## Lab 3 - Interactions and More Puzzles
- Implement Interact Subsystem ([InteractSubsystem.h](https://github.com/rh5140/tac438-labs/blob/main/TopDown/Source/TopDown/InteractSubsystem.h), [InteractSubsystem.cpp](https://github.com/rh5140/tac438-labs/blob/main/TopDown/Source/TopDown/InteractSubsystem.cpp)) and Interact Component ([InteractComponent.h](https://github.com/rh5140/tac438-labs/blob/main/TopDown/Source/TopDown/InteractComponent.h), [InteractComponent.cpp](https://github.com/rh5140/tac438-labs/blob/main/TopDown/Source/TopDown/InteractComponent.cpp)) in C++
- Set up Blueprint function library ([TopDownBPLibrary.h](https://github.com/rh5140/tac438-labs/blob/main/TopDown/Source/TopDown/TopDownBPLibrary.h), [TopDownBPLibrary.cpp](https://github.com/rh5140/tac438-labs/blob/main/TopDown/Source/TopDown/TopDownBPLibrary.cpp))
- Implement togglable puzzle debug visualization
- Highlight interactable component most directly in front of player within 200 units ([InteractSubsystem.cpp](https://github.com/rh5140/tac438-labs/blob/main/TopDown/Source/TopDown/InteractSubsystem.cpp))
- [Demo video](https://youtu.be/smzNsGR_UqQ)
```cpp
void UInteractSubsystem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	// Highlights interact component most directly in front of player within 200 units
	if (ACharacter* Character = UGameplayStatics::GetPlayerCharacter(this, 0))
	{
		FVector PlayerPos = Character->GetActorLocation();
		float MaxDistance = 200;
		
		float LargestDotProduct = 0;
		BestCandidate = nullptr;
		
		for (const auto& WeakPtr : InteractComponents)
		{
			if (UInteractComponent* Component = WeakPtr.Get())
			{
				FVector ComponentPos = Component->GetOwner()->GetActorLocation();
				float Distance = FVector::Distance(PlayerPos, ComponentPos);
				FVector PlayerToComponent = ComponentPos - PlayerPos;
				float DotProduct = FVector::DotProduct(Character->GetActorForwardVector(), PlayerToComponent);
					
				if (DotProduct > LargestDotProduct && Distance < MaxDistance)
				{
					if (BestCandidate != nullptr)
					{
						BestCandidate->ToggleGlow(false);
					}
					Component->ToggleGlow(true);
					BestCandidate = Component;
					LargestDotProduct = DotProduct;
				}
				else
				{
					Component->ToggleGlow(false);
				}
			}
		}
	}
}
```

## Lab 2 - Puzzles
- Implemented extensible Puzzle Component in C++ using delegates ([PuzzleComponent.h](https://github.com/rh5140/tac438-labs/blob/main/TopDown/Source/TopDown/PuzzleComponent.h), [PuzzleComponent.cpp](https://github.com/rh5140/tac438-labs/blob/main/TopDown/Source/TopDown/PuzzleComponent.cpp))
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
