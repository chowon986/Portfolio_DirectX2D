#include "PreCompile.h"
#include "YarnballShooter.h"
#include "IInGameMonsterBase.h"
#include "YarnballBullet.h"

YarnballShooter::YarnballShooter()
{
	IntervalTime = 0.09f;
}

YarnballShooter::~YarnballShooter()
{
}

void YarnballShooter::Start()
{
}

void YarnballShooter::End()
{
}

void YarnballShooter::Update(float _DeltaTime)
{
	MonsterWeaponBase::Update(_DeltaTime);

	ElapsedTime += _DeltaTime;
	if (ElapsedTime > IntervalTime)
	{
		ElapsedTime = 0.0f;
		switch (AttackState)
		{
		case InGameMonsterAttackState::YarnBall1:
		{
			YarnballBullet* Bullet = GetLevel()->CreateActor<YarnballBullet>();
			Bullet->SetColMapImage(GetColMapImage());
			Bullet->GetTransform().SetWorldPosition(GetTransform().GetWorldPosition());
			Bullet->SetDirection(GetDirection());
			break;
		}
		case InGameMonsterAttackState::YarnBall2:
		{
			YarnballBullet* Bullet = GetLevel()->CreateActor<YarnballBullet>();
			Bullet->GetRenderer()->ChangeFrameAnimation("Yarnball2");
			Bullet->SetColMapImage(GetColMapImage());
			Bullet->GetTransform().SetWorldPosition(GetTransform().GetWorldPosition());
			Bullet->SetDirection(GetDirection());
			break;
		}
		case InGameMonsterAttackState::YarnBall3:
		{
			YarnballBullet* Bullet = GetLevel()->CreateActor<YarnballBullet>();
			Bullet->GetRenderer()->ChangeFrameAnimation("YarnBall3");
			Bullet->SetColMapImage(GetColMapImage());
			Bullet->GetTransform().SetWorldPosition(GetTransform().GetWorldPosition());
			Bullet->SetDirection(GetDirection());
			break;
		}
		}
	}
}
