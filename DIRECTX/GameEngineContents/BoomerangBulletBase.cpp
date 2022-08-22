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
	if (nullptr != Renderer)
	{
		if (Direction.CompareInt2D(float4::UP))
		{
			Renderer->GetTransform().SetLocalRotate({ 0,0,90 });
		}

		else if (Direction.CompareInt2D(float4::UP + float4::RIGHT))
		{
			Renderer->GetTransform().SetLocalRotate({ 0, 0, 45 });
		}

		else if (Direction.CompareInt2D(float4::UP + float4::LEFT))
		{
			Renderer->GetTransform().SetLocalRotate({ 0, 0, 135 });
		}

		else if (Direction.CompareInt2D(float4::RIGHT))
		{
			Renderer->GetTransform().SetLocalRotate({ 0, 0, 0 });
		}

		else if (Direction.CompareInt2D(float4::LEFT))
		{
			Renderer->GetTransform().SetLocalRotate({ 0, 0, 180 });
		}

		else if (Direction.CompareInt2D(float4::DOWN + float4::RIGHT))
		{
			Renderer->GetTransform().SetLocalRotate({ 0, 0, 315 });
		}

		else if (Direction.CompareInt2D(float4::DOWN + float4::LEFT))
		{
			Renderer->GetTransform().SetLocalRotate({ 0, 0, 225 });
		}

		else if (Direction.CompareInt2D(float4::DOWN))
		{
			Renderer->GetTransform().SetLocalRotate({ 0,0, 270 });
		}
	}
}

void BoomerangBulletBase::Start()
{
}

void BoomerangBulletBase::Update(float _DeltaTime)
{
}

void BoomerangBulletBase::End()
{
}
