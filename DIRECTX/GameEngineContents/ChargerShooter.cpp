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

			ChargerBullet* Bullet = GetLevel()->CreateActor<ChargerBullet>();
			Bullet->GetTransform().SetWorldPosition(GetTransform().GetWorldPosition()); // Need to CHK
			Bullet->SetDirection(Direction);
			Bullet->SetColMapImage(GetColMapImage());
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

