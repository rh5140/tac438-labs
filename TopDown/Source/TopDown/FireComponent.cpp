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
}

void UFireComponent::NativeCatchFire()
{
	OnCatchFire.Broadcast();
}
