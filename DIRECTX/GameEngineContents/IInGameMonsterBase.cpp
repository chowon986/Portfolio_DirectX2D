#include "PreCompile.h"
#include "BulldogPlane.h"
#include "IInGameMonsterBase.h"

IInGameMonsterBase::IInGameMonsterBase()
	: Renderer(nullptr)
	, State(InGameMonsterState::Idle)
	, AttackState(InGameMonsterAttackState::None)
	, MoveDirection(float4::ZERO)
	, StartPos(float4::ZERO)
	, EndPos(float4::ZERO)
	, MoveSpeed(0.0f)
{
}

IInGameMonsterBase::~IInGameMonsterBase()
{
}

void IInGameMonsterBase::SetAttackState(InGameMonsterAttackState _State)
{
	if (AttackState != _State)
	{
		AttackState = _State;
		AttackStateChangedDelegate.Invoke(AttackState);
	}
}

void IInGameMonsterBase::SetRenderer(GameEngineTextureRenderer* _Renderer)
{
	Renderer = _Renderer;
}

void IInGameMonsterBase::MoveToEndPos(float4 _StartPos, float4 _EndPos, BulldogPlane* _Plane)
{
	StartPos = _StartPos;
	EndPos = _EndPos;
	MoveDirection = EndPos - StartPos;
	MoveDirection.Normalize();
	Plane = _Plane;
}

bool IInGameMonsterBase::IsEndPosArrived()
{
	if (Plane == nullptr)
	{
		if (true == GetTransform().GetWorldPosition().CompareInt2D(EndPos))
		{
			return true;
		}

		if (Direction.CompareInt2D(float4::RIGHT) &&
			GetTransform().GetWorldPosition().x >= EndPos.x)
		{
			return true;
		}

		if (Direction.CompareInt2D(float4::LEFT) &&
			GetTransform().GetWorldPosition().x <= EndPos.x)
		{
			return true;
		}

		if (Direction.CompareInt2D(float4::DOWN) &&
			GetTransform().GetWorldPosition().y <= EndPos.y)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		if (true == Plane->GetTransform().GetWorldPosition().CompareInt2D(EndPos))
		{
			return true;
		}

		if (Direction.CompareInt2D(float4::RIGHT) &&
			Plane->GetTransform().GetWorldPosition().x >= EndPos.x)
		{
			return true;
		}

		if (Direction.CompareInt2D(float4::LEFT) &&
			Plane->GetTransform().GetWorldPosition().x <= EndPos.x)
		{
			return true;
		}

		if (Direction.CompareInt2D(float4::DOWN) &&
			Plane->GetTransform().GetWorldPosition().y <= EndPos.y)
		{
			return true;
		}

		else
		{
			return false;
		}
	}
}

void IInGameMonsterBase::SetState(InGameMonsterState _State)
{
	if (State != _State)
	{
		State = _State;
		StateChangedDelegate.Invoke(State);
	}
}
