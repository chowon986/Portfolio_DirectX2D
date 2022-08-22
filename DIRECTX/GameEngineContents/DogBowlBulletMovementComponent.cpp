#include "PreCompile.h"
#include "DogBowlBulletMovementComponent.h"
#include "BulletBase.h"


DogBowlBulletMovementComponent::DogBowlBulletMovementComponent()
	: Speed(10.0f)
	, Direction(float4::ZERO)
{
}

DogBowlBulletMovementComponent::~DogBowlBulletMovementComponent()
{
}

void DogBowlBulletMovementComponent::Start()
{
}

void DogBowlBulletMovementComponent::Update(float _DeltaTime)
{
	float4 _Direction = Direction;

	BulletBase* Bullet = GetParent<BulletBase>();
	if (Bullet != nullptr)
	{
		_Direction *= Speed;
		Bullet->GetTransform().SetWorldMove(_Direction);
	}
}

void DogBowlBulletMovementComponent::End()
{
}
