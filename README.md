# tac438-labs
Practicing Advanced Gameplay Programming in Unreal Engine

Summer 2026 project: work on assignments from USC's [Advanced Gameplay Programming class](https://tac438-20253.github.io/)

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
