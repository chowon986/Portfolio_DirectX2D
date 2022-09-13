#include "PreCompile.h"
#include "ShellWeDancePhysicsComponent.h"
#include "ShellWeDance.h"

ShellWeDancePhysicsComponent::ShellWeDancePhysicsComponent()
	: Speed(0.0f)
	, Power(0.0f)
	, Gravity(-9.8f)
	, Mass(0.5f)
	, FixedUpdateInterval(0.01666666)
	, IsOnGround(false)
{
	Acceleration = Gravity / Mass;
}

ShellWeDancePhysicsComponent::~ShellWeDancePhysicsComponent()
{
}

void ShellWeDancePhysicsComponent::Start()
{
}

void ShellWeDancePhysicsComponent::Update(float _DeltaTime)
{
	ElapsedTime += GameEngineTime::GetDeltaTime();
	while (ElapsedTime > FixedUpdateInterval)
	{
		ElapsedTime -= FixedUpdateInterval;
		FixedUpdate(FixedUpdateInterval);
	}
}

void ShellWeDancePhysicsComponent::FixedUpdate(double _FixedUpdateInterval)
{
	ShellWeDance* Bullet = GetParent<ShellWeDance>();
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
	while (true == ColMapTexture->GetPixelToFloat4(Bullet->GetTransform().GetWorldPosition().x, -Bullet->GetTransform().GetWorldPosition().y).CompareInt4D(float4::BLACK))
	{
		Bullet->GetTransform().SetWorldMove(float4::UP * _FixedUpdateInterval);
		Reset();
		IsOnGround = true;
	}
}

void ShellWeDancePhysicsComponent::End()
{
}

void ShellWeDancePhysicsComponent::AddForce(float _Power)
{
	Power += _Power;
}

bool ShellWeDancePhysicsComponent::GroundCheck(GameEngineCollision* _This, GameEngineCollision* _Other)
{
	return true;
}
