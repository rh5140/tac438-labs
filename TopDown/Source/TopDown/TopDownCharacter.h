// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TopDownCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;

/**
 *  A controllable top-down perspective character
 */
UCLASS(abstract)
class ATopDownCharacter : public ACharacter
{
	GENERATED_BODY()

private:

	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> TopDownCameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USpringArmComponent> CameraBoom;
	
protected:
	
	/** Number of blue triggers player is overlapping */
	UPROPERTY(BlueprintReadOnly)
	int NumBlueTriggers = 0;

public:

	/** Constructor */
	ATopDownCharacter();

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
};

