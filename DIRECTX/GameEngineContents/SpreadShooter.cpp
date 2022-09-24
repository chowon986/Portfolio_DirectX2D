#include "PreCompile.h"
#include "SpreadShooter.h"
#include "IInGameCharacterBase.h"
#include "SpreadBullet.h"

SpreadShooter::SpreadShooter()
{
}

SpreadShooter::~SpreadShooter()
{
}

void SpreadShooter::Shoot()
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
				{
					SpreadBullet* Bullet = GetLevel()->CreateActor<SpreadBullet>();
					Bullet->GetTransform().SetWorldPosition(GetTransform().GetWorldPosition());
					float4 Dir = float4::VectorRotationToDegreeZAxis(Direction, -15);
					Bullet->SetDirection(Dir);
					Bullet->SetColMapImage(GetColMapImage());

				}

				{
					SpreadBullet* Bullet = GetLevel()->CreateActor<SpreadBullet>();
					Bullet->GetTransform().SetWorldPosition(GetTransform().GetWorldPosition());
					float4 Dir = float4::VectorRotationToDegreeZAxis(Direction, 15);
					Bullet->SetDirection(Dir);
					Bullet->SetColMapImage(GetColMapImage());

				}

				{
					SpreadBullet* Bullet = GetLevel()->CreateActor<SpreadBullet>();
					Bullet->GetTransform().SetWorldPosition(GetTransform().GetWorldPosition());
					float4 Dir = float4::VectorRotationToDegreeZAxis(Direction, 0);
					Bullet->SetDirection(Dir);
					Bullet->SetColMapImage(GetColMapImage());

				}
			}
			break;
			case InGameCharacterShooterState::SuperShot:
			{
			}
			break;
			case InGameCharacterShooterState::None:
				//SparkRenderer->ChangeFrameAnimation("Nothing");
				break;
			default:
				break;
			}
		}
	}
}

void SpreadShooter::Start()
{
}

void SpreadShooter::End()
{
}

void SpreadShooter::Update(float _DeltaTime)
{
}

