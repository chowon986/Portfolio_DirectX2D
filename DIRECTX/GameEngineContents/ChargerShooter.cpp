#include "PreCompile.h"
#include "ChargerShooter.h"
#include "IInGameCharacterBase.h"
#include "ChargerBullet.h"

ChargerShooter::ChargerShooter()
{
}

ChargerShooter::~ChargerShooter()
{
}

void ChargerShooter::Start()
{
}

void ChargerShooter::End()
{
}


void ChargerShooter::Update(float _DeltaTime)
{
	if (true != GetIsEquipped())
	{
		return;
	}
	WeaponBase::Update(_DeltaTime);

	ElapsedTime += _DeltaTime;
	ChargeTime += _DeltaTime;
	if (ElapsedTime > IntervalTime)
	{
		ElapsedTime -= IntervalTime;
		switch (AttackState)
		{
		case InGameCharacterAttackState::Shoot:
		{
			float4 Direction = GetVerticalDirection() + GetHorizontalDirection();
			if (Direction.CompareInt2D(float4::ZERO))
			{
				return;
			}

			ChargerBullet* Bullet = GetLevel()->CreateActor<ChargerBullet>();
			Bullet->GetTransform().SetWorldPosition(GetTransform().GetWorldPosition());
			Bullet->SetDirection(Direction);
			Bullet->SetColMapImage(GetColMapImage());
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

