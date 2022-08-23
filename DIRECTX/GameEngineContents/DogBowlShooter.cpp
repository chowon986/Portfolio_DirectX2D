#include "PreCompile.h"
#include "DogBowlShooter.h"
#include "IInGameMonsterBase.h"
#include "DogBowlBullet.h"
#include "MonsterPhysicsComponent.h"

DogBowlShooter::DogBowlShooter()
	:MonsterAttackState(InGameMonsterAttackState::None)
{
}

DogBowlShooter::~DogBowlShooter()
{
}

void DogBowlShooter::Start()
{
}

void DogBowlShooter::End()
{
}

void DogBowlShooter::Update(float _DeltaTime)
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
			case InGameMonsterAttackState::DogBowl:
			{
				int RandomKey = rand() % 1;

				DogBowlBullet* Bullet = GetLevel()->CreateActor<DogBowlBullet>();
				Bullet->SetColMapImage(GetColMapImage());
				Bullet->GetTransform().SetWorldPosition({ 500.0f, 70.0f }); /* { Bullet->TopDogBowl[RandomKey]}); */
				Bullet->GetLevel()->PushToRotateCamera(Bullet);
				if (RandomKey == 0)
				{
					Bullet->GetRenderer()->ChangeFrameAnimation("RedDogBowlDrop");
					Bullet->GetMonsterPhysicsComponent()->Reset();
					Bullet->GetMonsterPhysicsComponent()->AddForce(30);
				}
				else
				{
					Bullet->GetRenderer()->ChangeFrameAnimation("YellowDogBowlDrop");
					Bullet->GetMonsterPhysicsComponent()->Reset();
					Bullet->GetMonsterPhysicsComponent()->AddForce(30);
				}
				break;
			}
			}
		}

	}
}
