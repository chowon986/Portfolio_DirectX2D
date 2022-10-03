#include "PreCompile.h"
#include "DogBowlShooter.h"
#include "IInGameMonsterBase.h"
#include "DogBowlBullet.h"
#include "MonsterPhysicsComponent.h"
#include <GameEngineBase/GameEngineRandom.h>

DogBowlShooter::DogBowlShooter()
{
	IntervalTime = 2.0f;
	ShootCount = 0;
}

DogBowlShooter::~DogBowlShooter()
{
}

void DogBowlShooter::Start()
{
	srand(time(NULL));
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
		ElapsedTime -= IntervalTime;
		switch (AttackState)
		{
		case InGameMonsterAttackState::DogBowl:
		{
			if (ShootCount > 7)
			{
				if (Character != nullptr)
				{
					Character->SetState(InGameMonsterState::BeforeRoToateCameraOut);
					Character->SetAttackState(InGameMonsterAttackState::None);
					ShootCount = 0;
					return;
				}
			}
			ShootCount++;

			if (ShootCount < 7)
			{
				int RandomKey = GameEngineRandom::MainRandom.RandomInt(0, 2);

				DogBowlBullet* Bullet = GetLevel()->CreateActor<DogBowlBullet>();
				Bullet->SetColMapImage(GetColMapImage());
				Bullet->GetLevel()->PushToRotateCamera(Bullet);
				if (RandomKey == 0)
				{
					Bullet->GetRenderer()->ChangeFrameAnimation("RedDogBowlDrop");
					Bullet->GetMonsterPhysicsComponent()->Reset();
					Bullet->GetMonsterPhysicsComponent()->AddForce(30);
					Bullet->SetColor("Red");
				}
				else
				{
					Bullet->GetRenderer()->ChangeFrameAnimation("YellowDogBowlDrop");
					Bullet->GetMonsterPhysicsComponent()->Reset();
					Bullet->GetMonsterPhysicsComponent()->AddForce(30);
					Bullet->SetColor("Yellow");
				}
			}
			break;
		}
		}
	}
}
