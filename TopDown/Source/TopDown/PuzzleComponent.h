// Ray Hsiao 2026

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PuzzleComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FPuzzleComponentOnReceiveInput, class AActor*, InputActor,  bool, bValue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPuzzleComponentOnPuzzleReset);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOPDOWN_API UPuzzleComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPuzzleComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
	UPROPERTY(Transient, BlueprintReadOnly)
	bool bIsOutputActive;
	
	UPROPERTY(EditInstanceOnly)
	TSoftObjectPtr<AActor> OutputActor;
	
	/** Sets whether output is active */
	UFUNCTION(BlueprintCallable)
	virtual void SetOutputActive(bool bNewOutputActive);

	virtual void NativeReceiveInput(TObjectPtr<AActor> Sender, bool bNewIncomingValue);
	
	/** Resets puzzle */
	UFUNCTION(BlueprintCallable)
	virtual void PuzzleReset();
	
	UPROPERTY(BlueprintAssignable)
	FPuzzleComponentOnReceiveInput OnReceiveInput;
	
	UPROPERTY(BlueprintAssignable)
	FPuzzleComponentOnPuzzleReset OnPuzzleReset;
	
public:	
		
};
