#include "PreCompile.h"
#include "SuperBoomerangBulletMovementComponent.h"
#include "BulletBase.h"


SuperBoomerangBulletMovementComponent::SuperBoomerangBulletMovementComponent()
	: Speed(0.0f)
	, Direction(float4::ZERO)
	, Power(0.0f)
	, Gravity(0.0f)
	, Mass(0.4f)
	, FixedUpdateInterval(0.01666666)
	, ElapsedTime(0)
{
}

SuperBoomerangBulletMovementComponent::~SuperBoomerangBulletMovementComponent()
{
}

void SuperBoomerangBulletMovementComponent::Start()
{
}

void SuperBoomerangBulletMovementComponent::Update(float _DeltaTime)
{
	ElapsedTime += GameEngineTime::GetDeltaTime();
	while (ElapsedTime > FixedUpdateInterval)
	{
		ElapsedTime -= FixedUpdateInterval;
		FixedUpdate(static_cast<float>(FixedUpdateInterval));
	}
}
void SuperBoomerangBulletMovementComponent::FixedUpdate(float _DeltaTime)
{
	float4 _Direction = Direction;

	BulletBase* Bullet = GetParent<BulletBase>();

	// F = ma, 힘 = 질량 * 가속도
	Power += Gravity * 20 * _DeltaTime;
	Acceleration = Power / Mass;
	Speed += Acceleration * _DeltaTime;
	Bullet->GetTransform().SetWorldMove(Speed);
}

void SuperBoomerangBulletMovementComponent::End()
{
}

void SuperBoomerangBulletMovementComponent::AddForce(float4 _Power)
{
	Power += _Power;
}
