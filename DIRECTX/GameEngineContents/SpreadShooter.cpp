#include "PreCompile.h"
#include "SpreadShooter.h"
#include "IInGameCharacterBase.h"
#include "SpreadBullet.h"

SpreadShooter::SpreadShooter()
{
}

SpreadShooter::~SpreadShooter()
{
}

void SpreadShooter::OnCharacterAttackStateChanged(InGameCharacterAttackState _AttackState)
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

void SpreadShooter::OnCharacterVerticalDirectionChanged(std::string _VerticalDirection)
{
	UpdateDirection();
	OnVerticalDirectionChangedDelegate.Invoke(VerticalDirection);
}

void SpreadShooter::OnCharacterHorizontalDirectionChanged(std::string _HorizontalDirection)
{
	UpdateDirection();
	OnHorizontalDirectionChangedDelegate.Invoke(HorizontalDirection);
}

void SpreadShooter::SetParent(GameEngineUpdateObject* _Parent)
{
	WeaponBase::SetParent(_Parent);

	IInGameCharacterBase* Character = dynamic_cast<IInGameCharacterBase*>(GetParent());
	if (Character != nullptr)
	{
		Character->GetAttackStateChangedDelegate().Add(std::bind(&SpreadShooter::OnCharacterAttackStateChanged, this, std::placeholders::_1));
		Character->GetVerticalDirectionChangedDelegate().Add(std::bind(&SpreadShooter::OnCharacterVerticalDirectionChanged, this, std::placeholders::_1));
		Character->GetHorizontalDirectionChangedDelegate().Add(std::bind(&SpreadShooter::OnCharacterHorizontalDirectionChanged, this, std::placeholders::_1));
		UpdateDirection();
	}
}

void SpreadShooter::UpdateDirection()
{
	WeaponBase::UpdateDirection();

	if (State == InGameCharacterState::Duck)
	{
		VerticalDirection = "Center";
		HorizontalDirection = Character->GetRenderer()->GetTransform().GetLocalScale().x < 0 ? "Left" : "Right";
	}

	else if (State == InGameCharacterState::Walk)
	{
		VerticalDirection = CharacterVerticalDirection == "Down" ? "Center" : CharacterVerticalDirection;
		HorizontalDirection = Character->GetRenderer()->GetTransform().GetLocalScale().x < 0 ? "Left" : "Right";
	}

	else if (State == InGameCharacterState::Idle)
	{
		VerticalDirection = CharacterVerticalDirection;
		HorizontalDirection = CharacterVerticalDirection == "Up" ? "Center" : Character->GetRenderer()->GetTransform().GetLocalScale().x < 0 ? "Left" : "Right";
	}

	else
	{
		VerticalDirection = CharacterVerticalDirection;
		HorizontalDirection = CharacterHorizontalDirection;
	}
}

void SpreadShooter::Start()
{
}

void SpreadShooter::Update(float _DeltaTime)
{
	WeaponBase::Update(_DeltaTime);

	ElapsedTime += _DeltaTime;
	if (ElapsedTime > IntervalTime)
	{
		ElapsedTime -= IntervalTime;
		switch (AttackState)
		{
		case InGameCharacterAttackState::Shoot:
		{
			SpreadBullet* Bullet = GetLevel()->CreateActor<SpreadBullet>();
			Bullet->SetParent(this);
		}
		break;
		case InGameCharacterAttackState::SpecialAttack:
			// Å« ÃÑ¾ËÀ» ½ð´Ù.
			break;
		case InGameCharacterAttackState::SuperAttack:
			// ÇÊ»ì±â¸¦ ½ð´Ù.
			break;
		}
	}
}

void SpreadShooter::End()
{
}
