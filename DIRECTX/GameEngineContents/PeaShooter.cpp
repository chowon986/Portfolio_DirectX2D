#include "PreCompile.h"
#include "PeaShooter.h"
#include "IInGameCharacterBase.h"
#include "PeaBullet.h"

PeaShooter::PeaShooter()
{
}

PeaShooter::~PeaShooter()
{
}

void PeaShooter::OnCharacterAttackStateChanged(InGameCharacterAttackState _AttackState)
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

void PeaShooter::OnCharacterVerticalDirectionChanged(std::string _VerticalDirection)
{
	UpdateDirection();
	OnVerticalDirectionChangedDelegate.Invoke(VerticalDirection);
}

void PeaShooter::OnCharacterHorizontalDirectionChanged(std::string _HorizontalDirection)
{
	UpdateDirection();
	OnHorizontalDirectionChangedDelegate.Invoke(HorizontalDirection);
}

void PeaShooter::SetParent(GameEngineUpdateObject* _Parent)
{
	WeaponBase::SetParent(_Parent);

	IInGameCharacterBase* Character = dynamic_cast<IInGameCharacterBase*>(GetParent());
	if (Character != nullptr)
	{
		Character->GetAttackStateChangedDelegate().Add(std::bind(&PeaShooter::OnCharacterAttackStateChanged, this, std::placeholders::_1));
		Character->GetVerticalDirectionChangedDelegate().Add(std::bind(&PeaShooter::OnCharacterVerticalDirectionChanged, this, std::placeholders::_1));
		Character->GetHorizontalDirectionChangedDelegate().Add(std::bind(&PeaShooter::OnCharacterHorizontalDirectionChanged, this, std::placeholders::_1));
		UpdateDirection();
	}
}

void PeaShooter::UpdateDirection()
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

void PeaShooter::Start()
{
}

void PeaShooter::Update(float _DeltaTime)
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
			PeaBullet* Bullet = GetLevel()->CreateActor<PeaBullet>();
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

void PeaShooter::End()
{
}
