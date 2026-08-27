// Ray Hsiao 2026


#include "FireComponent.h"

UFireComponent::UFireComponent()
{
}

void UFireComponent::BeginPlay()
{
	Super::BeginPlay();
	PrimaryComponentTick.bCanEverTick = false;
	
	OnComponentBeginOverlap.AddDynamic(this, &UFireComponent::HandleOnBeginOverlap);
	
	if (bIsOnFire)
	{
		NativeCatchFire();
	}
}

void UFireComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	OnComponentBeginOverlap.RemoveAll(this);
}

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
}
