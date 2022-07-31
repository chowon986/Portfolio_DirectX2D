#include "PreCompile.h"
#include "WeaponBase.h"
#include "IInGameCharacterBase.h"

WeaponBase::WeaponBase()
	: IntervalTime(0.1f)
	, ElapsedTime(0.0f)
	, HorizontalDirection("Center")
	, VerticalDirection("Center")
	, Character(nullptr)
	, State(InGameCharacterState::Prepare)
	, CharacterHorizontalDirection("Center")
	, CharacterVerticalDirection("Center")
	, AttackState(InGameCharacterAttackState::None)
{
}

WeaponBase::~WeaponBase()
{
}

void WeaponBase::UpdateDirection()
{
	Character = dynamic_cast<IInGameCharacterBase*>(GetParent());
	if (Character == nullptr)
	{
		return;
	}

	State = Character->GetState();

	CharacterVerticalDirection = Character->GetVerticalDirection();
	CharacterHorizontalDirection = Character->GetHorizontalDirection();
}

void WeaponBase::Update(float _DeltaTime)
{
	Character = dynamic_cast<IInGameCharacterBase*>(GetParent());

	if (Character == nullptr)
	{
		return;
	}

	AttackState = Character->GetAttackState();
	if (AttackState == InGameCharacterAttackState::None)
	{
		return;
	}

	if (ElapsedTime == -1 || IntervalTime == -1)
	{
		return;
	}
}
