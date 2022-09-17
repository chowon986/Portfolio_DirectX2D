#include "PreCompile.h"
#include "BoomerangShooter.h"
#include "IInGameCharacterBase.h"
#include "BoomerangBullet.h"

BoomerangShooter::BoomerangShooter()
{
	IntervalTime = 0.5f;
}

BoomerangShooter::~BoomerangShooter()
{
}

void BoomerangShooter::Start()
{
	//SparkRenderer = CreateComponent<GameEngineTextureRenderer>();
	//SparkRenderer->CreateFrameAnimationFolder("BoomerangshotSpark", FrameAnimation_DESC("BoomerangshotSpark", 0.1f));
	//SparkRenderer->ChangeFrameAnimation("BoomerangshotSpark");
	//SparkRenderer->ScaleToTexture();
}

void BoomerangShooter::End()
{
}


void BoomerangShooter::Update(float _DeltaTime)
{
	if (true != GetIsEquipped())
	{
		return;
	}
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

			BoomerangBullet* Bullet = GetLevel()->CreateActor<BoomerangBullet>();
			Bullet->GetTransform().SetWorldPosition(GetTransform().GetWorldPosition());
			Bullet->SetDirection(Direction);
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

