#include "PreCompile.h"
#include "ConvergeShooter.h"
#include "IInGameCharacterBase.h"
#include "ConvergeBullet.h"
#include "SuperConvergeBullet.h"

ConvergeShooter::ConvergeShooter()
{
}

ConvergeShooter::~ConvergeShooter()
{
}

void ConvergeShooter::Shoot()
{
	if (true != GetIsEquipped())
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
				SparkRenderer->ChangeFrameAnimation("ConvergeSpark");

				float4 Direction = GetVerticalDirection() + GetHorizontalDirection();
				if (Direction.CompareInt3D(float4::ZERO))
				{
					return;
				}
				GameEngineSound::SoundPlayOneShot("sfx_player_weapon_wideshot_shoot_03.wav");
				{
					ConvergeBullet* Bullet = GetLevel()->CreateActor<ConvergeBullet>();
					Bullet->SetColMapImage(GetColMapImage());
					Bullet->GetTransform().SetWorldPosition(GetTransform().GetWorldPosition());
					float4 Dir = float4::VectorRotationToDegreeZAxis(Direction, -15);
					Bullet->SetDirection(Dir);
				}

				{
					ConvergeBullet* Bullet = GetLevel()->CreateActor<ConvergeBullet>();
					Bullet->SetColMapImage(GetColMapImage());
					Bullet->GetTransform().SetWorldPosition(GetTransform().GetWorldPosition());
					float4 Dir = float4::VectorRotationToDegreeZAxis(Direction, 15);
					Bullet->SetDirection(Dir);
				}

				{
					ConvergeBullet* Bullet = GetLevel()->CreateActor<ConvergeBullet>();
					Bullet->SetColMapImage(GetColMapImage());
					Bullet->GetTransform().SetWorldPosition(GetTransform().GetWorldPosition());
					float4 Dir = float4::VectorRotationToDegreeZAxis(Direction, 0);
					Bullet->SetDirection(Dir);
				}
			}
			break;
			case InGameCharacterShooterState::SuperShot:
			{
				float4 Direction = GetVerticalDirection() + GetHorizontalDirection();

				SuperConvergeBullet* Bullet = GetLevel()->CreateActor<SuperConvergeBullet>();
				Bullet->SetColMapImage(GetColMapImage());
				Bullet->GetTransform().SetWorldPosition(GetTransform().GetWorldPosition());
				float4 Dir = float4::VectorRotationToDegreeZAxis(Direction, 0);
				Bullet->SetDirection(Dir);

			}
			break;
			case InGameCharacterShooterState::None:
				SparkRenderer->ChangeFrameAnimation("Nothing");
				break;
			default:
				SparkRenderer->ChangeFrameAnimation("Nothing");
				break;
			}
		}
	}
}

void ConvergeShooter::Start()
{
	SparkRenderer = CreateComponent<GameEngineTextureRenderer>();
	SparkRenderer->CreateFrameAnimationFolder("ConvergeSpark", FrameAnimation_DESC("ConvergeSpark", 0.05f));
	SparkRenderer->CreateFrameAnimationFolder("Nothing", FrameAnimation_DESC("Nothing", 0.1f, false));
	SparkRenderer->AnimationBindEnd("ConvergeSpark", std::bind(&ConvergeShooter::PeashotSparkAnimationFrameFinished, this, std::placeholders::_1));
	SparkRenderer->ChangeFrameAnimation("Nothing");
	SparkRenderer->SetScaleModeImage();
	IntervalTime = 0.0f; 
	SparkRenderer->ChangeCamera(CAMERAORDER::ROTATECAMERA2);
}

void ConvergeShooter::End()
{
}

void ConvergeShooter::PeashotSparkAnimationFrameFinished(const FrameAnimation_DESC& _Info)
{
	SparkRenderer->ChangeFrameAnimation("Nothing");
}

void ConvergeShooter::Update(float _DeltaTime)
{
}

