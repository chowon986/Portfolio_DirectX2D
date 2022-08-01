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

void PeaShooter::Start()
{
}

void PeaShooter::End()
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
			float4 Direction = GetVerticalDirection() + GetHorizontalDirection();

			PeaBullet* Bullet = GetLevel()->CreateActor<PeaBullet>();
			Bullet->GetTransform().SetWorldPosition(GetTransform().GetWorldPosition());
			Bullet->SetDirection(Direction);
		}
		break;
		case InGameCharacterAttackState::SpecialAttack:
			// ū �Ѿ��� ���.
			break;
		case InGameCharacterAttackState::SuperAttack:
			// �ʻ�⸦ ���.
			break;
		}
	}
}

