#include "PreCompile.h"
#include "IWorldMapCharacterBase.h"

IWorldMapCharacterBase::IWorldMapCharacterBase()
	: Renderer(nullptr)
	, State(WorldMapCharacterState::Idle)
	, Dir("Down")
{
}

IWorldMapCharacterBase::~IWorldMapCharacterBase()
{
}

void IWorldMapCharacterBase::SetState(WorldMapCharacterState _State)
{
	if (State != _State)
	{
		State = _State;
		StateChangedDelegate.Invoke(State);
	}
}

WorldMapCharacterState IWorldMapCharacterBase::GetState()
{
	return State;
}

void IWorldMapCharacterBase::SetDirection(std::string _Dir)
{
	if (Dir != _Dir)
	{
		Dir = _Dir;
		DirectionChangedDelegate.Invoke(Dir);
	}
}

void IWorldMapCharacterBase::SetRenderer(GameEngineTextureRenderer* _Renderer)
{
	Renderer = _Renderer;
}
