#include "PreCompile.h"
#include "BulletMovementComponent.h"
#include "BulletBase.h"


BulletMovementComponent::BulletMovementComponent()
	: Speed(10.0f)
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
	float4 Direction = float4::ZERO;
	if (HorizontalDirection == "Right")
	{
		Direction += float4::RIGHT;
	}
	else if(HorizontalDirection == "Left")
	{
		Direction += float4::LEFT;
	}

	if (VerticalDirection == "Up")
	{
		Direction += float4::UP;
	}
	else if (VerticalDirection == "Down")
	{
		Direction += float4::DOWN;
	}

	BulletBase* Bullet = GetParent<BulletBase>();
	if (Bullet != nullptr)
	{
		Bullet->GetTransform().SetWorldMove(Direction * Speed);
	}
}

void BulletMovementComponent::End()
{
}
