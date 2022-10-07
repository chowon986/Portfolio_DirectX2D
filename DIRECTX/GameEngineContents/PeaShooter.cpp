#include "PreCompile.h"
#include "PeaShooter.h"
#include "IInGameCharacterBase.h"
#include "PeaBullet.h"
#include "SuperPeaBullet.h"
#include "InGameCharacterExShotEffect.h"

PeaShooter::PeaShooter()
{
}

PeaShooter::~PeaShooter()
{
}

void PeaShooter::Start()
{
	SparkRenderer = CreateComponent<GameEngineTextureRenderer>();
	SparkRenderer->CreateFrameAnimationFolder("PeashotSpark", FrameAnimation_DESC("PeashotSpark", 0.05f));
	SparkRenderer->CreateFrameAnimationFolder("Nothing", FrameAnimation_DESC("Nothing",0.1f, false));
	SparkRenderer->AnimationBindEnd("PeashotSpark", std::bind(&PeaShooter::PeashotSparkAnimationFrameFinished, this, std::placeholders::_1));
	SparkRenderer->ChangeFrameAnimation("Nothing");
	SparkRenderer->SetScaleModeImage();
	IntervalTime = 0.0f;
}

void PeaShooter::End()
{
}

void PeaShooter::Shoot()
{
	if(true != GetIsEquipped())
	{
		return;
	}

	{
		if (IInGameCharacterBase* Parent = dynamic_cast<IInGameCharacterBase*>(GetParent()))
		{
			InGameCharacterShooterState ShooterState = Parent->GetShooterState();
			switch (ShooterState)
			{

			case InGameCharacterShooterState::BasicShot:
			{
				SparkRenderer->ChangeFrameAnimation("PeashotSpark");
				float4 Direction = GetVerticalDirection() + GetHorizontalDirection();
				if (Direction.CompareInt3D(float4::ZERO))
				{
					return;
				}
				GameEngineSound::SoundPlayOneShot("sfx_player_weapon_peashot_002.wav");
				PeaBullet* Bullet = GetLevel()->CreateActor<PeaBullet>();
				Bullet->SetColMapImage(GetColMapImage());
				Bullet->GetTransform().SetWorldPosition(GetTransform().GetWorldPosition()); // Need to CHK
				Bullet->SetDirection(Direction);
			}
			break;
			case InGameCharacterShooterState::SuperShot:
			{
				float4 Direction = GetVerticalDirection() + GetHorizontalDirection();

				SuperPeaBullet* Bullet = GetLevel()->CreateActor<SuperPeaBullet>();
				Bullet->SetColMapImage(GetColMapImage());
				Bullet->GetTransform().SetWorldPosition(GetTransform().GetWorldPosition()); // Need to CHK
				Bullet->SetDirection(Direction);

				InGameCharacterExShotEffect* Dust = GetLevel()->CreateActor<InGameCharacterExShotEffect>();
				Dust->SetBoss(Parent);
				Dust->GetRenderer()->ChangeFrameAnimation("PlayerExShotEffect");
				float4 MyPos = GetTransform().GetWorldPosition();
				if (GetLevel()->GetNameCopy() == "DOGFIGHT")
				{
					if (GetHorizontalDirection().CompareInt3D(float4::RIGHT))
					{
						Dust->GetTransform().SetWorldPosition({ MyPos.x - 500, MyPos.y + 50, MyPos.z + 0.1f });
					}
					else if (GetHorizontalDirection().CompareInt3D(float4::LEFT))
					{
						Dust->GetRenderer()->GetTransform().PixLocalNegativeX();
						Dust->GetTransform().SetWorldPosition({ MyPos.x + 500, MyPos.y + 50, MyPos.z + 0.1f });
					}
				}
			}
			break;
			case InGameCharacterShooterState::None:
				SparkRenderer->ChangeFrameAnimation("Nothing");
				break;
			default:
				SparkRenderer->ChangeFrameAnimation("Nothing");
			}
		}
	}
}

void PeaShooter::PeashotSparkAnimationFrameFinished(const FrameAnimation_DESC& _Info)
{
	SparkRenderer->ChangeFrameAnimation("Nothing");
}


void PeaShooter::Update(float _DeltaTime)
{
}

