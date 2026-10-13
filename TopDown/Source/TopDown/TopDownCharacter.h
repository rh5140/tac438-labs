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
	
	// Crouch overrides
	virtual void OnStartCrouch(float HalfHeightAdjust, float ScaledHalfHeightAdjust) override;
	virtual void OnEndCrouch(float HalfHeightAdjust, float ScaledHalfHeightAdjust) override;

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
	
	// Gameplay abilities that should be given on begin play
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Abilities)
	TMap<FName, TSubclassOf<class UGameplayAbility>> InitialGameplayAbilities;
	
	/**
	 *  Give character a gameplay ability and track w/ specific name
	 *  @param AbilityName
	 *  @param AbilityClass
	 */
	UFUNCTION(BlueprintCallable, Category = Abilities)
	void GiveAbility(const FName& AbilityName, TSubclassOf<class UGameplayAbility> AbilityClass);
	
	/**
	 * Try to activate ability by given name
	 * 
	 * @param AbilityName
	 * @return true if ability activation worked
	 */
	UFUNCTION(BlueprintCallable, Category = Abilities)
	bool TryActivateAbility(const FName& AbilityName);
	
	// Called from AttributeSet when damage is taken
	void HandleDamage(float Amount, float NewHealth);
	
	// Called to enable ragdoll on character
	UFUNCTION(BlueprintCallable, Category=Abilities)
	void EnableRagdoll();
	
	float GetCurrentHealth();
	float GetHealthPct();
	
protected:
	/** Number of blue triggers player is overlapping */
	UPROPERTY(BlueprintReadOnly)
	int NumBlueTriggers = 0;
	
	// The actual crouching effect
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Abilities")
	TSubclassOf<class UGameplayEffect> CrouchingEffect;
	
	// The handle to track when crouching effect is active
	FActiveGameplayEffectHandle CrouchingEffectHandle;
	
	// Current Gameplay Abilities (do not directly modify)
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Abilities)
	TMap<FName, TSubclassOf<class UGameplayAbility>> GameplayAbilities;

private:
	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> TopDownCameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USpringArmComponent> CameraBoom;
	
};

