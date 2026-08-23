// Ray Hsiao 2026


#include "InteractComponent.h"
#include "InteractSubsystem.h"

// Sets default values for this component's properties
UInteractComponent::UInteractComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UInteractComponent::BeginPlay()
{
	Super::BeginPlay();

	if (UInteractSubsystem* Subsystem = GetWorld()->GetSubsystem<UInteractSubsystem>())
	{
		Subsystem->AddComponent(this);
	}
	
	// Bind
	
}

void UInteractComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	
	if (UInteractSubsystem* Subsystem = GetWorld()->GetSubsystem<UInteractSubsystem>())
	{
		Subsystem->RemoveComponent(this);
	}
}


// Called every frame
void UInteractComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UInteractComponent::NativeInteract()
{
	if (bIsEnabled)
	{
		OnInteract.Broadcast();
	}
}

void UInteractComponent::ToggleGlow(bool IsGlowing)
{
	if (UStaticMeshComponent* Mesh = GetOwner()->FindComponentByClass<UStaticMeshComponent>())
	{
		if (IsGlowing)
		{
			Mesh->SetVectorParameterValueOnMaterials(GlowMaterialParameterName, FVector(GlowColor));
		}
		else
		{
			Mesh->SetVectorParameterValueOnMaterials(GlowMaterialParameterName, FVector(DefaultColor));	
		}
	}
}

bool UInteractComponent::GetIsEnabled()
{
	return bIsEnabled;
}

