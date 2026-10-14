# tac438-labs
Following along with USC's course on [Advanced Gameplay Programming in Unreal Engine](https://tac438-20263.github.io/)

## Lab 6 - UI ([lab-6](https://github.com/rh5140/tac438-labs/tree/lab6))
- Implement C++ subclasses of User Widgets to create UI
  - Buttons ([TopDownButton.h](https://github.com/rh5140/tac438-labs/blob/lab6/TopDown/Source/TopDown/TopDownButton.h), [TopDownButton.cpp](https://github.com/rh5140/tac438-labs/blob/lab6/TopDown/Source/TopDown/TopDownButton.cpp))
  - Game over menu ([TopDownMenu.h](https://github.com/rh5140/tac438-labs/blob/lab6/TopDown/Source/TopDown/TopDownMenu.h), [TopDownMenu.cpp](https://github.com/rh5140/tac438-labs/blob/lab6/TopDown/Source/TopDown/TopDownMenu.cpp))
  - Damage numbers ([CombatTextWidget.h](https://github.com/rh5140/tac438-labs/blob/lab6/TopDown/Source/TopDown/CombatTextWidget.h), [CombatTextWidget.cpp](https://github.com/rh5140/tac438-labs/blob/lab6/TopDown/Source/TopDown/CombatTextWidget.cpp))
  - HUD with healthbar and stealth indicator ([TopDownHUD.h](https://github.com/rh5140/tac438-labs/blob/lab6/TopDown/Source/TopDown/TopDownHUD.h), [TopDownHUD.cpp](https://github.com/rh5140/tac438-labs/blob/lab6/TopDown/Source/TopDown/TopDownHUD.cpp))

<img width="2214" height="1365" alt="image" style="width:50%;height:auto" src="https://github.com/user-attachments/assets/3163e595-1157-4f50-8510-b424deced5c1" /><img width="2196" height="1362" alt="image" style="width:50%;height:auto" src="https://github.com/user-attachments/assets/402d5687-e2b0-448f-b19e-a7da35f245dc" />
 - Update Top Down Character to track threat level with asterisk (*) on HUD ([TopDownCharacter.h](https://github.com/rh5140/tac438-labs/blob/lab6/TopDown/Source/TopDown/TopDownCharacter.h), [TopDownCharacter.cpp](https://github.com/rh5140/tac438-labs/blob/lab6/TopDown/Source/TopDown/TopDownCharacter.cpp))

- [Demo video](https://youtu.be/NVTr1NMwCqM)

## Lab 5 - GAS and Animations ([lab-5](https://github.com/rh5140/tac438-labs/tree/lab5))
- Set up animations and GAS with C++ classes for Top Down Attribute Set ([TopDownAttributeSet.h](https://github.com/rh5140/tac438-labs/blob/main/TopDown/Source/TopDown/TopDownAttributeSet.h), [TopDownAttributeSet.cpp](https://github.com/rh5140/tac438-labs/blob/main/TopDown/Source/TopDown/TopDownAttributeSet.cpp)) and Top Down Ability System Component ([TopDownAbilitySystemComponent.h](https://github.com/rh5140/tac438-labs/blob/main/TopDown/Source/TopDown/TopDownAbilitySystemComponent.h), [TopDownAbilitySystemComponent.cpp](https://github.com/rh5140/tac438-labs/blob/main/TopDown/Source/TopDown/TopDownAbilitySystemComponent.cpp))
- Implement subclasses for AnimNotifyState ([AnimNotifyState_ApplyEffect.h](https://github.com/rh5140/tac438-labs/blob/main/TopDown/Source/TopDown/AnimNotifyState_ApplyEffect.h), [AnimNotifyState_ApplyEffect.cpp](https://github.com/rh5140/tac438-labs/blob/main/TopDown/Source/TopDown/AnimNotifyState_ApplyEffect.cpp)) and TriggerBox ([TriggerBox_GameEffect.h](https://github.com/rh5140/tac438-labs/blob/main/TopDown/Source/TopDown/TriggerBox_GameEffect.h), [TriggerBox_GameEffect.cpp](https://github.com/rh5140/tac438-labs/blob/main/TopDown/Source/TopDown/TriggerBox_GameEffect.cpp)) to apply Gameplay Effects
- Implement crouch/uncrouch with Gameplay Effect (cut move speed in half), Animation Montage, and Anim Notify (prevent crouch/uncrouch spam)
```cpp
void ATopDownPlayerController::OnCrouchAction(const FInputActionInstance& Instance)
{
	if (ATopDownCharacter* TopDownChar = UTopDownBPLibrary::GetTopDownCharacter(this, 0))
	{
		const FGameplayTag ImmobileTag = FGameplayTag::RequestGameplayTag("Debuff.Immobile", false);
		if (TopDownChar->AbilitySystemComponent->HasMatchingGameplayTag(ImmobileTag))
			return;
	}
	
	if (ACharacter* MyCharacter = GetCharacter())
	{
		if (MyCharacter->IsCrouched())
		{
			MyCharacter->UnCrouch();
		}
		else
		{
			MyCharacter->Crouch();
		}
	}
}
```
```cpp
void ATopDownCharacter::OnStartCrouch(float HalfHeightAdjust, float ScaledHalfHeightAdjust)
{
	Super::OnStartCrouch(HalfHeightAdjust, ScaledHalfHeightAdjust);
	
	// Apply crouching effect
	FGameplayEffectContextHandle ContextHandle;
	CrouchingEffectHandle = AbilitySystemComponent->BP_ApplyGameplayEffectToSelf(CrouchingEffect, 0.0f, ContextHandle);
}

void ATopDownCharacter::OnEndCrouch(float HalfHeightAdjust, float ScaledHalfHeightAdjust)
{
	Super::OnEndCrouch(HalfHeightAdjust, ScaledHalfHeightAdjust);
	
	// Remove crouching effect
	AbilitySystemComponent->RemoveActiveGameplayEffect(CrouchingEffectHandle);
	CrouchingEffectHandle.Invalidate();
}
```
- Implement dash ability with Gameplay Ability, Animation Montage, Anim Notifies (play sound, enable i-frames), and Gameplay Cue (i-frame)
- Implement burning Gameplay Effect applied by TriggerBox_ApplyEffect
- Implement death with Gameplay Ability, Animation Montage, and ragdolling mesh in C++
  - <img width="2278" height="1078" alt="image" src="https://github.com/user-attachments/assets/ccb7bcbb-a0b8-4508-9ad2-0bb4e71d4688" />

- [Demo video](https://youtu.be/ofE2rMG-hUM)


## Lab 4 - Physics and Sequences ([lab-4](https://github.com/rh5140/tac438-labs/tree/lab4))
- Script pressure plate and swing in Blueprints
- Create physics-based puzzles that require spreading fire to solve
- Implement Fire Component to allow objects to catch on fire with C++ ([FireComponent.h](https://github.com/rh5140/tac438-labs/blob/main/TopDown/Source/TopDown/FireComponent.h), [FireComponent.cpp](https://github.com/rh5140/tac438-labs/blob/main/TopDown/Source/TopDown/FireComponent.cpp))
- [Demo video](https://youtu.be/KJaGJk-F92Y)
```cpp
void UFireComponent::HandleOnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                          UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// If on-fire component overlaps with one that's not, spread the fire
	if (UFireComponent* FireComponent = OtherActor->FindComponentByClass<UFireComponent>())
	{
		if (bIsOnFire && !FireComponent->bIsOnFire)
		{
			FireComponent->NativeCatchFire();
		}
		else if (!bIsOnFire && FireComponent->bIsOnFire)
		{
			NativeCatchFire();
		}
	}
}

void UFireComponent::NativeCatchFire()
{
	OnCatchFire.Broadcast();
	bIsOnFire = true;
	UGameplayStatics::SpawnSoundAttached(SoundFx, this);
	UGameplayStatics::SpawnEmitterAttached(ParticleFx, this);
}
```

## Lab 3 - Interactions and More Puzzles ([lab-3](https://github.com/rh5140/tac438-labs/tree/lab3))
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

## Lab 2 - Puzzles ([lab-2](https://github.com/rh5140/tac438-labs/tree/lab2))
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

## Lab 1 - Unreal Basics ([lab-1](https://github.com/rh5140/tac438-labs/tree/lab1))
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
