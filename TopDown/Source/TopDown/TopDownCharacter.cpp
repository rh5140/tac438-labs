// Copyright Epic Games, Inc. All Rights Reserved.

#include "TopDownCharacter.h"

#include "CombatTextWidget.h"
#include "TopDownAbilitySystemComponent.h"
#include "TopDownAttributeSet.h"
#include "TopDownCharMovementComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "Materials/Material.h"
#include "Engine/World.h"

ATopDownCharacter::ATopDownCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<UTopDownCharMovementComponent>(CharacterMovementComponentName))
{
	// Set size for player capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	// Create the camera boom component
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));

	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true);
	CameraBoom->TargetArmLength = 800.f;
	CameraBoom->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
	CameraBoom->bDoCollisionTest = false;

	// Create the camera component
	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));

	TopDownCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false;
	
	AbilitySystemComponent = CreateDefaultSubobject<UTopDownAbilitySystemComponent>(TEXT("AbilitySystem"));
	DefaultAttributeSet = CreateDefaultSubobject<UTopDownAttributeSet>(TEXT("DefaultAttributeSet"));
	
	CombatTextWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("CombatTextWidget"));
	CombatTextWidget->SetupAttachment(RootComponent);
	CombatTextWidget->SetWidgetSpace(EWidgetSpace::Screen);
	
	// Activate ticking in order to update the cursor every frame.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

void ATopDownCharacter::BeginPlay()
{
	Super::BeginPlay();
	AbilitySystemComponent->InitAbilityActorInfo(this, this);
	
	// Grant initial abilities
	for (const auto& Ability : InitialGameplayAbilities)
	{
		GiveAbility(Ability.Key, Ability.Value);
	}
}

void ATopDownCharacter::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

	// stub
}

void ATopDownCharacter::OnBlueTriggerEnter()
{
	NumBlueTriggers++;
	if (NumBlueTriggers == 1)
	{
		FVector NewColor(BlueTriggerColor.R, BlueTriggerColor.G, BlueTriggerColor.B);
		GetMesh()->SetVectorParameterValueOnMaterials(BodyColorParameter, NewColor);
	}
}

void ATopDownCharacter::OnBlueTriggerExit()
{
	NumBlueTriggers--;
	if (NumBlueTriggers == 0)
	{
		FVector NewColor(DefaultColor.R, DefaultColor.G, DefaultColor.B);
		GetMesh()->SetVectorParameterValueOnMaterials(BodyColorParameter, NewColor);
	}
}

UAbilitySystemComponent* ATopDownCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void ATopDownCharacter::GiveAbility(const FName& AbilityName, TSubclassOf<class UGameplayAbility> AbilityClass)
{
	AbilitySystemComponent->GiveAbility(AbilityClass);
	GameplayAbilities.Emplace(AbilityName, AbilityClass);
}

bool ATopDownCharacter::TryActivateAbility(const FName& AbilityName)
{
	if (GameplayAbilities.Contains(AbilityName))
	{
		return AbilitySystemComponent->TryActivateAbilityByClass(GameplayAbilities[AbilityName]);
	}
	return false;
}

void ATopDownCharacter::HandleDamage(float Amount, float NewHealth)
{
	if (UCombatTextWidget* CombatWidget = Cast<UCombatTextWidget>(CombatTextWidget->GetWidget()))
	{
		CombatWidget->ShowDamage(Amount);
	}
	
	if (NewHealth == 0.0f)
	{
		TryActivateAbility("Death");
	}
}

void ATopDownCharacter::EnableRagdoll()
{
	// Turn on physics on SkeletalMeshComponent to ragdoll
	USkeletalMeshComponent* SMC = GetMesh();
	SMC->SetSimulatePhysics(true);
	SMC->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	SMC->SetAllBodiesSimulatePhysics(true);
	SMC->SetAllBodiesPhysicsBlendWeight(1.0f);
	
	// Disable collision on capsule
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

float ATopDownCharacter::GetCurrentHealth()
{
	return DefaultAttributeSet->GetHealth();
}

float ATopDownCharacter::GetHealthPct()
{
	float CurrentHealth = DefaultAttributeSet->GetHealth();
	float MaxHealth = DefaultAttributeSet->GetMaxHealth();
	return CurrentHealth / MaxHealth;
}

int ATopDownCharacter::CalculateThreatLevel()
{
	int NewThreatLevel = DEFAULT_THREAT_LEVEL;
	
	// Increase by 1 if character is moving
	if (!GetCharacterMovement()->Velocity.IsZero())
	{
		NewThreatLevel++;
	}
	
	// Decrease by 1 if character is crouching
	if (GetCharacterMovement()->IsCrouching())
	{
		NewThreatLevel--;
	}
	
	// Decrease by 1 per stealth trigger
	const FGameplayTag StealthTag = FGameplayTag::RequestGameplayTag("Buff.Stealth", false);
	NewThreatLevel -= AbilitySystemComponent->GetGameplayTagCount(StealthTag);
	
	// Prevent negative value
	if (NewThreatLevel < 0)
	{
		NewThreatLevel = 0;
	}
	
	return NewThreatLevel;
}

void ATopDownCharacter::OnStartCrouch(float HalfHeightAdjust, float ScaledHalfHeightAdjust)
{
	Super::OnStartCrouch(HalfHeightAdjust, ScaledHalfHeightAdjust);
	
	// Apply crouching effect
	FGameplayEffectContextHandle ContextHandle;
	CrouchingEffectHandle = AbilitySystemComponent->BP_ApplyGameplayEffectToSelf(CrouchingEffect, 0.0f, ContextHandle);
}

void ATopDownCharacter::OnEndCrouch(float HalfHeightAdjust, float ScaledHalfHeightAdjust)
{
	Super::OnEndCrouch(HalfHeightAdjust, ScaledHalfHeightAdjust);
	
	// Remove crouching effect
	AbilitySystemComponent->RemoveActiveGameplayEffect(CrouchingEffectHandle);
	CrouchingEffectHandle.Invalidate();
}
