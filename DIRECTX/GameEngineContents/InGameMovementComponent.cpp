#include "PreCompile.h"
#include "InGameMovementComponent.h"

InGameMovementComponent::InGameMovementComponent()
	:Speed(0.0f)
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

void InGameMovementComponent::Move(float4 _StartPos, float4 _EndPos)
{
	StartPos = _StartPos;
	EndPos = _EndPos;

	Direction = EndPos - StartPos;
	Direction.Normalize();
}

void InGameMovementComponent::Start()
{
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

	Actor->GetTransform().SetWorldMove(Direction * Speed * _DeltaTime);
}

void InGameMovementComponent::End()
{
}
