// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "ActiveGameplayEffectHandle.h"
#include "GameFramework/Character.h"
#include "TopDownCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class UTopDownAbilitySystemComponent;

/**
 *  A controllable top-down perspective character
 */
UCLASS()
class ATopDownCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	/** Constructor */
	ATopDownCharacter(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	/** Initialization */
	virtual void BeginPlay() override;

	/** Update */
	virtual void Tick(float DeltaSeconds) override;

	/** Returns the camera component **/
	UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent.Get(); }

	/** Returns the Camera Boom component **/
	USpringArmComponent* GetCameraBoom() const { return CameraBoom.Get(); }

	/** Increments number of overlapping blue triggers **/
	UFUNCTION(BlueprintCallable)
	void OnBlueTriggerEnter();
	
	/** Decrements number of overlapping blue triggers **/
	UFUNCTION(BlueprintCallable)
	void OnBlueTriggerExit();
	
	UPROPERTY(EditDefaultsOnly)
	FLinearColor DefaultColor = FLinearColor::White;
	
	UPROPERTY(EditDefaultsOnly)
	FLinearColor BlueTriggerColor = FLinearColor::Blue;
	
	UPROPERTY(EditDefaultsOnly)
	FName BodyColorParameter = FName(TEXT("Paint Tint"));
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Abilities")
	TObjectPtr<class UTopDownAbilitySystemComponent> AbilitySystemComponent;
	
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	UPROPERTY()
	TObjectPtr<class UTopDownAttributeSet> DefaultAttributeSet;

protected:
	/** Number of blue triggers player is overlapping */
	UPROPERTY(BlueprintReadOnly)
	int NumBlueTriggers = 0;
	
	// The actual crouching effect
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Abilities")
	TSubclassOf<class UGameplayEffect> CrouchingEffect;
	
	// The handle to track when crouching effect is active
	FActiveGameplayEffectHandle CrouchingEffectHandle;

private:
	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> TopDownCameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USpringArmComponent> CameraBoom;
	
	virtual void OnStartCrouch(float HalfHeightAdjust, float ScaledHalfHeightAdjust) override;
	
	virtual void OnEndCrouch(float HalfHeightAdjust, float ScaledHalfHeightAdjust) override;
	
};

