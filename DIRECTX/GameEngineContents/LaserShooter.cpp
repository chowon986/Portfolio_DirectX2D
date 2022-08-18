#include "PreCompile.h"
#include "LaserShooter.h"
#include "IInGameMonsterBase.h"
#include "Laser.h"

LaserShooter::LaserShooter()
	:MonsterAttackState(InGameMonsterAttackState::None)
{
}

LaserShooter::~LaserShooter()
{
}

void LaserShooter::Start()
{
}

void LaserShooter::End()
{
}


void LaserShooter::Update(float _DeltaTime)
{
	MonsterWeaponBase::Update(_DeltaTime);

	ElapsedTime += _DeltaTime;
	if (ElapsedTime > IntervalTime)
	{
		if (MonsterAttackState != AttackState)
		{
			MonsterAttackState = AttackState;

			switch (AttackState)
			{
			case InGameMonsterAttackState::LaserPattern1:
			{
				ElapsedTime = 0.0f;
				Laser* Bullet = GetLevel()->CreateActor<Laser>();
				Bullet->SetColMapImage(GetColMapImage());
				Bullet->GetTransform().SetWorldPosition(GetTransform().GetWorldPosition());
				Bullet->SetDirection(GetDirection());
				break;
			}
			}
		}
	}
}
