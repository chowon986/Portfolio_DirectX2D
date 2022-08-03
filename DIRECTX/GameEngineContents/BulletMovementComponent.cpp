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
		//Speed -= 10*_DeltaTime;

		_Direction *= Speed;
		Bullet->GetTransform().SetWorldMove(_Direction);

		//if (_Direction.x == float4::RIGHT.x) // ¿À¸¥ÂÊ
		//{
		//	if (_Direction.y == float4::UP.y)
		//	{
		//		Bullet->GetTransform().SetWorldRotation(45);
		//	}
		//	else if (_Direction.y == float4::ZERO.y)
		//	{
		//		Bullet->GetTransform().SetWorldRotation(0);
		//	}
		//	else
		//	{
		//		Bullet->GetTransform().SetWorldRotation(-45);
		//	}
		//}

		//else if (_Direction.x == float4::LEFT.x)
		//{
		//	if (Bullet->GetTransform().GetLocalScale().x > 0)
		//	{
		//		Bullet->GetTransform().SetLocalScale(Bullet->GetTransform().GetLocalScale().x * -1);

		//		if (_Direction.y == float4::UP.y)
		//		{
		//			Bullet->GetTransform().SetWorldRotation(-45);
		//			//Bullet->GetTransform().SetLocalRotation(Bullet->GetTransform().GetLocalRotation().RotationToDegreeZ(45));
		//		}
		//		else if (_Direction.y == float4::ZERO.y)
		//		{
		//			Bullet->GetTransform().SetWorldRotation(0);
		//		}
		//		else
		//		{
		//			Bullet->GetTransform().SetWorldRotation(45);
		//		}
		//	}
		//}

		//else if (_Direction.CompareInt2D(float4::UP))
		//{
		//	Bullet->GetTransform().SetWorldRotation(-90);
		//}

		//else
		//{
		//	Bullet->GetTransform().SetWorldRotation(90);
		//}

	}
}

void BulletMovementComponent::End()
{
}
