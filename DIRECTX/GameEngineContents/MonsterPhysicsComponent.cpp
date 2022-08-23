#include "PreCompile.h"
#include "MonsterPhysicsComponent.h"
#include "BulletBase.h"

MonsterPhysicsComponent::MonsterPhysicsComponent()
	: Speed(0.0f)
	, Power(0.0f)
	, Gravity(-9.8f)
	, Mass(0.5f)
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

	// F = ma, �� = ���� * ���ӵ�
	Power += Gravity * 20 * _DeltaTime;
	Acceleration = Power / Mass;
	Speed += Acceleration * _DeltaTime;
	Bullet->GetTransform().SetWorldMove({ 0, Speed, 0 });
	// ���⼭ x���� �������ָ� ��, ��� �̵��ϸ鼭 ������ �� ����

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
