#include "PreCompile.h"
#include "PeaShooter.h"
#include "IInGameCharacterBase.h"
#include "PeaBullet.h"

PeaShooter::PeaShooter()
	: PlayerShooterState(InGameCharacterShooterState::None)
{
}

PeaShooter::~PeaShooter()
{
}

void PeaShooter::Start()
{
	SparkRenderer = CreateComponent<GameEngineTextureRenderer>();
	SparkRenderer->CreateFrameAnimationFolder("PeashotSpark", FrameAnimation_DESC("PeashotSpark", 0.1f));
	SparkRenderer->CreateFrameAnimationFolder("Nothing", FrameAnimation_DESC("Nothing", 0.1f));
	SparkRenderer->AnimationBindEnd("PeashotSpark", std::bind(&PeaShooter::PeashotSparkAnimationFrameFinished, this, std::placeholders::_1));
	SparkRenderer->ChangeFrameAnimation("Nothing");
	SparkRenderer->SetScaleModeImage();
}

void PeaShooter::End()
{
}

void PeaShooter::PeashotSparkAnimationFrameFinished(const FrameAnimation_DESC& _Info)
{
	SparkRenderer->ChangeFrameAnimation("Nothing");
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
					SparkRenderer->ChangeFrameAnimation("PeashotSpark");
					float4 Direction = GetVerticalDirection() + GetHorizontalDirection();

					PeaBullet* Bullet = GetLevel()->CreateActor<PeaBullet>();
					Bullet->SetColMapImage(GetColMapImage());
					Bullet->GetTransform().SetWorldPosition(GetTransform().GetWorldPosition()); // Need to CHK
					Bullet->SetDirection(Direction);
				}
			}
			break;
			case InGameCharacterAttackState::SpecialAttack:
				// Å« ÃÑ¾ËÀ» ½ð´Ù.
				break;
			case InGameCharacterAttackState::SuperAttack:
				// ÇÊ»ì±â¸¦ ½ð´Ù.
				break;
			case InGameCharacterAttackState::None:
				SparkRenderer->ChangeFrameAnimation("Nothing");
				break;
			default:
				SparkRenderer->ChangeFrameAnimation("Nothing");
			}
		}
	}
}

