// Ray Hsiao 2026

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "FireComponent.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FFireComponentOnCatchFire);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class TOPDOWN_API UFireComponent : public USphereComponent
{
	GENERATED_BODY()
	
public:
	// Constructor
	UFireComponent();
	
	virtual void BeginPlay() override;
	
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	
protected:
	
	UFUNCTION()
	void HandleOnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsOnFire = false;
	
	UPROPERTY(EditAnywhere)
	TObjectPtr<USoundBase> SoundFx;
	
	UPROPERTY(EditAnywhere)
	TObjectPtr<UParticleSystem> ParticleFx;
	
	UPROPERTY(BlueprintAssignable)
	FFireComponentOnCatchFire OnCatchFire;
	
	virtual void NativeCatchFire();
};


