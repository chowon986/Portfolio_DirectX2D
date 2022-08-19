#include "PreCompile.h"
#include "BowWowShooter.h"
#include "IInGameMonsterBase.h"
#include "BowWowBullet.h"
#include "Ph2Dog.h"

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
				//int RandomAttack = rand() % 4;
				//++RandomAttack;

				//if (RandomAttack == 1)
				{
					BowWowBullet* Bullet = GetLevel()->CreateActor<BowWowBullet>();
					Bullet->GetRenderer()->ChangeFrameAnimation("Bow1");
					Bullet->SetColMapImage(GetColMapImage());
					Bullet->GetTransform().SetWorldPosition(GetTransform().GetWorldPosition());
					Ph2Dog* Dog = dynamic_cast<Ph2Dog*>(GetParent());
					if (Dog != nullptr)
					{
						Bullet->SetDirection(Dog->GetBowWowDirection());
					}
					break;
				}
				//else if (RandomAttack == 2)
				//{
				//	Bullet = GetLevel()->CreateActor<BowWowBullet>();
				//	Bullet->GetRenderer()->ChangeFrameAnimation("Bow2");
				//}
				//else if (RandomAttack == 3)
				//{
				//	Bullet = GetLevel()->CreateActor<BowWowBullet>();
				//	Bullet->GetRenderer()->ChangeFrameAnimation("Wow1");
				//}
				//else
				//{
				//	Bullet = GetLevel()->CreateActor<BowWowBullet>();
				//	Bullet->GetRenderer()->ChangeFrameAnimation("Wow2");
				//}


			}
			}
		}
	}
}
