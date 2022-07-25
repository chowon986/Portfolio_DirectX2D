#include "PreCompile.h"
#include "WorldMapCharacterAnimationControllerComponent.h"
#include "WorldMapCuphead.h"

WorldMapCharacterAnimationControllerComponent::WorldMapCharacterAnimationControllerComponent()
{
}

WorldMapCharacterAnimationControllerComponent::~WorldMapCharacterAnimationControllerComponent()
{
}

void WorldMapCharacterAnimationControllerComponent::OnStateChanged(WorldMapCupheadState _State)
{
	UpdateAnimation();
}


void WorldMapCharacterAnimationControllerComponent::OnDirectionChanged(std::string _Dir)
{
	UpdateAnimation();
}

void WorldMapCharacterAnimationControllerComponent::UpdateAnimation()
{
	IWorldMapCharacterBase* WorldMapCharacter = GetParent<IWorldMapCharacterBase>();
	if (WorldMapCharacter == nullptr)
	{
		return;
	}
	GameEngineTextureRenderer* Renderer = WorldMapCharacter->GetRenderer();
	WorldMapCupheadState State = WorldMapCharacter->GetState();
	std::string Dir = WorldMapCharacter->GetDirection();

	if (State == WorldMapCupheadState::Idle)
	{
		if (Dir == "RightUp")
		{
			Renderer->ChangeFrameAnimation("WorldMapCupheadIdleDiagUp");
			Renderer->ScaleToTexture();

		}
		else if (Dir == "RightDown")
		{
			Renderer->ChangeFrameAnimation("WorldMapCupheadIdleDiagDown");
			Renderer->ScaleToTexture();

		}
		else if (Dir == "Right")
		{
			Renderer->ChangeFrameAnimation("WorldMapCupheadIdleSide");
			Renderer->ScaleToTexture();
		}

		else if (Dir == "LeftUp")
		{
			Renderer->ChangeFrameAnimation("WorldMapCupheadIdleDiagUp");
			Renderer->ScaleToTexture();
			if (Renderer->GetTransform().GetLocalScale().x > 0)
			{
				float x = Renderer->GetTransform().GetLocalScale().x * -1;
				Renderer->GetTransform().SetLocalScale({ x,Renderer->GetTransform().GetLocalScale().y, Renderer->GetTransform().GetLocalScale().z });
			}

		}
		else if (Dir == "LeftDown")
		{
			Renderer->ChangeFrameAnimation("WorldMapCupheadIdleDiagDown");
			Renderer->ScaleToTexture();
			if (Renderer->GetTransform().GetLocalScale().x > 0)
			{
				float x = Renderer->GetTransform().GetLocalScale().x * -1;
				Renderer->GetTransform().SetLocalScale({ x,Renderer->GetTransform().GetLocalScale().y, Renderer->GetTransform().GetLocalScale().z });
			}

		}
		else if (Dir == "Left")
		{
			Renderer->ChangeFrameAnimation("WorldMapCupheadIdleSide");
			Renderer->ScaleToTexture();
			if (Renderer->GetTransform().GetLocalScale().x > 0)
			{
				float x = Renderer->GetTransform().GetLocalScale().x * -1;
				Renderer->GetTransform().SetLocalScale({ x,Renderer->GetTransform().GetLocalScale().y, Renderer->GetTransform().GetLocalScale().z });
			}
		}
		else if (Dir == "Up")
		{
			Renderer->ChangeFrameAnimation("WorldMapCupheadIdleUp");
			Renderer->ScaleToTexture();

		}
		else if (Dir == "Down")
		{
			Renderer->ChangeFrameAnimation("WorldMapCupheadIdleDown");
			Renderer->ScaleToTexture();
		}
	}

	else if (State == WorldMapCupheadState::Walk)
	{
		if (Dir == "Right")
		{
			Renderer->ChangeFrameAnimation("WorldMapCupheadWalkSide");
			Renderer->ScaleToTexture();

		}
		else if (Dir == "RightUp")
		{
			Renderer->ChangeFrameAnimation("WorldMapCupheadWalkDiagUp");
			Renderer->ScaleToTexture();
		}
		else if (Dir == "RightDown")
		{
			Renderer->ChangeFrameAnimation("WorldMapCupheadWalkDiagDown");
			Renderer->ScaleToTexture();
		}
		else if (Dir == "Left")
		{
			Renderer->ChangeFrameAnimation("WorldMapCupheadWalkSide");
			Renderer->ScaleToTexture();
			if (Renderer->GetTransform().GetLocalScale().x > 0)
			{
				float x = Renderer->GetTransform().GetLocalScale().x * -1;
				Renderer->GetTransform().SetLocalScale({ x,Renderer->GetTransform().GetLocalScale().y, Renderer->GetTransform().GetLocalScale().z });
			}

		}
		else if (Dir == "LeftUp")
		{
			Renderer->ChangeFrameAnimation("WorldMapCupheadWalkDiagUp");
			Renderer->ScaleToTexture();
			if (Renderer->GetTransform().GetLocalScale().x > 0)
			{
				float x = Renderer->GetTransform().GetLocalScale().x * -1;
				Renderer->GetTransform().SetLocalScale({ x,Renderer->GetTransform().GetLocalScale().y, Renderer->GetTransform().GetLocalScale().z });
			}

		}
		else if (Dir == "LeftDown")
		{
			Renderer->ChangeFrameAnimation("WorldMapCupheadWalkDiagDown");
			Renderer->ScaleToTexture();
			if (Renderer->GetTransform().GetLocalScale().x > 0)
			{
				float x = Renderer->GetTransform().GetLocalScale().x * -1;
				Renderer->GetTransform().SetLocalScale({ x,Renderer->GetTransform().GetLocalScale().y, Renderer->GetTransform().GetLocalScale().z });
			}

		}
		else if (Dir == "Up")
		{
			Renderer->ChangeFrameAnimation("WorldMapCupheadWalkUp");
			Renderer->ScaleToTexture();

		}
		else if (Dir == "Down")
		{
			Renderer->ChangeFrameAnimation("WorldMapCupheadWalkDown");
			Renderer->ScaleToTexture();
		}
	}
}

void WorldMapCharacterAnimationControllerComponent::Start()
{
	IWorldMapCharacterBase* WorldMapCharacter = GetParent<IWorldMapCharacterBase>();
	if (WorldMapCharacter != nullptr)
	{

		WorldMapCharacter->GetStateChangedDelegate().Add(std::bind(&WorldMapCharacterAnimationControllerComponent::OnStateChanged, this, std::placeholders::_1));
		WorldMapCharacter->GetDirectionChangedDelegate().Add(std::bind(&WorldMapCharacterAnimationControllerComponent::OnDirectionChanged, this, std::placeholders::_1));
	}
}

void WorldMapCharacterAnimationControllerComponent::Update(float _DeltaTime)
{
	GameEngineActor* Actor = GetParent<GameEngineActor>();
	if (Actor == nullptr)
	{
		return;
	}
}

void WorldMapCharacterAnimationControllerComponent::End()
{
}
