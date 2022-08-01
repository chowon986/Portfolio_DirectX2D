#include "PreCompile.h"
#include "WeaponBase.h"
#include "IInGameCharacterBase.h"

WeaponBase::WeaponBase()
	: IntervalTime(0.1f)
	, ElapsedTime(0.0f)
	, HorizontalDirection(float4::ZERO)
	, VerticalDirection(float4::ZERO)
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

	if (State == InGameCharacterState::Duck)
	{
		VerticalDirection = float4::ZERO;
		HorizontalDirection = Character->GetRenderer()->GetTransform().GetLocalScale().x < 0 ? float4::LEFT : float4::RIGHT;
	}

	else if (State == InGameCharacterState::Walk)
	{
		VerticalDirection = CharacterVerticalDirection == "Down" ? float4::ZERO : CharacterVerticalDirection == "Up" ? float4::UP : float4::ZERO;
		HorizontalDirection = Character->GetRenderer()->GetTransform().GetLocalScale().x < 0 ? float4::LEFT : float4::RIGHT;
	}

	else if (State == InGameCharacterState::Idle)
	{
		VerticalDirection = CharacterVerticalDirection == "Up" ? float4::UP : CharacterVerticalDirection == "Center" ? float4::ZERO : float4::DOWN;
		HorizontalDirection = CharacterVerticalDirection == "Up" ? float4::ZERO : Character->GetRenderer()->GetTransform().GetLocalScale().x < 0 ? float4::LEFT : float4::RIGHT;
	}

	else if (State == InGameCharacterState::Aim)
	{
		VerticalDirection = CharacterVerticalDirection == "Up" ? float4::UP : CharacterVerticalDirection == "Center" ? float4::ZERO : float4::DOWN;
		if (CharacterHorizontalDirection == "Center")
		{
			if (CharacterVerticalDirection == "Up" ||
				CharacterVerticalDirection == "Down")
			{
				HorizontalDirection = float4::ZERO;
			}
			else
			{
				HorizontalDirection = Character->GetRenderer()->GetTransform().GetLocalScale().x < 0 ? float4::LEFT : float4::RIGHT;
			}
		}
		else
		{
			HorizontalDirection = Character->GetRenderer()->GetTransform().GetLocalScale().x < 0 ? float4::LEFT : float4::RIGHT;
		}
	}
	else
	{
		VerticalDirection = CharacterVerticalDirection == "Up" ? float4::UP : CharacterVerticalDirection == "Center" ? float4::ZERO : float4::DOWN;
		HorizontalDirection = CharacterHorizontalDirection == "Left" ? float4::LEFT : CharacterHorizontalDirection == "Right" ? float4::RIGHT : float4::ZERO;
	}
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

void WeaponBase::OnCharacterVerticalDirectionChanged(std::string _VerticalDirection)
{
	UpdateDirection();
	OnVerticalDirectionChangedDelegate.Invoke(VerticalDirection);
}

void WeaponBase::OnCharacterHorizontalDirectionChanged(std::string _HorizontalDirection)
{
	UpdateDirection();
	OnHorizontalDirectionChangedDelegate.Invoke(HorizontalDirection);
}


void WeaponBase::OnCharacterStateChanged(InGameCharacterState _State)
{
	UpdateDirection();
}

void WeaponBase::OnCharacterAttackStateChanged(InGameCharacterAttackState _AttackState)
{
	switch (_AttackState)
	{
	case InGameCharacterAttackState::None:
		IntervalTime = -1;
		ElapsedTime = -1;
		break;
	case InGameCharacterAttackState::Shoot:
		IntervalTime = 0.1f;
		ElapsedTime = 0.0f;
		break;
	case InGameCharacterAttackState::SpecialAttack:
		IntervalTime = 1.0f;
		ElapsedTime = 0.0f;
		break;
	case InGameCharacterAttackState::SuperAttack:
		IntervalTime = 5.0f;
		ElapsedTime = 0.0f;
		break;
	}
	UpdateDirection();
}


void WeaponBase::SetParent(GameEngineUpdateObject* _Parent)
{
	GameEngineActor::SetParent(_Parent);

	IInGameCharacterBase* Character = dynamic_cast<IInGameCharacterBase*>(GetParent());
	if (Character != nullptr)
	{
		Character->GetStateChangedDelegate().Add(std::bind(&WeaponBase::OnCharacterStateChanged, this, std::placeholders::_1));
		Character->GetAttackStateChangedDelegate().Add(std::bind(&WeaponBase::OnCharacterAttackStateChanged, this, std::placeholders::_1));
		Character->GetVerticalDirectionChangedDelegate().Add(std::bind(&WeaponBase::OnCharacterVerticalDirectionChanged, this, std::placeholders::_1));
		Character->GetHorizontalDirectionChangedDelegate().Add(std::bind(&WeaponBase::OnCharacterHorizontalDirectionChanged, this, std::placeholders::_1));
		UpdateDirection();
	}
}