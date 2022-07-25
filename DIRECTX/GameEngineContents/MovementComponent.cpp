#include "PreCompile.h"
#include "MovementComponent.h"
#include "WorldMapCuphead.h"
#include <functional>

MovementComponent::MovementComponent()
	: Direction(float4::ZERO)
	, Speed(200)
{
}

MovementComponent::~MovementComponent()
{
}

void MovementComponent::OnStateChanged(WorldMapCupheadState _State)
{
	UpdateDirection();
}

void MovementComponent::OnDirectionChanged(std::string _Dir)
{
	UpdateDirection();
}

void MovementComponent::UpdateDirection()
{
	IWorldMapCharacterBase* WorldMapCharacter = GetParent<IWorldMapCharacterBase>();
	if (WorldMapCharacter == nullptr ||
		WorldMapCharacter->GetState() != WorldMapCupheadState::Walk)
	{
		Direction = float4::ZERO;
		return;
	}

	std::string Dir = WorldMapCharacter->GetDirection();

	if (Dir == "Left")
	{
		Direction = float4::LEFT;
	}
	else if (Dir == "LeftUp")
	{
		Direction = float4::LEFT + float4::UP;
	}
	else if (Dir == "LeftDown")
	{
		Direction = float4::LEFT + float4::DOWN;
	}
	else if (Dir == "Right")
	{
		Direction = float4::RIGHT;
	}
	else if (Dir == "RightUp")
	{
		Direction = float4::RIGHT + float4::UP;
	}
	else if (Dir == "RightDown")
	{
		Direction = float4::RIGHT + float4::DOWN;
	}
	else if (Dir == "Up")
	{
		Direction = float4::UP;
	}
	else if (Dir == "Down")
	{
		Direction = float4::DOWN;
	}
	else
	{
		Direction = float4::ZERO;
	}
}

void MovementComponent::Start()
{
	Direction = float4::ZERO;

	IWorldMapCharacterBase* WorldMapCharacter = GetParent<IWorldMapCharacterBase>();
	if (WorldMapCharacter != nullptr)
	{
		WorldMapCharacter->GetStateChangedDelegate().Add(std::bind(&MovementComponent::OnStateChanged, this, std::placeholders::_1));
		WorldMapCharacter->GetDirectionChangedDelegate().Add(std::bind(&MovementComponent::OnDirectionChanged, this, std::placeholders::_1));
	}
}

void MovementComponent::Update(float _DeltaTime)
{
	GameEngineActor* Actor = GetParent<GameEngineActor>();
	if (Actor == nullptr)
	{
		return;
	}

	Actor->GetTransform().SetWorldMove(Direction * Speed * _DeltaTime);
}

void MovementComponent::End()
{
}
