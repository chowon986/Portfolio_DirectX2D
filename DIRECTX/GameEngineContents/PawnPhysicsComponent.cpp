#include "PreCompile.h"
#include "PawnPhysicsComponent.h"
#include "Pawn.h"

PawnPhysicsComponent::PawnPhysicsComponent()
	: Speed(0.0f)
	, Power(0.0f)
	, Gravity(-9.8f)
	, Mass(0.5f)
	, FixedUpdateInterval(0.01666666)
{
	Acceleration = Gravity / Mass;
}

PawnPhysicsComponent::~PawnPhysicsComponent()
{
}

void PawnPhysicsComponent::Start()
{
}

void PawnPhysicsComponent::Update(float _DeltaTime)
{
	ElapsedTime += GameEngineTime::GetDeltaTime();
	while (ElapsedTime > FixedUpdateInterval)
	{
		ElapsedTime -= FixedUpdateInterval;
		FixedUpdate(FixedUpdateInterval);
	}
}

void PawnPhysicsComponent::FixedUpdate(double _FixedUpdateInterval)
{
	Pawn* Monster = GetParent<Pawn>();
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
	Monster->GetTransform().SetWorldMove({ 0, Speed, 0 });

	while (true == ColMapTexture->GetPixelToFloat4(Monster->GetTransform().GetWorldPosition().x, -(Monster->GetTransform().GetWorldPosition().y - 15)).CompareInt4D(float4::RED) &&
		Monster->GetState() != InGameMonsterState::Jump)
	{
		Monster->GetTransform().SetWorldMove(float4::UP * GameEngineTime::GetDeltaTime());
		Reset();
	}

	while (true == ColMapTexture->GetPixelToFloat4(Monster->GetTransform().GetWorldPosition().x, -(Monster->GetTransform().GetWorldPosition().y -15)).CompareInt4D(float4::BLACK))
	{
		Monster->GetTransform().SetWorldMove(float4::UP * GameEngineTime::GetDeltaTime());
		Reset();
	}

	if (Monster->IsOnGround != true)
	{
		Monster->IsOnGround = true;
	}
}

void PawnPhysicsComponent::End()
{
}

void PawnPhysicsComponent::AddForce(float _Power)
{
	Power += _Power;
}

bool PawnPhysicsComponent::GroundCheck(GameEngineCollision* _This, GameEngineCollision* _Other)
{
	return true;
}
