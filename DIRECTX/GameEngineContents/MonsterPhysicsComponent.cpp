#include "PreCompile.h"
#include "MonsterPhysicsComponent.h"
#include "BulletBase.h"

MonsterPhysicsComponent::MonsterPhysicsComponent()
	: Speed(0.0f)
	, Power(0.0f)
	, Gravity(-9.8f)
	, Mass(0.5f)
	, FixedUpdateInterval(0.01666666)
{
	Acceleration = Gravity / Mass;
}

MonsterPhysicsComponent::~MonsterPhysicsComponent()
{
}

void MonsterPhysicsComponent::Start()
{
}

void MonsterPhysicsComponent::Update(float _DeltaTime)
{
	ElapsedTime += GameEngineTime::GetDeltaTime();
	while (ElapsedTime > FixedUpdateInterval)
	{
		ElapsedTime -= FixedUpdateInterval;
		FixedUpdate(FixedUpdateInterval);
	}
}

void MonsterPhysicsComponent::FixedUpdate(double _FixedUpdateInterval)
{
	BulletBase* Bullet = GetParent<BulletBase>();
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
	Bullet->GetTransform().SetWorldMove({ 0, Speed /** GameEngineTime::GetDeltaTime()*/, 0});
	// 여기서 x값을 조정해주면 좌, 우로 이동하면서 내려갈 것 같음

	//Bullet->SetIsOnGround(Speed == 0);
}

void MonsterPhysicsComponent::End()
{
}

void MonsterPhysicsComponent::AddForce(float _Power)
{
	Power += _Power;
}

bool MonsterPhysicsComponent::GroundCheck(GameEngineCollision* _This, GameEngineCollision* _Other)
{
	return true;
}
