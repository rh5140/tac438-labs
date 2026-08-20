// Ray Hsiao 2026

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InteractComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FInteractDelegate);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOPDOWN_API UInteractComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInteractComponent();
	
	// Called when the game starts
	virtual void BeginPlay() override;
	
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void NativeInteract();
	
	// Called on interaction by InteractSubsystem
	virtual void ToggleGlow(bool IsGlowing);

protected:
	UPROPERTY(BlueprintAssignable)
	FInteractDelegate OnInteract;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Glow)
	FName GlowMaterialParameterName = "InteractGlow";
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Glow)
	FColor GlowColor = FColor::White;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Glow)
	FColor DefaultColor = FColor::Black;

};
