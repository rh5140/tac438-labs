// Ray Hsiao 2026


#include "InteractSubsystem.h"
#include "InteractComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"

void UInteractSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

void UInteractSubsystem::Deinitialize()
{
	Super::Deinitialize();
	InteractComponents.Empty();
}

void UInteractSubsystem::AddComponent(UInteractComponent* Component)
{
	InteractComponents.Add(Component);
}

void UInteractSubsystem::RemoveComponent(UInteractComponent* Component)
{
	InteractComponents.Remove(Component);
}

TStatId UInteractSubsystem::GetStatId() const
{
	RETURN_QUICK_DECLARE_CYCLE_STAT(UInteractSubsystem, STATGROUP_Tickables);
}

void UInteractSubsystem::PerformInteract()
{
	if (UInteractComponent* Component = BestCandidate.Get())
	{
		Component->NativeInteract();
	}
}

void UInteractSubsystem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	BestCandidate = nullptr;
	
	if (ACharacter* Character = UGameplayStatics::GetPlayerCharacter(this, 0))
	{
		FVector PlayerPos = Character->GetActorLocation();
		float BestDistance = TNumericLimits<float>::Max();
		
		for (const auto& WeakPtr : InteractComponents)
		{
			if (UInteractComponent* Component = WeakPtr.Get())
			{
				float Distance = FVector::Distance(PlayerPos, Component->GetOwner()->GetActorLocation());
				if (Distance < BestDistance)
				{
					BestCandidate = Component;
				}
			}
		}
	}
}

bool UInteractSubsystem::DoesSupportWorldType(const EWorldType::Type WorldType) const
{
	return WorldType == EWorldType::Game || WorldType == EWorldType::PIE;
}
