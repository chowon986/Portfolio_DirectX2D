#include "PreCompile.h"
#include "InGameCharacterMovementCompmonent.h"
#include "IngameCuphead.h"
#include <functional>

InGameCharacterMovementCompmonent::InGameCharacterMovementCompmonent()
	: Direction(float4::ZERO)
	, Speed(400)
	, DashSpeed(1)
{
}

InGameCharacterMovementCompmonent::~InGameCharacterMovementCompmonent()
{
}

void InGameCharacterMovementCompmonent::OnStateChanged(InGameCharacterState _State)
{
	UpdateDirection();
}

void InGameCharacterMovementCompmonent::OnDirectionChanged(std::string _Dir)
{
	UpdateDirection();
}

void InGameCharacterMovementCompmonent::UpdateDirection()
{
	IInGameCharacterBase* InGameCharacter = GetParent<IInGameCharacterBase>();
	if (InGameCharacter == nullptr &&
		InGameCharacter->GetState() != InGameCharacterState::Walk &&
		InGameCharacter->GetState() != InGameCharacterState::Dash)
	{
			Direction = float4::ZERO;
			return;
	}

	std::string VerticalDir = InGameCharacter->GetVerticalDirection();
	std::string HorizontalDir = InGameCharacter->GetHorizontalDirection();

	if (HorizontalDir == "Left")
	{
		Direction = float4::LEFT;
	}
	else if (HorizontalDir == "Right")
	{
		Direction = float4::RIGHT;
	}
	else
	{
		Direction = float4::ZERO;
	}
}

void InGameCharacterMovementCompmonent::Start()
{
	Direction = float4::ZERO;

	IInGameCharacterBase* InGameCharacter = GetParent<IInGameCharacterBase>();
	if (InGameCharacter != nullptr)
	{
		InGameCharacter->GetStateChangedDelegate().Add(std::bind(&InGameCharacterMovementCompmonent::OnStateChanged, this, std::placeholders::_1));
		InGameCharacter->GetVerticalDirectionChangedDelegate().Add(std::bind(&InGameCharacterMovementCompmonent::OnDirectionChanged, this, std::placeholders::_1));
		InGameCharacter->GetHorizontalDirectionChangedDelegate().Add(std::bind(&InGameCharacterMovementCompmonent::OnDirectionChanged, this, std::placeholders::_1));
	}
}

void InGameCharacterMovementCompmonent::Update(float _DeltaTime)
{
	GameEngineActor* Actor = GetParent<GameEngineActor>();
	if (Actor == nullptr)
	{
		return;
	}

	IInGameCharacterBase* InGameCharacter = GetParent<IInGameCharacterBase>();
	if (InGameCharacter == nullptr &&
		InGameCharacter->GetState() != InGameCharacterState::Dash)
	{
		DashSpeed = 2;
	}
	else
	{
		DashSpeed = 1;
	}
	Actor->GetTransform().SetWorldMove(Direction * Speed * _DeltaTime * DashSpeed);
}

void InGameCharacterMovementCompmonent::End()
{
}

