#include "PreCompile.h"
#include "InGameMovementComponent.h"
#include "Bulldog.h"

InGameMovementComponent::InGameMovementComponent()
	:Speed(100.0f)
	, Direction(float4::ZERO)
	, ImageDir(float4::ZERO)
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

	State = _State;

	switch (_State)
	{
	case InGameMonsterState::Unmount:
	{
		if (nullptr != GetParent<Bulldog>())
		{
			Bulldog* BulldogMonster = GetParent<Bulldog>();

			Move(BulldogMonster->GetTransform().GetLocalPosition(), { BulldogMonster->GetTransform().GetLocalPosition().x, BulldogMonster->GetTransform().GetLocalPosition().y + 300 });
			SetSpeed(100.0f);
		}
		break;
	}

	case InGameMonsterState::Mount:
	{
		if (nullptr != GetParent<Bulldog>())
		{
			Bulldog* BulldogMonster = GetParent<Bulldog>();
				MoveBeforePos(BulldogMonster->GetBeforePosition());
				Move(BulldogMonster->GetTransform().GetLocalPosition(), { BulldogMonster->GetTransform().GetLocalPosition().x, BulldogMonster->GetTransform().GetLocalPosition().y - 300});
				SetSpeed(150.0f);
		}
		break;
	}

	case InGameMonsterState::PrepareAttack1:
	{
		if (nullptr != GetParent<Bulldog>())
		{
			Bulldog* BulldogMonster = GetParent<Bulldog>();
				ImageDir = BulldogMonster->GetRenderer()->GetTransform().GetLocalScale().x < 0 ? BulldogMonster->GetTransform().GetLocalPosition().x + 150 : BulldogMonster->GetTransform().GetLocalPosition().x - 150;
				Move(BulldogMonster->GetTransform().GetLocalPosition(), { ImageDir.x, BulldogMonster->GetTransform().GetLocalPosition().y });
				SetSpeed(100.0f);
		}
		break;
	}

	case InGameMonsterState::PrepareAttack2:
	{
		if (nullptr != GetParent<Bulldog>())
		{
			Bulldog* BulldogMonster = GetParent<Bulldog>();
				Move(BulldogMonster->GetTransform().GetLocalPosition(), { BulldogMonster->GetTransform().GetLocalPosition().x, BulldogMonster->GetTransform().GetLocalPosition().y - 450 });
				SetSpeed(110.0f);
		}
		break;
	}

	case InGameMonsterState::Attack2:
	{
		if (nullptr != GetParent<Bulldog>())
		{
			Bulldog* BulldogMonster = GetParent<Bulldog>();
				Move(BulldogMonster->GetTransform().GetLocalPosition(), { BulldogMonster->GetTransform().GetLocalPosition().x, BulldogMonster->GetTransform().GetLocalPosition().y - 300 });
				SetSpeed(150.0f);
		}
		break;
	}

	case InGameMonsterState::AttackFinish2:
	{
		if (nullptr != GetParent<Bulldog>())
		{
			Bulldog* BulldogMonster = GetParent<Bulldog>();
				Move(BulldogMonster->GetTransform().GetLocalPosition(), { BulldogMonster->GetTransform().GetLocalPosition().x, BulldogMonster->GetTransform().GetLocalPosition().y + 100 });
				SetSpeed(100.0f);
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
		Actor->GetTransform().GetWorldPosition().y <= EndPos.y)
	{
		return;
	}

	if (State == InGameMonsterState::AttackFinish2)
	{
		Actor->GetTransform().SetWorldMove(Direction * 4 * Speed * _DeltaTime);

	}
	else
	{
		Actor->GetTransform().SetWorldMove(Direction * Speed * _DeltaTime);
	}
}

void InGameMovementComponent::End()
{
}
