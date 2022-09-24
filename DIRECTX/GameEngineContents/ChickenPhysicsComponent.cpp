#include "PreCompile.h"
#include "ChickenPhysicsComponent.h"
#include "Chicken.h"

ChickenPhysicsComponent::ChickenPhysicsComponent()
	: Speed(0.0f)
	, Power(0.0f)
	, Gravity(9.8f)
	, Mass(0.5f)
	, FixedUpdateInterval(0.01666666)
	, IsOnGround(false)
{
	Acceleration = Gravity / Mass;
}

ChickenPhysicsComponent::~ChickenPhysicsComponent()
{
}

void ChickenPhysicsComponent::Start()
{
}

void ChickenPhysicsComponent::Update(float _DeltaTime)
{
	ElapsedTime += GameEngineTime::GetDeltaTime();
	while (ElapsedTime > FixedUpdateInterval)
	{
		ElapsedTime -= FixedUpdateInterval;
		FixedUpdate(FixedUpdateInterval);
	}
}

void ChickenPhysicsComponent::FixedUpdate(double _FixedUpdateInterval)
{
	Chicken* Monster = GetParent<Chicken>();
	if (Monster == nullptr)
	{
		return;
	}

	GameEngineTextureRenderer* CollisionMap = Monster->GetLevel()->GetMainColMapImage();
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
	Monster->GetTransform().SetWorldMove({ 0, Speed , 0 });

	IsOnGround = false;


	while (true == ColMapTexture->GetPixelToFloat4(Monster->GetTransform().GetWorldPosition().x, -Monster->GetTransform().GetWorldPosition().y).CompareInt4D((Gravity > 0 ? float4::BLACK : float4::RED)) ||
		true == ColMapTexture->GetPixelToFloat4(Monster->GetTransform().GetWorldPosition().x, -Monster->GetTransform().GetWorldPosition().y + 15).CompareInt4D((Gravity > 0 ? float4::BLACK : float4::RED)))
	{
		Reset();

		Monster->GetTransform().SetWorldMove((Gravity > 0 ? float4::DOWN : float4::UP) * _FixedUpdateInterval);
		IsOnGround = true;
	}
}

void ChickenPhysicsComponent::End()
{
}

void ChickenPhysicsComponent::AddForce(float _Power)
{
	Power += _Power;
}

bool ChickenPhysicsComponent::GroundCheck(GameEngineCollision* _This, GameEngineCollision* _Other)
{
	return true;
}
