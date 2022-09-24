#include "PreCompile.h"
#include "BoomerangShooter.h"
#include "IInGameCharacterBase.h"
#include "BoomerangBullet.h"
#include "SuperBoomerangBullet.h"
#include "SuperBoomerangBulletMovementComponent.h"

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

void BoomerangShooter::Shoot()
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
				float4 Direction = GetVerticalDirection() + GetHorizontalDirection();

				BoomerangBullet* Bullet = GetLevel()->CreateActor<BoomerangBullet>();
				Bullet->GetTransform().SetWorldPosition(GetTransform().GetWorldPosition());
				Bullet->SetDirection(Direction);
			}
			break;
			case InGameCharacterShooterState::SuperShot:
			{
				float4 Direction = GetVerticalDirection() + GetHorizontalDirection();
				if (Direction.CompareInt3D(float4::ZERO))
				{
					return;
				}
				SuperBoomerangBullet* Bullet = GetLevel()->CreateActor<SuperBoomerangBullet>();
				Bullet->SetColMapImage(GetColMapImage());
				Bullet->GetTransform().SetWorldPosition(GetTransform().GetWorldPosition()); // Need to CHK

				if (SuperBoomerangBulletMovementComponent* Movement = dynamic_cast<SuperBoomerangBulletMovementComponent*>(Bullet->GetMovementComponent()))
				{
					Movement->AddForce(Direction * 10);
					Movement->SetGravity(-Direction);
				}
			}
			break;
			default:
				break;
			}
		}
	}
}


void BoomerangShooter::Update(float _DeltaTime)
{
}

