#include "PreCompile.h"
#include "DogBowlShooter.h"
#include "IInGameMonsterBase.h"
#include "DogBowlBullet.h"
#include "MonsterPhysicsComponent.h"
#include "DogCopterShooter.h"
#include <GameEngineBase/GameEngineRandom.h>

DogBowlShooter::DogBowlShooter()
	:RedOrYellow(false)
{
	IntervalTime = 1.0f;
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
			if (ShootCount == 0)
			{
				GameEngineSound::SoundPlayOneShot("sfx_DLC_Dogfight_P3_Leader_ButtonPresses_Loop.wav");
			}

			if (ShootCount > 7)
			{
				if (Character != nullptr)
				{
					Character->SetState(InGameMonsterState::BeforeRoToateCameraOut);
					Character->SetAttackState(InGameMonsterAttackState::None);
					ShootCount = 0;
					if (DogCopterShooter* Shooter = dynamic_cast<DogCopterShooter*>(Character))
					{
						Shooter->Collision->Off();
					}

					return;
				}
			}
			ShootCount++;

			if (ShootCount < 7)
			{

				GameEngineSound::SoundPlayOneShot("sfx_DLC_Dogfight_P3_DogCopter_DogBowl_Fire_01.wav");
				DogBowlBullet* Bullet = GetLevel()->CreateActor<DogBowlBullet>();
				Bullet->SetColMapImage(GetColMapImage());
				Bullet->GetLevel()->PushToRotateCamera(Bullet);
				if (RedOrYellow == false)
				{
					Bullet->GetRenderer()->ChangeFrameAnimation("YellowDogBowlDrop");
					Bullet->GetMonsterPhysicsComponent()->Reset();
					Bullet->GetMonsterPhysicsComponent()->AddForce(30);
					Bullet->SetColor("Yellow");
					RedOrYellow = true;
				}
				else
				{
					Bullet->GetRenderer()->ChangeFrameAnimation("RedDogBowlDrop");
					Bullet->GetMonsterPhysicsComponent()->Reset();
					Bullet->GetMonsterPhysicsComponent()->AddForce(30);
					Bullet->SetColor("Red");
					RedOrYellow = false;
				}
			}
			break;
		}
		}
	}
}
