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
				Bullet->GetRenderer()->GetTransform().SetLocalPosition(Bullet->TopDogBowl[RandomKey]);
				if (RandomKey == 0)
				{
					Bullet->GetRenderer()->ChangeFrameAnimation("RedDogBowlDrop");
					Bullet->GetMonsterPhysicsComponent()->Reset();
					Bullet->GetMonsterPhysicsComponent()->AddForce(55);
					//Bullet->SetDirection(float4::DOWN);
				}
				else
				{
					Bullet->GetRenderer()->ChangeFrameAnimation("YellowDogBowlDrop");
					Bullet->GetMonsterPhysicsComponent()->Reset();
					Bullet->GetMonsterPhysicsComponent()->AddForce(55);
				}
				break;
			}
			}
		}

	}
}
