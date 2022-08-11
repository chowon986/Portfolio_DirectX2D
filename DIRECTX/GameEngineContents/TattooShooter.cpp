#include "PreCompile.h"
#include "TattooShooter.h"
#include "IInGameMonsterBase.h"
#include "TattooBullet.h"

TattooShooter::TattooShooter()
{
	IntervalTime = 0.09f;
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
		switch (AttackState)
		{
		case InGameMonsterAttackState::Tatto1:
		{
			ElapsedTime = 0.0f;
			TattooBullet* Bullet = GetLevel()->CreateActor<TattooBullet>();
			Bullet->SetColMapImage(GetColMapImage());
			Bullet->GetTransform().SetWorldPosition(GetTransform().GetWorldPosition());
			Bullet->SetDirection(GetDirection());
		}
		break;
		}
	}
}
