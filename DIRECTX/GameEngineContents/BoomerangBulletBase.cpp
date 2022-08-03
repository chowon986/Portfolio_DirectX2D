#include "PreCompile.h"
#include "BoomerangBulletBase.h"
#include "BoomerangBulletMovementComponent.h"

BoomerangBulletBase::BoomerangBulletBase()
	: Renderer(nullptr)
	, MovementComponent(nullptr)
{
}

BoomerangBulletBase::~BoomerangBulletBase()
{
}

void BoomerangBulletBase::SetDirection(float4 _Direction)
{
	Direction = _Direction;
	if (nullptr != MovementComponent)
	{
		MovementComponent->SetDirection(Direction);
	}
}
