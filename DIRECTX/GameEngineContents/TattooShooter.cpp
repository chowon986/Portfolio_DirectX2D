#include "PreCompile.h"
#include "TattooShooter.h"
#include "IInGameMonsterBase.h"
#include "TattooBullet.h"

TattooShooter::TattooShooter()
	: MonsterAttackState(InGameMonsterAttackState::None)
	, TattooCount(0)
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

void TattooShooter::UpdatePivot()
{

	if (State != InGameMonsterState::Attack2 ||
		AttackState == InGameMonsterAttackState::None)
	{
		return;
	}

	else
	{
		if (Character->GetRenderer()->GetTransform().GetLocalScale().x > 0)
		{
			++TattooCount;

			if (1 == TattooCount)
			{
				GetTransform().SetLocalPosition({ -350.0f, 500.0f,(int)ZOrder::NPC - 1 });
			}
			else if (2 == TattooCount)
			{
				GetTransform().SetLocalPosition({ -350.0f, 400.0f,(int)ZOrder::NPC - 1 });
			}
			else if(3 == TattooCount)
			{
				GetTransform().SetLocalPosition({ -350.0f, 240.0f,(int)ZOrder::NPC - 1 });
				TattooCount = 0;
			}
			else
			{
				TattooCount = 0;
			}
		}
		else
		{
			++TattooCount;

			if (1 == TattooCount)
			{
				GetTransform().SetLocalPosition({ 350.0f, 500.0f,(int)ZOrder::NPC - 1 });
			}
			else if (2 == TattooCount)
			{
				GetTransform().SetLocalPosition({ 350.0f, 400.0f,(int)ZOrder::NPC - 1 });
			}
			else if(3 == TattooCount)
			{
				GetTransform().SetLocalPosition({ 350.0f, 240.0f,(int)ZOrder::NPC - 1 });
				TattooCount = 0;
			}
			else
			{
				TattooCount = 0;
			}
		}
	}

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
		}
	}
}
