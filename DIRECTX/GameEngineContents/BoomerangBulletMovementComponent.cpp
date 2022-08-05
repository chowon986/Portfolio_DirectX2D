#include "PreCompile.h"
#include "BoomerangBulletMovementComponent.h"
#include "BoomerangBulletBase.h"


BoomerangBulletMovementComponent::BoomerangBulletMovementComponent()
	: Speed(10.0f)
	, Direction(float4::ZERO)
{
	InitialY = 2.0f;
}

BoomerangBulletMovementComponent::~BoomerangBulletMovementComponent()
{
}

void BoomerangBulletMovementComponent::Start()
{
}

void BoomerangBulletMovementComponent::Update(float _DeltaTime)
{
	float4 _Direction = Direction;

	BoomerangBulletBase* Bullet = GetParent<BoomerangBulletBase>();
	if (Bullet != nullptr)
	{
		Speed -= 10 * _DeltaTime;

		_Direction *= Speed;
		InitialY -= _DeltaTime;
		if (InitialY <= 0)
		{
			InitialY = 0;
		}
		_Direction.y += InitialY;
		Bullet->GetTransform().SetWorldMove(_Direction);
	}

}

void BoomerangBulletMovementComponent::End()
{
}
