#include "PreCompile.h"
#include "BowWowShooter.h"
#include "IInGameMonsterBase.h"
#include "IInGameCharacterBase.h"
#include "BowWowBullet.h"
#include "Ph2Dog.h"
#include <GameEngineContents/DogFightLevel.h>

BowWowShooter::BowWowShooter()
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

void BowWowShooter::Shoot(InGameMonsterAttackState State)
{
	switch (State)
	{
	case InGameMonsterAttackState::BowWow:
	{
		DogFightLevel* Level = dynamic_cast<DogFightLevel*>(GetLevel());
		if (Level == nullptr)
		{
			return;
		}

		IInGameCharacterBase* Player = Level->GetPlayer();
		if (Player == nullptr)
		{
			return;
		}

		//SetBowWowDirection(ShootPos);
		BowWowBullet* Bullet = GetLevel()->CreateActor<BowWowBullet>();
		Bullet->SetColMapImage(GetColMapImage());
		Bullet->GetTransform().SetWorldPosition({ GetTransform().GetWorldPosition().x, GetTransform().GetWorldPosition().y, -1 });


		float4 PlayerPos = Player->GetRenderer()->GetTransform().GetWorldPosition();
		float4 MyPos = Bullet->GetTransform().GetWorldPosition();
		float4 ShootPos = PlayerPos - MyPos;
		if (ShootPos.x > 0)
		{
			ShootPos.x = 1;
		}
		else if (ShootPos.x < 0)
		{
			ShootPos.x = -1;
		}
		else
		{
			ShootPos.x = 0;
		}
		if (ShootPos.y > 0)
		{
			ShootPos.y = 1;
		}
		else if (ShootPos.y < 0)
		{
			ShootPos.y = -1;
		}
		else
		{
			ShootPos.y = 0;
		}
		Bullet->SetDirection({ ShootPos.x, ShootPos.y });

		int RandomAttack = (rand() % 4) + 1;
		if (RandomAttack == 1)
		{
			Bullet->GetRenderer()->ChangeFrameAnimation("Bow1");
			break;
		}
		else if (RandomAttack == 2)
		{
			Bullet->GetRenderer()->ChangeFrameAnimation("Bow2");
			break;
		}
		else if (RandomAttack == 3)
		{
			Bullet->GetRenderer()->ChangeFrameAnimation("Wow1");
			break;
		}
		else if (RandomAttack == 4)
		{
			Bullet->GetRenderer()->ChangeFrameAnimation("Wow2");
			break;
		}
	}
	}
}

void BowWowShooter::Update(float _DeltaTime)
{
	MonsterWeaponBase::Update(_DeltaTime);

	
}
