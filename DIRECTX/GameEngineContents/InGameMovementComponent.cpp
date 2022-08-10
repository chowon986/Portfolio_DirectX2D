#include "PreCompile.h"
#include "InGameMovementComponent.h"
#include "Bulldog.h"

InGameMovementComponent::InGameMovementComponent()
	:Speed(100.0f)
	, Direction(float4::ZERO)
{
}

InGameMovementComponent::~InGameMovementComponent()
{
}

void InGameMovementComponent::SetSpeed(float _Speed)
{
	Speed = _Speed;
}

float InGameMovementComponent::GetSpeed()
{
	return Speed;
}

void InGameMovementComponent::OnStateChanged(InGameMonsterState _State)
{
	IInGameMonsterBase* InGameMonster = GetParent<IInGameMonsterBase>();
	if (InGameMonster == nullptr)
	{
		return;
	}

	switch (_State)
	{
	case InGameMonsterState::Mount:
	{
		if (nullptr != GetParent<Bulldog>())
		{
			Bulldog* BulldogMonster = GetParent<Bulldog>();
			if (false == BulldogMonster->GetTransform().GetLocalPosition().CompareInt2D(BulldogMonster->GetBeforePosition()))
			{
				MoveBeforePos(BulldogMonster->GetBeforePosition());
				Move(BulldogMonster->GetTransform().GetLocalPosition(), { BulldogMonster->GetTransform().GetLocalPosition().x, BulldogMonster->GetTransform().GetLocalPosition().y - 500 });
				SetSpeed(200.0f);
			}
		}
		break;
	}

	case InGameMonsterState::PrepareAttack1:
	{
		if (nullptr != GetParent<Bulldog>())
		{
			Bulldog* BulldogMonster = GetParent<Bulldog>();
			if (false == BulldogMonster->GetTransform().GetLocalPosition().CompareInt2D(BulldogMonster->GetBeforePosition()))
			{
				Move(BulldogMonster->GetTransform().GetLocalPosition(), { BulldogMonster->GetTransform().GetLocalPosition().x - 200, BulldogMonster->GetTransform().GetLocalPosition().y});
				SetSpeed(100.0f);
			}
		}
		break;
	}
	}
}

void InGameMovementComponent::Move(float4 _StartPos, float4 _EndPos)
{
	StartPos = _StartPos;
	EndPos = _EndPos;

	Direction = EndPos - StartPos;
	Direction.Normalize();
}

void InGameMovementComponent::MoveBeforePos(float4 _EndPos)
{
	EndPos = _EndPos;

	Bulldog* BulldogMonster = GetParent<Bulldog>();
	if (BulldogMonster == nullptr)
	{
		return;
	}

	BulldogMonster->GetTransform().SetWorldPosition(_EndPos);
}


void InGameMovementComponent::Start()
{
	IInGameMonsterBase* InGameMonster = GetParent<IInGameMonsterBase>();
	if (InGameMonster != nullptr)
	{
		InGameMonster->GetStateChangedDelegate().Add(std::bind(&InGameMovementComponent::OnStateChanged, this, std::placeholders::_1));
	}
}

void InGameMovementComponent::Update(float _DeltaTime)
{
	GameEngineActor* Actor = GetParent<GameEngineActor>();
	if (Actor == nullptr)
	{
		return;
	}

	if (true == Actor->GetTransform().GetWorldPosition().CompareInt2D(EndPos))
	{
		return;
	}

	if (Direction.CompareInt2D(float4::RIGHT) &&
		Actor->GetTransform().GetWorldPosition().x >= EndPos.x)
	{
		return;
	}

	if (Direction.CompareInt2D(float4::LEFT) &&
		Actor->GetTransform().GetWorldPosition().x <= EndPos.x)
	{
		return;
	}

	if (Direction.CompareInt2D(float4::DOWN) &&
		Actor->GetTransform().GetWorldPosition().y <= EndPos.x)
	{
		return;
	}

	Actor->GetTransform().SetWorldMove(Direction * Speed * _DeltaTime);
}

void InGameMovementComponent::End()
{
}
