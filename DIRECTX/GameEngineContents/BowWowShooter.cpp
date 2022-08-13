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
			//case InGameMonsterAttackState::BowWow1:
			//{
			//	BowWowBullet* Bullet = GetLevel()->CreateActor<BowWowBullet>();
			//	Bullet->SetColMapImage(GetColMapImage());
			//	Bullet->GetTransform().SetWorldPosition(GetTransform().GetWorldPosition());
			//	Bullet->SetDirection(GetDirection());
			//	break;
			//}
			//case InGameMonsterAttackState::BowWow2:
			//{
			//	BowWowBullet* Bullet = GetLevel()->CreateActor<BowWowBullet>();
			//	Bullet->GetRenderer()->ChangeFrameAnimation("BowWow2");
			//	Bullet->SetColMapImage(GetColMapImage());
			//	Bullet->GetTransform().SetWorldPosition(GetTransform().GetWorldPosition());
			//	Bullet->SetDirection(GetDirection());
			//	break;
			//}
			//case InGameMonsterAttackState::BowWow3:
			//{
			//	BowWowBullet* Bullet = GetLevel()->CreateActor<BowWowBullet>();
			//	Bullet->GetRenderer()->ChangeFrameAnimation("BowWow3");
			//	Bullet->SetColMapImage(GetColMapImage());
			//	Bullet->GetTransform().SetWorldPosition(GetTransform().GetWorldPosition());
			//	Bullet->SetDirection(GetDirection());
			//	break;
			//}
			}
		}
	}
}
