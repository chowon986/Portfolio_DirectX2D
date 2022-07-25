#include "PreCompile.h"
#include "IWorldMapCharacterBase.h"

IWorldMapCharacterBase::IWorldMapCharacterBase()
	: Renderer(nullptr)
	, State(WorldMapCupheadState::Idle)
	, Dir("Down")
{
}

IWorldMapCharacterBase::~IWorldMapCharacterBase()
{
}

void IWorldMapCharacterBase::SetState(WorldMapCupheadState _State)
{
	if (State != _State)
	{
		State = _State;
		StateChangedDelegate.Invoke(State);
	}
}

WorldMapCupheadState IWorldMapCharacterBase::GetState()
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
