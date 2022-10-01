	#include "PreCompile.h"
#include "PhysicsComponent.h"
#include "IInGameCharacterBase.h"
#include <GameEngineContents/DogFightLevel.h>

PhysicsComponent::PhysicsComponent()
	: Speed(0.0f)
	, Power(0.0f)
	, Gravity(-9.8f)
	, Mass(0.4f)
	, FixedUpdateInterval(0.01666666)
	, ElapsedTime(0)
{
	Acceleration = Gravity / Mass;
}

PhysicsComponent::~PhysicsComponent()
{
}

void PhysicsComponent::Start()
{
}

void PhysicsComponent::Update(float _DeltaTime)
{
	ElapsedTime += GameEngineTime::GetDeltaTime();
	while (ElapsedTime > FixedUpdateInterval)
	{
		ElapsedTime -= FixedUpdateInterval;
		FixedUpdate(static_cast<float>(FixedUpdateInterval));
	}
}

void PhysicsComponent::End()
{
}

void PhysicsComponent::FixedUpdate(float _DeltaTime)
{
	IInGameCharacterBase* Actor = GetParent<IInGameCharacterBase>();
	if (Actor == nullptr)
	{
		return;
	}

	GameEngineTextureRenderer* CollisionMap = Actor->GetColMapImage();
	if (CollisionMap == nullptr)
	{
		return;
	}

	GameEngineTexture* ColMapTexture = CollisionMap->GetCurTexture();
	if (ColMapTexture == nullptr)
	{
		return;
	}


	// F = ma, �� = ���� * ���ӵ�
	Power += Gravity * 20 * _DeltaTime;
	Acceleration = Power / Mass;
	Speed += Acceleration * _DeltaTime;
	Actor->GetTransform().SetWorldMove({ 0, Speed, 0 });

	while (true == ColMapTexture->GetPixelToFloat4(Actor->GetTransform().GetWorldPosition().x, -Actor->GetTransform().GetWorldPosition().y).CompareInt4D(float4::RED) ||
		Actor->GetMainCollision()->IsCollision(CollisionType::CT_AABB2D, ObjectOrder::GROUND, CollisionType::CT_AABB2D,
			std::bind(&PhysicsComponent::GroundCheck, this, std::placeholders::_1, std::placeholders::_2)))
	{
		Actor->GetTransform().SetWorldMove(float4::UP * _DeltaTime);
		Reset();
	}

	while (true == ColMapTexture->GetPixelToFloat4(static_cast<int>(Actor->GetTransform().GetWorldPosition().x), static_cast<int>(-Actor->GetTransform().GetWorldPosition().y - 10)).CompareInt4D(float4::BLACK))
	{
		Actor->GetTransform().SetWorldMove(float4::DOWN * _DeltaTime);
		Reset();
	}

	Actor->SetIsOnGround(Speed == 0);

	while (true == ColMapTexture->GetPixelToFloat4(static_cast<int>(Actor->GetTransform().GetWorldPosition().x - 10), static_cast<int>(-Actor->GetTransform().GetWorldPosition().y)).CompareInt4D(float4::BLACK) ||
		true == ColMapTexture->GetPixelToFloat4(static_cast<int>(Actor->GetTransform().GetWorldPosition().x - 10), static_cast<int>(-Actor->GetTransform().GetWorldPosition().y - 10)).CompareInt4D(float4::BLACK))
	{
		Actor->GetTransform().SetWorldMove(float4::RIGHT * _DeltaTime);
	}

	while (true == ColMapTexture->GetPixelToFloat4(static_cast<int>(Actor->GetTransform().GetWorldPosition().x + 10), static_cast<int>(-Actor->GetTransform().GetWorldPosition().y)).CompareInt4D(float4::BLACK) ||
		true == ColMapTexture->GetPixelToFloat4(static_cast<int>(Actor->GetTransform().GetWorldPosition().x + 10), static_cast<int>(-Actor->GetTransform().GetWorldPosition().y - 10)).CompareInt4D(float4::BLACK))
	{
		Actor->GetTransform().SetWorldMove(float4::LEFT * _DeltaTime);
	}

}

void PhysicsComponent::AddForce(float _Power)
{
	Power += _Power;
}

CollisionReturn PhysicsComponent::GroundCheck(GameEngineCollision* _This, GameEngineCollision* _Other)
{
	return CollisionReturn::Break;
}
