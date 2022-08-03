#include "PreCompile.h"
#include "InGameCharacterMovementCompmonent.h"
#include "IngameCuphead.h"
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
	, JumpHeight(150)
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

	CurrentColor = ColMapTexture->GetPixel(Transform.ix(), -Transform.iy());

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
		InGameCharacter->GetState() != InGameCharacterState::Walk)
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

	InGameCharacterState State = InGameCharacter->GetState();

	if (State == InGameCharacterState::Jump)
	{
		JumpHeight -= 5;
		float4 Dir = JumpHeight > -250 ? float4::UP : float4::DOWN;
		
		HorizontalDir = InGameCharacter->GetHorizontalDirection();

		if (HorizontalDir == "Left")
		{
			Dir += float4::LEFT;
		}
		else if (HorizontalDir == "Right")
		{
			Dir += float4::RIGHT;
		}
		else
		{
			Dir += float4::ZERO;
		}

		InGameCharacter->GetTransform().SetWorldMove(Dir * 200 * _DeltaTime);
	}

	else
	{
		JumpHeight = 150;

		if (true == CanMoveAreaCheck()) // 흰색에 있고
		{
			if (true == IsOnGround()) // 아래가 검은색일때
			{
				if (State == InGameCharacterState::Dash)
				{
					float4 Dir = InGameCharacter->GetRenderer()->GetTransform().GetLocalScale().x < 0 ? float4::LEFT : float4::RIGHT;
					float DashSpeed = Speed;
					InGameCharacter->GetTransform().SetWorldMove(Dir * DashSpeed * _DeltaTime);
				}

				else
				{
					InGameCharacter->GetTransform().SetWorldMove(Direction * Speed * _DeltaTime);
				}
			}

			else
			{
				Gravity = 3.0f;
				DownDir.y -= Gravity;
				InGameCharacter->GetTransform().SetWorldMove(DownDir * _DeltaTime);
			}
		}

		else
		{
			while (true == CurrentColor.CompareInt4D(float4::BLACK))
			{
				InGameCharacter->GetTransform().SetWorldMove(float4::UP * _DeltaTime);
			}
		}
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

