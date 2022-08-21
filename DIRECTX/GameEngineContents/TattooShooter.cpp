#include "PreCompile.h"
#include "TattooShooter.h"
#include "IInGameMonsterBase.h"
#include "TattooBullet.h"

TattooShooter::TattooShooter()
	:MonsterAttackState(InGameMonsterAttackState::None)
{
}

TattooShooter::~TattooShooter()
{
}

void TattooShooter::Start()
{
}

void TattooShooter::End()
{
}


void TattooShooter::Update(float _DeltaTime)
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
			case InGameMonsterAttackState::Tattoo1:
			{
				//ElapsedTime = 0.0f;
				TattooBullet* Bullet = GetLevel()->CreateActor<TattooBullet>();
				Bullet->SetColMapImage(GetColMapImage());
				Bullet->GetTransform().SetWorldPosition(GetTransform().GetWorldPosition());
				Bullet->SetDirection(GetDirection());
				break;
			}
			case InGameMonsterAttackState::Tattoo2:
			{
				//ElapsedTime = 0.0f;
				TattooBullet* Bullet = GetLevel()->CreateActor<TattooBullet>();
				Bullet->GetRenderer()->ChangeFrameAnimation("BulldogTattooB");
				Bullet->SetColMapImage(GetColMapImage());
				Bullet->GetTransform().SetWorldPosition(GetTransform().GetWorldPosition());
				Bullet->SetDirection(GetDirection());
				break;
			}
			case InGameMonsterAttackState::Tattoo3:
			{
				//ElapsedTime = 0.0f;
				TattooBullet* Bullet = GetLevel()->CreateActor<TattooBullet>();
				Bullet->GetRenderer()->ChangeFrameAnimation("BulldogTattooPink");
				Bullet->SetColMapImage(GetColMapImage());
				Bullet->GetTransform().SetWorldPosition(GetTransform().GetWorldPosition());
				Bullet->SetDirection(GetDirection());
				break;
			}
			}
		}
	}
}
