// Ray Hsiao 2026

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "InteractSubsystem.generated.h"

UCLASS()
class TOPDOWN_API UInteractSubsystem : public UTickableWorldSubsystem
{
	GENERATED_BODY()
	
public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	
	void AddComponent(class UInteractComponent* Component);
	void RemoveComponent(class UInteractComponent* Component);
	
	virtual TStatId GetStatId() const override;
	
	void PerformInteract();
	
	// Getter
	TWeakObjectPtr<class UInteractComponent> GetBestCandidate();
	
protected:
	virtual void Tick(float DeltaTime) override;
	virtual bool DoesSupportWorldType(const EWorldType::Type WorldType) const override;
	
	TArray<TWeakObjectPtr<class UInteractComponent>> InteractComponents;
	TWeakObjectPtr<class UInteractComponent> BestCandidate;
};
