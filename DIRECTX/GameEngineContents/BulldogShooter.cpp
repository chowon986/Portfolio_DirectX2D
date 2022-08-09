#include "PreCompile.h"
#include "BulldogShooter.h"
#include "IInGameMonsterBase.h"
#include "YarnballBullet.h"
#include "TattooBullet.h"

BulldogShooter::BulldogShooter()
{
	IntervalTime = 0.4f;
}

BulldogShooter::~BulldogShooter()
{
}

void BulldogShooter::Start()
{
	//SparkRenderer = CreateComponent<GameEngineTextureRenderer>();
	//SparkRenderer->CreateFrameAnimationFolder("BulldogshotSpark", FrameAnimation_DESC("BulldogshotSpark", 0.1f));
	//SparkRenderer->ChangeFrameAnimation("BulldogshotSpark");
	//SparkRenderer->ScaleToTexture();
}

void BulldogShooter::End()
{
}


void BulldogShooter::Update(float _DeltaTime)
{
	MonsterWeaponBase::Update(_DeltaTime);

	ElapsedTime += _DeltaTime;
	if (ElapsedTime > IntervalTime)
	{
		ElapsedTime -= IntervalTime;
		switch (AttackState)
		{
		case InGameMonsterAttackState::Shoot1:
		{
			YarnballBullet* Bullet = GetLevel()->CreateActor<YarnballBullet>();
			Bullet->SetColMapImage(GetColMapImage());
			Bullet->GetTransform().SetWorldPosition(GetTransform().GetWorldPosition());
			Bullet->SetDirection(GetDirection());
		}
		break;
		case InGameMonsterAttackState::Shoot2:
		{
			TattooBullet* Bullet = GetLevel()->CreateActor<TattooBullet>();
			Bullet->SetColMapImage(GetColMapImage());
			Bullet->GetTransform().SetWorldPosition(GetTransform().GetWorldPosition());
			Bullet->SetDirection(GetDirection());
		}
		break;
		}
	}
}
