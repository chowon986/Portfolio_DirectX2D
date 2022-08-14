#include "PreCompile.h"
#include "BulldogPlane.h"
#include "IInGameMonsterBase.h"
#include "InGameLevelBase.h"

IInGameMonsterBase::IInGameMonsterBase()
	: Renderer(nullptr)
	, State(InGameMonsterState::Idle)
	, AttackState(InGameMonsterAttackState::None)
	, MoveDirection(float4::ZERO)
	, StartPos(float4::ZERO)
	, EndPos(float4::ZERO)
	, MoveSpeed(0.0f)
	, ColMapImage(nullptr)
	, HP(0.0f)
	, Plane(nullptr)
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

void IInGameMonsterBase::OnPhaseChanged(Phase _Phase)
{
	// 페이즈가 바꼈을 때 할 게 있으면 여기서

}

void IInGameMonsterBase::Start()
{
	if (InGameLevelBase* LevelBase = dynamic_cast<InGameLevelBase*>(GetLevel()))
	{
		LevelBase->GetPhaseChangedDelegate().Add(std::bind(&IInGameMonsterBase::OnPhaseChanged, this, std::placeholders::_1));
	}
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
		if (true == GetTransform().GetLocalPosition().CompareInt2D(EndPos))
		{
			return true;
		}

		if (MoveDirection.CompareInt2D(float4::RIGHT) &&
			GetTransform().GetLocalPosition().x >= EndPos.x)
		{
			return true;
		}

		if (MoveDirection.CompareInt2D(float4::LEFT) &&
			GetTransform().GetLocalPosition().x <= EndPos.x)
		{
			return true;
		}

		if (MoveDirection.CompareInt2D(float4::DOWN) &&
			GetTransform().GetLocalPosition().y <= EndPos.y)
		{
			return true;
		}

		if (MoveDirection.CompareInt2D(float4::UP) &&
			GetTransform().GetLocalPosition().y >= EndPos.y)
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

		if (MoveDirection.CompareInt2D(float4::RIGHT) &&
			Plane->GetTransform().GetWorldPosition().x >= EndPos.x)
		{
			return true;
		}

		if (MoveDirection.CompareInt2D(float4::LEFT) &&
			Plane->GetTransform().GetWorldPosition().x <= EndPos.x)
		{
			return true;
		}

		if (MoveDirection.CompareInt2D(float4::DOWN) &&
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
