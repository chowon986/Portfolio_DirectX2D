#include "PreCompile.h"
#include "IInGameCharacterBase.h"

IInGameCharacterBase::IInGameCharacterBase()
	: State(InGameCharacterState::Idle)
	, Renderer(nullptr)
	, VerticalDir("Center")
	, HorizontalDir("Right")
{
}

IInGameCharacterBase::~IInGameCharacterBase()
{
}

void IInGameCharacterBase::SetState(InGameCharacterState _State)
{
	if (State != _State)
	{
		State = _State;
		StateChangedDelegate.Invoke(State);
	}
}

void IInGameCharacterBase::SetVerticalDirection(std::string _Dir)
{
	if (VerticalDir != _Dir)
	{
		VerticalDir = _Dir;
		VerticalDirectionChangedDelegate.Invoke(VerticalDir);
	}
}

void IInGameCharacterBase::SetHorizontalDirection(std::string _Dir)
{
	if (HorizontalDir != _Dir)
	{
		HorizontalDir = _Dir;
		HorizontalDirectionChangedDelegate.Invoke(HorizontalDir);
	}
}

void IInGameCharacterBase::SetRenderer(GameEngineTextureRenderer* _Renderer)
{
	Renderer = _Renderer;
}

