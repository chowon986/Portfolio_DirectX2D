#include "PreCompile.h"
#include "InGameCharacterMovementCompmonent.h"
#include "IngameCuphead.h"
#include "PhysicsComponent.h"
#include <functional>

InGameCharacterMovementCompmonent::InGameCharacterMovementCompmonent()
	: Direction(float4::ZERO)
	, Speed(400)
	, DownDir(float4::DOWN)
	, IsOnGround(false)
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
	if (InGameCharacter == nullptr ||
		InGameCharacter->GetState() == InGameCharacterState::Idle ||
		InGameCharacter->GetState() == InGameCharacterState::Aim ||
		InGameCharacter->GetState() == InGameCharacterState::TakeDamage)
	{
		Direction = float4::ZERO;
		return;
	}

	VerticalDir = InGameCharacter->GetVerticalDirection();
	HorizontalDir = InGameCharacter->GetHorizontalDirection();

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

	InGameCharacter = GetParent<IInGameCharacterBase>();
	if (InGameCharacter != nullptr)
	{
		InGameCharacter->GetStateChangedDelegate().Add(std::bind(&InGameCharacterMovementCompmonent::OnStateChanged, this, std::placeholders::_1));
		InGameCharacter->GetVerticalDirectionChangedDelegate().Add(std::bind(&InGameCharacterMovementCompmonent::OnDirectionChanged, this, std::placeholders::_1));
		InGameCharacter->GetHorizontalDirectionChangedDelegate().Add(std::bind(&InGameCharacterMovementCompmonent::OnDirectionChanged, this, std::placeholders::_1));
	}
}

void InGameCharacterMovementCompmonent::Update(float _DeltaTime)
{
	if (InGameCharacter == nullptr)
	{
		return;
	}

	PhysicsComponent* Physics = InGameCharacter->GetPhysicsComponent();
	if (Physics == nullptr)
	{
		return;
	}

	InGameCharacterState State = InGameCharacter->GetState();

	if (State == InGameCharacterState::Dash)
	{
		Physics->Reset();

		float4 Dir = InGameCharacter->GetRenderer()->GetTransform().GetLocalScale().x < 0 ? float4::LEFT : float4::RIGHT;
		float DashSpeed = Speed;
		InGameCharacter->GetTransform().SetWorldMove(Dir * DashSpeed * _DeltaTime);
	}

	else
	{
		InGameCharacter->GetTransform().SetWorldMove(Direction * Speed * _DeltaTime);
	}
}

void InGameCharacterMovementCompmonent::End()
{
}

