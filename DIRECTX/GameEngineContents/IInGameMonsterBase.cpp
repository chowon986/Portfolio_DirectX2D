#include "PreCompile.h"
#include "IInGameMonsterBase.h"

IInGameMonsterBase::IInGameMonsterBase()
	: Renderer(nullptr)
	, State(InGameMonsterState::Idle)
	, AttackState(InGameMonsterAttackState::None)
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

void IInGameMonsterBase::SetState(InGameMonsterState _State)
{
	if (State != _State)
	{
		State = _State;
		StateChangedDelegate.Invoke(State);
	}
}
