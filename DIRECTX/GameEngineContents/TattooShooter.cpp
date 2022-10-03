#include "PreCompile.h"
#include "TattooShooter.h"
#include "IInGameMonsterBase.h"
#include "TattooBullet.h"

TattooShooter::TattooShooter()
	: TattooCount(0)
{
}

TattooShooter::~TattooShooter()
{
}


void TattooShooter::Shoot(InGameMonsterAttackState State)
{
	if (Character->GetRenderer()->GetTransform().GetLocalScale().x > 0)
	{
		if (0 == TattooCount)
		{
			GetTransform().SetLocalPosition({ -350.0f, 500.0f });
		}
		else if (1 == TattooCount)
		{
			GetTransform().SetLocalPosition({ -350.0f, 400.0f });
		}
		else if (2 == TattooCount)
		{
			GetTransform().SetLocalPosition({ -350.0f, 240.0f });
		}
	}
	else
	{
		if (0 == TattooCount)
		{
			GetTransform().SetLocalPosition({ 350.0f, 500.0f });
		}
		else if (1 == TattooCount)
		{
			GetTransform().SetLocalPosition({ 350.0f, 400.0f });
		}
		else if (2 == TattooCount)
		{
			GetTransform().SetLocalPosition({ 350.0f, 240.0f });
		}
	}

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
		if (nullptr != Bullet->GetCollision())
		{
			Bullet->GetCollision()->ChangeOrder(ObjectOrder::PARRIABLEOBJECT);
		}
		Bullet->SetColMapImage(GetColMapImage());
		Bullet->GetTransform().SetWorldPosition(GetTransform().GetWorldPosition());
		Bullet->SetDirection(GetDirection());
		break;
	}
	}
	TattooCount = (TattooCount + 1) % 3;
}

void TattooShooter::Start()
{
}

void TattooShooter::End()
{
}

void TattooShooter::UpdatePivot()
{
}


void TattooShooter::Update(float _DeltaTime)
{
	MonsterWeaponBase::Update(_DeltaTime);
}
