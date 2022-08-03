#include "PreCompile.h"
#include "SpreadShooter.h"
#include "IInGameCharacterBase.h"
#include "SpreadBullet.h"

SpreadShooter::SpreadShooter()
{
}

SpreadShooter::~SpreadShooter()
{
}

void SpreadShooter::Start()
{
}

void SpreadShooter::End()
{
}

void SpreadShooter::Update(float _DeltaTime)
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
			//{
			//	SpreadBullet* Bullet = GetLevel()->CreateActor<SpreadBullet>();
			//	Bullet->GetTransform().SetWorldPosition(GetTransform().GetWorldPosition());
			//	float4 Dir = float4::VectorRotationToDegreeZAxis(Direction, -7.5);
			//	Bullet->SetDirection(Dir);
			//}

			//{
			//	SpreadBullet* Bullet = GetLevel()->CreateActor<SpreadBullet>();
			//	Bullet->GetTransform().SetWorldPosition(GetTransform().GetWorldPosition());
			//	float4 Dir = float4::VectorRotationToDegreeZAxis(Direction, 7.5);
			//	Bullet->SetDirection(Dir);
			//}

			//{
			//	SpreadBullet* Bullet = GetLevel()->CreateActor<SpreadBullet>();
			//	Bullet->GetTransform().SetWorldPosition(GetTransform().GetWorldPosition());
			//	float4 Dir = float4::VectorRotationToDegreeZAxis(Direction, 0);
			//	Bullet->SetDirection(Dir);
			//}		

			{
				SpreadBullet* Bullet = GetLevel()->CreateActor<SpreadBullet>();
				Bullet->GetTransform().SetWorldPosition(GetTransform().GetWorldPosition());
				float4 Dir = float4::VectorRotationToDegreeZAxis(Direction, -15);
				Bullet->SetDirection(Dir);
			}

			{
				SpreadBullet* Bullet = GetLevel()->CreateActor<SpreadBullet>();
				Bullet->GetTransform().SetWorldPosition(GetTransform().GetWorldPosition());
				float4 Dir = float4::VectorRotationToDegreeZAxis(Direction, 15);
				Bullet->SetDirection(Dir);
			}

			{
				SpreadBullet* Bullet = GetLevel()->CreateActor<SpreadBullet>();
				Bullet->GetTransform().SetWorldPosition(GetTransform().GetWorldPosition());
				float4 Dir = float4::VectorRotationToDegreeZAxis(Direction, 0);
				Bullet->SetDirection(Dir);
			}
		}
		break;
		case InGameCharacterAttackState::SpecialAttack:
			// ū �Ѿ��� ���.
			break;
		case InGameCharacterAttackState::SuperAttack:
			// �ʻ�⸦ ���.
			break;
		}
	}
}

