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

void MovementComponent::OnStateChanged(WorldMapCharacterState _State)
{
	UpdateDirection();
}

void MovementComponent::OnDirectionChanged(std::string _Dir)
{
	UpdateDirection();
}

bool MovementComponent::GroundCheck()
{
	IWorldMapCharacterBase* WorldMapCharacter = GetParent<IWorldMapCharacterBase>();
	if (WorldMapCharacter != nullptr)
	{
	ColMapImage = WorldMapCharacter->GetColMapImage();
	}
	GameEngineTexture* ColMapTexture = ColMapImage->GetCurTexture();
	if (nullptr == ColMapTexture)
	{
		MsgBoxAssert("콜맵이 존재하지 않습니다.");
	}

	float4 Transform = WorldMapCharacter->GetTransform().GetWorldPosition();

	float4 Color = ColMapTexture->GetPixel(Transform.ix(), -Transform.iy());

	float4 RightColor = ColMapTexture->GetPixel(Transform.ix() + 10, -Transform.iy());
	float4 RightUpColor = ColMapTexture->GetPixel(Transform.ix() + 10, -(Transform.iy() + 10));
	float4 RightDownColor = ColMapTexture->GetPixel(Transform.ix() + 10, -(Transform.iy() - 10));

	float4 LeftColor = ColMapTexture->GetPixel(Transform.ix() - 10, -Transform.iy());
	float4 LeftUpColor = ColMapTexture->GetPixel(Transform.ix() - 10, -(Transform.iy() +10));
	float4 LeftDownColor = ColMapTexture->GetPixel(Transform.ix() - 10, -(Transform.iy() -10));

	float4 UpColor = ColMapTexture->GetPixel(Transform.ix(), -(Transform.iy() +10));
	float4 DownColor = ColMapTexture->GetPixel(Transform.ix(), -(Transform.iy() - 10));

	std::string Dir = WorldMapCharacter->GetDirection();
	if (true == Color.CompareInt4D(float4::BLACK)) // 현재 움직일 수 있는 땅이고
	{
		if (Dir == "Left") // 왼쪽을 보고 있으며
		{
			if (true != LeftColor.CompareInt4D(float4::BLACK))
			{
				return false;
			}
			else true;

		}
		else if (Dir == "LeftUp")
		{
			if (true != LeftUpColor.CompareInt4D(float4::BLACK))
			{
				return false;
			}
			else true;

		}
		else if (Dir == "LeftDown")
		{
			if (true != LeftDownColor.CompareInt4D(float4::BLACK))
			{
				return false;
			}
			else true;

		}
		else if (Dir == "Right")
		{
			if (true != RightColor.CompareInt4D(float4::BLACK))
			{
				return false;
			}
			else true;

		}
		else if (Dir == "RightUp")
		{
			if (true != RightUpColor.CompareInt4D(float4::BLACK))
			{
				return false;
			}
			else true;

		}
		else if (Dir == "RightDown")
		{
			if (true != RightDownColor.CompareInt4D(float4::BLACK))
			{
				return false;
			}
			else true;

		}
		else if (Dir == "Up")
		{
			if (true != UpColor.CompareInt4D(float4::BLACK))
			{
				return false;
			}
			else true;
		}
		else if (Dir == "Down")
		{
			if (true != DownColor.CompareInt4D(float4::BLACK))
			{
				return false;
			}
			else true;
		}
		else
		{
			return true;
		}
	}
	else
	{
		return false;
	}
}

void MovementComponent::UpdateDirection()
{
	IWorldMapCharacterBase* WorldMapCharacter = GetParent<IWorldMapCharacterBase>();
	if (WorldMapCharacter == nullptr ||
		WorldMapCharacter->GetState() != WorldMapCharacterState::Walk)
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

	if (false != GroundCheck())
	{
		Actor->GetTransform().SetWorldMove(Direction * Speed * _DeltaTime);
		
	}

}

void MovementComponent::End()
{
}
