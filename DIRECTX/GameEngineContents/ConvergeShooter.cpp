#include "PreCompile.h"
#include "ConvergeShooter.h"
#include "IInGameCharacterBase.h"
#include "ConvergeBullet.h"

ConvergeShooter::ConvergeShooter()
{
}

ConvergeShooter::~ConvergeShooter()
{
}

void ConvergeShooter::Start()
{
}

void ConvergeShooter::End()
{
}

void ConvergeShooter::Update(float _DeltaTime)
{
	WeaponBase::Update(_DeltaTime);

	ElapsedTime += _DeltaTime;
	if (ElapsedTime > IntervalTime)
	{
		ElapsedTime -= IntervalTime;
		switch (AttackState)
		{
		case InGameCharacterAttackState::Shoot:
		{
			float4 Direction = GetVerticalDirection() + GetHorizontalDirection();
			{
				ConvergeBullet* Bullet = GetLevel()->CreateActor<ConvergeBullet>();
				Bullet->GetTransform().SetWorldPosition(GetTransform().GetWorldPosition());
				float4 Dir = float4::VectorRotationToDegreeZAxis(Direction, -15);
				Bullet->SetDirection(Dir);
			}

			{
				ConvergeBullet* Bullet = GetLevel()->CreateActor<ConvergeBullet>();
				Bullet->GetTransform().SetWorldPosition(GetTransform().GetWorldPosition());
				float4 Dir = float4::VectorRotationToDegreeZAxis(Direction, 15);
				Bullet->SetDirection(Dir);
			}

			{
				ConvergeBullet* Bullet = GetLevel()->CreateActor<ConvergeBullet>();
				Bullet->GetTransform().SetWorldPosition(GetTransform().GetWorldPosition());
				float4 Dir = float4::VectorRotationToDegreeZAxis(Direction, 0);
				Bullet->SetDirection(Dir);
			}
		}
		break;
		case InGameCharacterAttackState::SpecialAttack:
			// Å« ÃÑ¾ËÀ» ½ð´Ù.
			break;
		case InGameCharacterAttackState::SuperAttack:
			// ÇÊ»ì±â¸¦ ½ð´Ù.
			break;
		}
	}
}

