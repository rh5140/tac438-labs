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

TWeakObjectPtr<class UInteractComponent> UInteractSubsystem::GetBestCandidate()
{
	return BestCandidate;
}

void UInteractSubsystem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (ACharacter* Character = UGameplayStatics::GetPlayerCharacter(this, 0))
	{
		FVector PlayerPos = Character->GetActorLocation();
		float BestDistance = -1;
		
		for (const auto& WeakPtr : InteractComponents)
		{
			if (UInteractComponent* Component = WeakPtr.Get())
			{
				float Distance = FVector::Distance(PlayerPos, Component->GetOwner()->GetActorLocation());
				if (BestDistance < 0 || Distance < BestDistance)
				{
					if (BestCandidate != nullptr) BestCandidate->ToggleGlow(false);
					Component->ToggleGlow(true);
					BestCandidate = Component;
					BestDistance = Distance;
				}
			}
		}
	}
}

bool UInteractSubsystem::DoesSupportWorldType(const EWorldType::Type WorldType) const
{
	return WorldType == EWorldType::Game || WorldType == EWorldType::PIE;
}
