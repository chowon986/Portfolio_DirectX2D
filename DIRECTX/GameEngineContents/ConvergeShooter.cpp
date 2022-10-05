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
				float4 Direction = GetVerticalDirection() + GetHorizontalDirection();
				if (Direction.CompareInt3D(float4::ZERO))
				{
					return;
				}

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
				//SparkRenderer->ChangeFrameAnimation("Nothing");
				break;
			default:
				//SparkRenderer->ChangeFrameAnimation("Nothing");
				break;
			}
		}
	}
}

void ConvergeShooter::Start()
{
}

void ConvergeShooter::End()
{
}

void ConvergeShooter::Update(float _DeltaTime)
{
}

