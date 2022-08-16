#include "PreCompile.h"
#include "BowWowShooter.h"
#include "IInGameMonsterBase.h"
#include "BowWowBullet.h"

BowWowShooter::BowWowShooter()
	:MonsterAttackState(InGameMonsterAttackState::None)
{
}

BowWowShooter::~BowWowShooter()
{
}

void BowWowShooter::Start()
{
}

void BowWowShooter::End()
{
}

void BowWowShooter::Update(float _DeltaTime)
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
			case InGameMonsterAttackState::BowWow:
			{
				int RandomAttack = rand() % 4;
				++RandomAttack;
				BowWowBullet* Bullet = GetLevel()->CreateActor<BowWowBullet>();
				if (RandomAttack == 1)
				{
					Bullet->GetRenderer()->ChangeFrameAnimation("Bow1");
				}
				else if (RandomAttack == 2)
				{
					Bullet->GetRenderer()->ChangeFrameAnimation("Bow2");
				}
				else if (RandomAttack == 3)
				{
					Bullet->GetRenderer()->ChangeFrameAnimation("Wow1");
				}
				else
				{
					Bullet->GetRenderer()->ChangeFrameAnimation("Wow2");
				}
				Bullet->SetColMapImage(GetColMapImage());
				Bullet->GetTransform().SetWorldPosition(GetTransform().GetWorldPosition());
				Bullet->SetDirection(GetDirection());
				break;
			}
			}
		}
	}
}
