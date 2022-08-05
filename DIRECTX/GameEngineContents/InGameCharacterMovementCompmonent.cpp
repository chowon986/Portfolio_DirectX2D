#include "PreCompile.h"
#include "InGameCharacterMovementCompmonent.h"
#include "IngameCuphead.h"
#include "PhysicsComponent.h"
#include <functional>

InGameCharacterMovementCompmonent::InGameCharacterMovementCompmonent()
	: Direction(float4::ZERO)
	, Speed(400)
	, RightColor(0.0f)
	, RightUpColor(0.0f)
	, RightDownColor(0.0f)
	, LeftColor(0.0f)
	, LeftUpColor(0.0f)
	, LeftDownColor(0.0f)
	, UpColor(0.0f)
	, DownColor(0.0f)
	, CurrentColor(0.0f)
	, DropSpeed(0.0f)
	, Gravity(0.0f)
	, DownDir(float4::DOWN)
	, JumpHeight(50)
	, IsSetZero(false)
{
}

InGameCharacterMovementCompmonent::~InGameCharacterMovementCompmonent()
{
}

bool InGameCharacterMovementCompmonent::CanMoveAreaCheck()
{
	Transform = InGameCharacter->GetTransform().GetWorldPosition();

	ColMapImage = InGameCharacter->GetColMapImage();
	ColMapTexture = ColMapImage->GetCurTexture();
	if (nullptr == ColMapTexture)
	{
		MsgBoxAssert("콜맵이 존재하지 않습니다.");
	}

	RightColor = ColMapTexture->GetPixel(Transform.ix() + 10, -Transform.iy());
	RightUpColor = ColMapTexture->GetPixel(Transform.ix() + 10, -(Transform.iy() + 10));
	RightDownColor = ColMapTexture->GetPixel(Transform.ix() + 10, -(Transform.iy() - 10));

	LeftColor = ColMapTexture->GetPixel(Transform.ix() - 10, -Transform.iy());
	LeftUpColor = ColMapTexture->GetPixel(Transform.ix() - 10, -(Transform.iy() + 10));
	LeftDownColor = ColMapTexture->GetPixel(Transform.ix() - 10, -(Transform.iy() - 10));

	UpColor = ColMapTexture->GetPixel(Transform.ix(), -(Transform.iy() + 10));
	DownColor = ColMapTexture->GetPixel(Transform.ix(), -(Transform.iy() - 10));

	CurrentColor = ColMapTexture->GetPixel(Transform.x, -Transform.y);

	std::string HorizontalDirectionDir = InGameCharacter->GetHorizontalDirection();
	std::string VerticalDirectionDir = InGameCharacter->GetVerticalDirection();

	if (true == CurrentColor.CompareInt4D(float4::WHITE)) // 현재 움직일 수 있는 땅이고
	{
		if (HorizontalDirectionDir == "Left") 
		{
			if (true == LeftColor.CompareInt4D(float4::WHITE))
			{
				return true;
			}
			else false;
		}

		else if (HorizontalDirectionDir == "Right")
		{
			if (true == RightColor.CompareInt4D(float4::WHITE))
			{
				return true;
			}
			else false;
		}

		else
		{
			if (true == LeftColor.CompareInt4D(float4::WHITE))
			{
				return true;
			}

			else if (true == RightColor.CompareInt4D(float4::WHITE))
			{
				return true;
			}

			else
			{
				return false;
			}
		}
	}
	else
	{
		return false;
	}
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
		InGameCharacter->GetState() == InGameCharacterState::Idle)
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
	ColMapImage = InGameCharacter->GetColMapImage();
	ColMapTexture = ColMapImage->GetCurTexture();
	if (ColMapTexture == nullptr)
	{
		return;
	}
	
	while (true == ColMapTexture->GetPixel(InGameCharacter->GetTransform().GetWorldPosition().x, -InGameCharacter->GetTransform().GetWorldPosition().y).CompareInt4D(float4::BLACK))
	{
		if (State != InGameCharacterState::Jump)
		{
			Physics->SetZero();
		}

		InGameCharacter->GetTransform().SetWorldMove(float4::UP * _DeltaTime);
	}

	if (State == InGameCharacterState::Jump)
	{
		if (IsSetZero == false)
		{
			Physics->Reset();
			IsSetZero = true;
		}
		//InGameCharacter->GetTransform().SetWorldMove({ Direction * Speed * _DeltaTime });
		InGameCharacter->GetTransform().SetWorldMove({ Direction.x * 100 * _DeltaTime, -Physics->GetSpeed(), 0});
	}

	else if (State == InGameCharacterState::Dash)
	{
		if (Physics->GetGravity() != -0.98f)
		{
			Physics->Reset();
		}

		float4 Dir = InGameCharacter->GetRenderer()->GetTransform().GetLocalScale().x < 0 ? float4::LEFT : float4::RIGHT;
		float DashSpeed = Speed;
		InGameCharacter->GetTransform().SetWorldMove(Dir * DashSpeed * _DeltaTime);
	}

	else
	{
		JumpHeight = 50.0f;
		IsSetZero = false;
		if (Physics->GetGravity() != -0.98f)
		{
			Physics->Reset();
		}
		InGameCharacter->GetTransform().SetWorldMove(Direction * Speed * _DeltaTime);
	}
}

bool InGameCharacterMovementCompmonent::IsOnGround()
{
	if (DownColor.CompareInt4D(float4::BLACK))
	{
		return true;
	}
	return false;
}


void InGameCharacterMovementCompmonent::End()
{
}

