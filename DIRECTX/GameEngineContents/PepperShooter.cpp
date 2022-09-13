#include "PreCompile.h"
#include "PepperShooter.h"
#include "IInGameMonsterBase.h"
#include "PepperBullet.h"
#include "Pepper.h"
#include "IInGameCharacterBase.h"

PepperShooter::PepperShooter()
	: MonsterAttackState(InGameMonsterAttackState::None)
{
}

PepperShooter::~PepperShooter()
{
}

void PepperShooter::UpdateDirection()
{
	if (Character = dynamic_cast<IInGameMonsterBase*>(GetParent()))
	{
		State = Character->GetState();
		AttackState = Character->GetAttackState();
	}
	if (Pepper* Parent = dynamic_cast<Pepper*>(GetParent()))
	{
		Player = Parent->GetPlayer();
	}

	if (State == InGameMonsterState::Attack1)
	{
		if (Player != nullptr)
		{
			float4 PlayerPos = Player->GetTransform().GetWorldPosition();
			float4 MoveDirection = PlayerPos - GetTransform().GetWorldPosition();
			MoveDirection.Normalize();
			Direction = float4({ MoveDirection });
		}
	}

	UpdatePivot();
}


void PepperShooter::Update(float _DeltaTime)
{
	MonsterWeaponBase::Update(_DeltaTime);

	ElapsedTime += _DeltaTime;
	if (ElapsedTime > IntervalTime)
	{
		ElapsedTime -= IntervalTime;

		if (MonsterAttackState != AttackState)
		{
			MonsterAttackState = AttackState;

			switch (MonsterAttackState)
			{
			case InGameMonsterAttackState::Attack1:
			{
				PepperBullet* Bullet = GetLevel()->CreateActor<PepperBullet>();
				Bullet->GetRenderer()->ChangeFrameAnimation("Bow1");
				Bullet->SetColMapImage(GetColMapImage());
				Bullet->SetDirection(GetDirection());
			}
			break;
			}
		}
	}
}

void PepperShooter::UpdatePivot()
{
	if (State != InGameMonsterState::Attack1)
	{
		return;
	}

	if (State == InGameMonsterState::Attack1)
	{
		GetTransform().SetLocalPosition({ 0.0f, 0.0f });
	}
}

void PepperShooter::OnMonsterStateChanged(InGameMonsterState _State)
{
	UpdateDirection();
}

void PepperShooter::OnMonsterAttackStateChanged(InGameMonsterAttackState _AttackState)
{
	switch (_AttackState)
	{
	case InGameMonsterAttackState::Attack1:
		ElapsedTime = 0.0f;
		break;
	}

	UpdateDirection();
}

void PepperShooter::Start()
{
}

void PepperShooter::End()
{
}