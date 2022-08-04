#include "PreCompile.h"
#include "BoomerangBulletMovementComponent.h"
#include "BoomerangBulletBase.h"


BoomerangBulletMovementComponent::BoomerangBulletMovementComponent()
	: Speed(10.0f)
	, Direction(float4::ZERO)
{
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
		Speed -= 10*_DeltaTime;

		_Direction *= Speed;
		_Direction.y += 0.25;
		Bullet->GetTransform().SetWorldMove(_Direction);
	}

}

void BoomerangBulletMovementComponent::End()
{
}
