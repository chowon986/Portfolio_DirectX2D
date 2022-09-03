#include "PreCompile.h"
#include "PeaShooter.h"
#include "IInGameCharacterBase.h"
#include "PeaBullet.h"

PeaShooter::PeaShooter()
{
}

PeaShooter::~PeaShooter()
{
}

void PeaShooter::Start()
{
	//SparkRenderer = CreateComponent<GameEngineTextureRenderer>();
	//SparkRenderer->CreateFrameAnimationFolder("PeashotSpark", FrameAnimation_DESC("PeashotSpark", 0.1f));
	//SparkRenderer->ChangeFrameAnimation("PeashotSpark");
	//SparkRenderer->ScaleToTexture();
}

void PeaShooter::End()
{
}


void PeaShooter::Update(float _DeltaTime)
{
	WeaponBase::Update(_DeltaTime);

	ElapsedTime += _DeltaTime;
	if (ElapsedTime > IntervalTime)
	{
		ElapsedTime -= IntervalTime;
		if (IInGameCharacterBase* Parent = dynamic_cast<IInGameCharacterBase*>(GetParent()))
		{
			ShooterState = Parent->GetShooterState();
		}
		if (PlayerShooterState != ShooterState)
		{
			PlayerShooterState = ShooterState;

			switch (AttackState)
			{
			case InGameCharacterAttackState::Shoot:
			{
				if (PlayerShooterState == InGameCharacterShooterState::BasicShot)
				{
					float4 Direction = GetVerticalDirection() + GetHorizontalDirection();

					PeaBullet* Bullet = GetLevel()->CreateActor<PeaBullet>();
					Bullet->SetColMapImage(GetColMapImage());
					Bullet->GetTransform().SetWorldPosition(GetTransform().GetWorldPosition()); // Need to CHK
					Bullet->SetDirection(Direction);
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
}

