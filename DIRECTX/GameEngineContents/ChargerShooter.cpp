#include "PreCompile.h"
#include "ChargerShooter.h"
#include "IInGameCharacterBase.h"
#include "ChargerBullet.h"

ChargerShooter::ChargerShooter()
{
}

ChargerShooter::~ChargerShooter()
{
}

void ChargerShooter::Shoot()
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
				if (Direction.CompareInt2D(float4::ZERO))
				{
					return;
				}

				ChargerBullet* Bullet = GetLevel()->CreateActor<ChargerBullet>();
				Bullet->GetTransform().SetWorldPosition(GetTransform().GetWorldPosition());
				Bullet->SetDirection(Direction);
				Bullet->SetColMapImage(GetColMapImage());
			}
			break;
			case InGameCharacterShooterState::SuperShot:
			{
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

void ChargerShooter::Start()
{
}

void ChargerShooter::End()
{
}


void ChargerShooter::Update(float _DeltaTime)
{
}

