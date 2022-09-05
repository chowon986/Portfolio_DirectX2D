#include "PreCompile.h"
#include "TennisballShooter.h"
#include "IInGameMonsterBase.h"
#include "TennisballBullet.h"

TennisballShooter::TennisballShooter()
	:MonsterAttackState(InGameMonsterAttackState::None)
{
}

TennisballShooter::~TennisballShooter()
{
}

void TennisballShooter::Start()
{
}

void TennisballShooter::End()
{
}

void TennisballShooter::Update(float _DeltaTime)
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
			case InGameMonsterAttackState::TennisBall:
			{
				{
					TennisballBullet* Bullet = GetLevel()->CreateActor<TennisballBullet>();
					Bullet->GetTransform().SetWorldPosition({ GetTransform().GetWorldPosition().x - 30, GetTransform().GetWorldPosition().y+100 });
					float4 Dir = float4::VectorRotationToDegreeZAxis(GetDirection(), -15);
					Bullet->SetDirection(Dir);
					Bullet->SetColMapImage(GetColMapImage());

				}

				{
					TennisballBullet* Bullet = GetLevel()->CreateActor<TennisballBullet>();
					Bullet->GetTransform().SetWorldPosition({ GetTransform().GetWorldPosition().x + 30, GetTransform().GetWorldPosition().y+100 });
					float4 Dir = float4::VectorRotationToDegreeZAxis(GetDirection(), 15);
					Bullet->SetDirection(Dir);
					Bullet->SetColMapImage(GetColMapImage());

				}

				{
					TennisballBullet* Bullet = GetLevel()->CreateActor<TennisballBullet>();
					Bullet->GetTransform().SetWorldPosition({ GetTransform().GetWorldPosition().x, GetTransform().GetWorldPosition().y + 100 });
					float4 Dir = float4::VectorRotationToDegreeZAxis(GetDirection(), 0);
					Bullet->SetDirection(Dir);
					Bullet->SetColMapImage(GetColMapImage());
				}
			}
			}
		}
	}
}
