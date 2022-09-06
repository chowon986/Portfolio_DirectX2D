#include "PreCompile.h"
#include "BulletMovementComponent.h"
#include "BulletBase.h"


BulletMovementComponent::BulletMovementComponent()
	: Speed(10.0f)
	, Direction(float4::ZERO)
{
}

BulletMovementComponent::~BulletMovementComponent()
{
}

void BulletMovementComponent::Start()
{
}

void BulletMovementComponent::Update(float _DeltaTime)
{
	float4 _Direction = Direction;

	BulletBase* Bullet = GetParent<BulletBase>();
	if (Bullet != nullptr)
	{
		_Direction *= Speed;
		Bullet->GetTransform().SetWorldMove(_Direction * _DeltaTime);
	}
}

void BulletMovementComponent::End()
{
}
