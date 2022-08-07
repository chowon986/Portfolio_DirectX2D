#include "PreCompile.h"
#include "InGameMonsterMovementComponent.h"
#include "IInGameMonsterBase.h"
#include "IngameCuphead.h"
#include "PhysicsComponent.h"
#include <functional>

InGameMonsterMovementComponent::InGameMonsterMovementComponent()
{
}

InGameMonsterMovementComponent::~InGameMonsterMovementComponent()
{
}

void InGameMonsterMovementComponent::OnStateChanged(InGameMonsterState _State)
{
	UpdateDirection();
}

void InGameMonsterMovementComponent::OnDirectionChanged(std::string _Dir)
{
	UpdateDirection();
}

void InGameMonsterMovementComponent::UpdateDirection()
{
	IInGameMonsterBase* InGameMonster = GetParent<IInGameMonsterBase>();
	if (InGameMonster == nullptr ||
		InGameMonster->GetState() == InGameMonsterState::Idle)
	{
		Direction = float4::ZERO;
		return;
	}

}

void InGameMonsterMovementComponent::Start()
{
	Direction = float4::ZERO;

	InGameMonster = GetParent<IInGameMonsterBase>();
	if (InGameMonster != nullptr)
	{
		InGameMonster->GetStateChangedDelegate().Add(std::bind(&InGameMonsterMovementComponent::OnStateChanged, this, std::placeholders::_1));
	}
}

void InGameMonsterMovementComponent::Update(float _DeltaTime)
{
	if (InGameMonster == nullptr)
	{
		return;
	}

	InGameMonsterState State = InGameMonster->GetState();

}

void InGameMonsterMovementComponent::End()
{
}

