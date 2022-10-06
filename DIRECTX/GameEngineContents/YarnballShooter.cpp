#include "PreCompile.h"
#include "YarnballShooter.h"
#include "IInGameMonsterBase.h"
#include "YarnballBullet.h"

YarnballShooter::YarnballShooter()
	:MonsterAttackState(InGameMonsterAttackState::None)
{
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

void YarnballShooter::UpdatePivot()
{
	if (State != InGameMonsterState::Attack1)
	{
		return;
	}

	else
	{
		if (Character->GetRenderer()->GetTransform().GetLocalScale().x > 0)
		{
			GetTransform().SetLocalPosition({ 350.0f, 350.0f });
		}
		else
		{
			GetTransform().SetLocalPosition({ -350.0f, 350.0f });
		}
	}
}

void YarnballShooter::Update(float _DeltaTime)
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
			case InGameMonsterAttackState::YarnBall1:
			{
				YarnballBullet* Bullet = GetLevel()->CreateActor<YarnballBullet>();
				Bullet->SetColMapImage(GetColMapImage());
				Bullet->GetTransform().SetWorldPosition(GetTransform().GetWorldPosition());
				Bullet->SetDirection(GetDirection());
				GameEngineSound::SoundPlayOneShot("sfx_DLC_Dogfight_P1_CatGun_Shoot_05.wav");
				break;
			}
			case InGameMonsterAttackState::YarnBall2:
			{
				YarnballBullet* Bullet = GetLevel()->CreateActor<YarnballBullet>();
				Bullet->GetRenderer()->ChangeFrameAnimation("Yarnball2");
				Bullet->SetColMapImage(GetColMapImage());
				Bullet->GetTransform().SetWorldPosition(GetTransform().GetWorldPosition());
				Bullet->SetDirection(GetDirection());
				GameEngineSound::SoundPlayOneShot("sfx_DLC_Dogfight_P1_CatGun_Shoot_05.wav");
				break;
			}
			case InGameMonsterAttackState::YarnBall3:
			{
				YarnballBullet* Bullet = GetLevel()->CreateActor<YarnballBullet>();
				Bullet->GetRenderer()->ChangeFrameAnimation("YarnBall3");
				Bullet->SetColMapImage(GetColMapImage());
				Bullet->GetTransform().SetWorldPosition(GetTransform().GetWorldPosition());
				Bullet->SetDirection(GetDirection());
				GameEngineSound::SoundPlayOneShot("sfx_DLC_Dogfight_P1_CatGun_Shoot_05.wav");
				break;
			}
			}
		}
	}
}
