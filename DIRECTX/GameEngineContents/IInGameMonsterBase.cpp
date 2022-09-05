#include "PreCompile.h"
#include "BulldogPlane.h"
#include "IInGameMonsterBase.h"
#include "InGameLevelBase.h"

IInGameMonsterBase::IInGameMonsterBase()
	: Renderer(nullptr)
	, State(InGameMonsterState::Idle)
	, Ph2DogState(InGamePh2DogState::None)
	, AttackState(InGameMonsterAttackState::None)
	, ColMapImage(nullptr)
	, HP(0.0f)
	, Plane(nullptr)
	, IsAnimatedOrderPositive(true)
	, AnimationNum(0)
	, Number(std::to_string(AnimationNum))
	, Angle(0.0f)
	, StartAngle(0.0f)
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
		//LevelBase->GetPhaseChangedDelegate().Add(std::bind(&IInGameMonsterBase::OnPhaseChanged, this, std::placeholders::_1));
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

void IInGameMonsterBase::SetPh2DogState(InGamePh2DogState _State)
{
	if (Ph2DogState != _State)
	{
		Ph2DogState = _State;
		Ph2DogStateChangedDelegate.Invoke(Ph2DogState);
	}
}


