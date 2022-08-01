#include "PreCompile.h"
#include "BulletBase.h"
#include "BulletMovementComponent.h"

BulletBase::BulletBase()
	: Renderer(nullptr)
	, MovementComponent(nullptr)
{
}

BulletBase::~BulletBase()
{
}

void BulletBase::SetDirection(float4 _Direction)
{
	Direction = _Direction;
	 if (nullptr != MovementComponent)
	 {
		 MovementComponent->SetDirection(Direction);
	 }
}
