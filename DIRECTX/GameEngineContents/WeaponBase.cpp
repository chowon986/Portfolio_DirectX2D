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
	, ColMapImage(nullptr)
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

	UpdatePivot();
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

	if (ElapsedTime == -1)
	{
		return;
	}
}

void WeaponBase::UpdatePivot()
{
	if (AttackState != InGameCharacterAttackState::Shoot)
	{
		return;
	}

	if (State == InGameCharacterState::Duck)
	{
		if (Character->GetRenderer()->GetTransform().GetLocalScale().x > 0)
		{
			GetTransform().SetLocalPosition({ 80.0f, 60.0f });
		}
		else
		{
			GetTransform().SetLocalPosition({ -80.0f, 60.0f });
		}
	}

	else if (State == InGameCharacterState::Walk)
	{

		if (HorizontalDirection.CompareInt2D(float4::RIGHT))
		{
			if (VerticalDirection.CompareInt2D(float4::UP))
			{
				GetTransform().SetLocalPosition({ 75.0f, 120.0f });
			}

			else if (VerticalDirection.CompareInt2D(float4::ZERO))
			{
				GetTransform().SetLocalPosition({ 75.0f, 60.0f });
			}

			else
			{
				return;
			}
		}

		else if (HorizontalDirection.CompareInt2D(float4::LEFT))
		{
			if (VerticalDirection.CompareInt2D(float4::UP))
			{
				GetTransform().SetLocalPosition({ -80.0f, 120.0f });
			}

			else if (VerticalDirection.CompareInt2D(float4::ZERO))
			{
				GetTransform().SetLocalPosition({ -75.0f, 60.0f });
			}

			else
			{
				return;
			}
		}
	}

	else if (State == InGameCharacterState::Aim ||
		State == InGameCharacterState::Idle)
	{
		if (HorizontalDirection.CompareInt2D(float4::RIGHT))
		{
			if (VerticalDirection.CompareInt2D(float4::UP))
			{
				GetTransform().SetLocalPosition({ 60.0f, 120.0f });
			}

			else if (VerticalDirection.CompareInt2D(float4::DOWN))
			{
				GetTransform().SetLocalPosition({ 60.0f, 50.0f });
			}

			else
			{
				GetTransform().SetLocalPosition({ 60.0f, 80.0f });
			}
		}

		else if (HorizontalDirection.CompareInt2D(float4::LEFT))
		{
			if (VerticalDirection.CompareInt2D(float4::UP))
			{
				GetTransform().SetLocalPosition({ -60.0f, 120.0f });
			}

			else if (VerticalDirection.CompareInt2D(float4::DOWN))
			{
				GetTransform().SetLocalPosition({ -60.0f, 50.0f });
			}

			else
			{
				GetTransform().SetLocalPosition({ -60.0f, 80.0f });
			}
		}

		else
		{
			if (Character->GetRenderer()->GetTransform().GetLocalScale().x >0)
			{
				if (VerticalDirection.CompareInt2D(float4::UP))
				{
					GetTransform().SetLocalPosition({ 25.0f, 150.0f });
				}

				else if (VerticalDirection.CompareInt2D(float4::DOWN))
				{
					GetTransform().SetLocalPosition({ 30.0f, 0.0f });
				}
			}
			else
			{
				if (VerticalDirection.CompareInt2D(float4::UP))
				{
					GetTransform().SetLocalPosition({ -25.0f, 150.0f });
				}

				else if (VerticalDirection.CompareInt2D(float4::DOWN))
				{
					GetTransform().SetLocalPosition({ -30.0f, 0.0f });
				}
			}
		}

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
		ElapsedTime = -1;
		break;
	case InGameCharacterAttackState::Shoot:
		ElapsedTime = 0.0f;
		break;
	case InGameCharacterAttackState::SpecialAttack:
		ElapsedTime = 0.0f;
		break;
	case InGameCharacterAttackState::SuperAttack:
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
		SetColMapImage(Character->GetColMapImage());
	}
}