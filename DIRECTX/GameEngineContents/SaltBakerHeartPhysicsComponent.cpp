#include "PreCompile.h"
#include "SaltBakerHeartPhysicsComponent.h"
#include "SaltBakerHeart.h"

SaltBakerHeartPhysicsComponent::SaltBakerHeartPhysicsComponent()
	: Speed(0.0f)
	, Power(0.0f)
	, Gravity(-9.8f)
	, Mass(0.5f)
	, FixedUpdateInterval(0.01666666)
{
	Acceleration = Gravity / Mass;
}

SaltBakerHeartPhysicsComponent::~SaltBakerHeartPhysicsComponent()
{
}

void SaltBakerHeartPhysicsComponent::Start()
{
}

void SaltBakerHeartPhysicsComponent::Update(float _DeltaTime)
{
	ElapsedTime += GameEngineTime::GetDeltaTime();
	while (ElapsedTime > FixedUpdateInterval)
	{
		ElapsedTime -= FixedUpdateInterval;
		FixedUpdate(FixedUpdateInterval);
	}
}

void SaltBakerHeartPhysicsComponent::FixedUpdate(double _FixedUpdateInterval)
{
	SaltBakerHeart* Bullet = GetParent<SaltBakerHeart>();
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

	IsOnBottomGround = false;
	IsOnCeilingGround = false;

	while (true == ColMapTexture->GetPixelToFloat4(Bullet->GetTransform().GetWorldPosition().x, -(Bullet->GetTransform().GetWorldPosition().y - 15)).CompareInt4D(float4::BLACK))
	{
		Bullet->GetTransform().SetWorldMove(float4::UP * _FixedUpdateInterval);
		Reset();
		IsOnBottomGround = true;
		Bullet->SetVerticalDirection(float4::UP);
	}

	while (true == ColMapTexture->GetPixelToFloat4(Bullet->GetTransform().GetWorldPosition().x, -(Bullet->GetTransform().GetWorldPosition().y + 15)).CompareInt4D(float4::BLACK))
	{
		Bullet->GetTransform().SetWorldMove(float4::DOWN * _FixedUpdateInterval);
		Reset();
		IsOnCeilingGround = true;
		Bullet->SetVerticalDirection(float4::DOWN);
	}

	while (true == ColMapTexture->GetPixelToFloat4(Bullet->GetTransform().GetWorldPosition().x - 15, -(Bullet->GetTransform().GetWorldPosition().y )).CompareInt4D(float4::BLACK))
	{
		Bullet->GetTransform().SetWorldMove(float4::RIGHT * _FixedUpdateInterval);
		Reset();
		IsOnCeilingGround = true;
		Bullet->SetHorizontalDirection(float4::RIGHT);
	}

	while (true == ColMapTexture->GetPixelToFloat4(Bullet->GetTransform().GetWorldPosition().x - 15, -(Bullet->GetTransform().GetWorldPosition().y)).CompareInt4D(float4::BLACK))
	{
		Bullet->GetTransform().SetWorldMove(float4::LEFT * _FixedUpdateInterval);
		Reset();
		IsOnCeilingGround = true;
		Bullet->SetHorizontalDirection(float4::LEFT);
	}
}

void SaltBakerHeartPhysicsComponent::End()
{
}

void SaltBakerHeartPhysicsComponent::AddForce(float _Power)
{
	Power += _Power;
}

bool SaltBakerHeartPhysicsComponent::GroundCheck(GameEngineCollision* _This, GameEngineCollision* _Other)
{
	return true;
}
