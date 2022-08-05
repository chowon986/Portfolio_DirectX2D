#include "PreCompile.h"
#include "PhysicsComponent.h"
#include "IInGameCharacterBase.h"

PhysicsComponent::PhysicsComponent()
	: Speed (0.0f)
	, Power(200.0f)
	, Gravity(-0.98f)
	, Mass(1.0f)
	, Acceleration(0.0f)
{
}

PhysicsComponent::~PhysicsComponent()
{
}

void PhysicsComponent::Start()
{
}

void PhysicsComponent::Update(float _DeltaTime)
{
	IInGameCharacterBase* Actor = GetParent<IInGameCharacterBase>();
	if (Actor == nullptr)
	{
		return;
	}

	State == Actor->GetState();

	// F = ma, 힘 = 질량 * 가속도

	Power += Gravity * _DeltaTime;
	Power = Power > Gravity ? Power : -Power;
	Acceleration = Power / Mass;
	Speed -= Acceleration * _DeltaTime;
	Actor->GetTransform().SetWorldMove({ 0, Speed, 0 });
}

void PhysicsComponent::End()
{
}

void PhysicsComponent::AddForce(float _Power)
{
	Power = _Power;
}
