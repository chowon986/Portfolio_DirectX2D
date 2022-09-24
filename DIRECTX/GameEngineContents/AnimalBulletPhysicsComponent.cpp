#include "PreCompile.h"
#include "AnimalBulletPhysicsComponent.h"
#include "AnimalBullet.h"

AnimalBulletPhysicsComponent::AnimalBulletPhysicsComponent()
	: Speed(0.0f)
	, Power(0.0f)
	, Gravity(-9.8f)
	, Mass(0.5f)
	, FixedUpdateInterval(0.01666666)
	, IsOnGround(false)
{
	Acceleration = Gravity / Mass;
}

AnimalBulletPhysicsComponent::~AnimalBulletPhysicsComponent()
{
}

void AnimalBulletPhysicsComponent::Start()
{
}

void AnimalBulletPhysicsComponent::Update(float _DeltaTime)
{
	ElapsedTime += GameEngineTime::GetDeltaTime();
	while (ElapsedTime > FixedUpdateInterval)
	{
		ElapsedTime -= FixedUpdateInterval;
		FixedUpdate(FixedUpdateInterval);
	}
}

void AnimalBulletPhysicsComponent::FixedUpdate(double _FixedUpdateInterval)
{
	AnimalBullet* Bullet = GetParent<AnimalBullet>();
	if (Bullet == nullptr)
	{
		return;
	}

	GameEngineTextureRenderer* CollisionMap = Bullet->GetLevel()->GetMainColMapImage();
	if (CollisionMap == nullptr)
	{
		return;
	}

	GameEngineTexture* ColMapTexture = CollisionMap->GetCurTexture();
	if (ColMapTexture == nullptr)
	{
		return;
	}

	// F = ma, 힘 = 질량 * 가속도
	Power += Gravity * 20 * _FixedUpdateInterval;
	Acceleration = Power / Mass;
	Speed += Acceleration * _FixedUpdateInterval;
	Bullet->GetTransform().SetWorldMove({ 0, Speed , 0 });

	IsOnGround = false;
	while (true == ColMapTexture->GetPixelToFloat4(Bullet->GetTransform().GetWorldPosition().x, -Bullet->GetTransform().GetWorldPosition().y).CompareInt4D(float4::RED))
	{
		Bullet->GetTransform().SetWorldMove(float4::UP * _FixedUpdateInterval);
		Reset();
		IsOnGround = true;
	}
}

void AnimalBulletPhysicsComponent::End()
{
}

void AnimalBulletPhysicsComponent::AddForce(float _Power)
{
	Power += _Power;
}

bool AnimalBulletPhysicsComponent::GroundCheck(GameEngineCollision* _This, GameEngineCollision* _Other)
{
	return true;
}
