// Ray Hsiao 2026


#include "TopDownAttributeSet.h"
#include "GameplayEffectExtension.h"
#include "TopDownCharacter.h"

UTopDownAttributeSet::UTopDownAttributeSet()
{
	InitHealth(150.0f);
	InitMaxHealth(150.0f);
	InitMoveSpeed(600.0f);
}

void UTopDownAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	if (Attribute == GetHealthAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.0f, GetMaxHealth());
	}
	Super::PreAttributeChange(Attribute, NewValue);
}

void UTopDownAttributeSet::PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
	if (Data.EvaluatedData.Attribute == GetDamageAttribute())
	{
		float DamageValue = GetDamage();
		
		// Don't apply damage if invulnerable
		const FGameplayTag InvulnTag = FGameplayTag::RequestGameplayTag("Buff.Invulnerable", false);
		if (Data.Target.HasMatchingGameplayTag(InvulnTag))
		{
			DamageValue = 0.0f;
		}
		
		// Calculate new health
		const float NewHealth = FMath::Clamp(GetHealth() - DamageValue, 0.0f, GetMaxHealth());
		
		if (NewHealth != GetHealth())
		{
			SetHealth(NewHealth);
			Cast<ATopDownCharacter>(Data.Target.GetOwnerActor())->HandleDamage(DamageValue, NewHealth);
		}
		
		SetDamage(0.0f);
	}
	
}
