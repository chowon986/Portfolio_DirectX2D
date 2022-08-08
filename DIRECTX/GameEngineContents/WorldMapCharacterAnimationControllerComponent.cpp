#include "PreCompile.h"
#include "WorldMapCharacterAnimationControllerComponent.h"
#include "WorldMapCuphead.h"

WorldMapCharacterAnimationControllerComponent::WorldMapCharacterAnimationControllerComponent()
{
}

WorldMapCharacterAnimationControllerComponent::~WorldMapCharacterAnimationControllerComponent()
{
}

void WorldMapCharacterAnimationControllerComponent::OnStateChanged(WorldMapCharacterState _State)
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
	WorldMapCharacterState State = WorldMapCharacter->GetState();
	std::string Dir = WorldMapCharacter->GetDirection();
	std::string Name = GetCharacterName();

	if (State == WorldMapCharacterState::Idle)
	{
		if (Dir == "RightUp")
		{
			Renderer->ChangeFrameAnimation("WorldMap"+ Name + "IdleDiagUp");
			Renderer->ScaleToTexture();

		}
		else if (Dir == "RightDown")
		{
			Renderer->ChangeFrameAnimation("WorldMap"+ Name+"IdleDiagDown");
			Renderer->ScaleToTexture();

		}
		else if (Dir == "Right")
		{
			Renderer->ChangeFrameAnimation("WorldMap" + Name + "IdleSide");
			Renderer->ScaleToTexture();
		}

		else if (Dir == "LeftUp")
		{
			Renderer->ChangeFrameAnimation("WorldMap" + Name + "IdleDiagUp");
			Renderer->ScaleToTexture();
			if (Renderer->GetTransform().GetLocalScale().x > 0)
			{
				float x = Renderer->GetTransform().GetLocalScale().x * -1;
				Renderer->GetTransform().SetLocalScale({ x,Renderer->GetTransform().GetLocalScale().y, Renderer->GetTransform().GetLocalScale().z });
			}

		}
		else if (Dir == "LeftDown")
		{
			Renderer->ChangeFrameAnimation("WorldMap" + Name + "IdleDiagDown");
			Renderer->ScaleToTexture();
			if (Renderer->GetTransform().GetLocalScale().x > 0)
			{
				float x = Renderer->GetTransform().GetLocalScale().x * -1;
				Renderer->GetTransform().SetLocalScale({ x,Renderer->GetTransform().GetLocalScale().y, Renderer->GetTransform().GetLocalScale().z });
			}

		}
		else if (Dir == "Left")
		{
			Renderer->ChangeFrameAnimation("WorldMap" + Name + "IdleSide");
			Renderer->ScaleToTexture();
			if (Renderer->GetTransform().GetLocalScale().x > 0)
			{
				float x = Renderer->GetTransform().GetLocalScale().x * -1;
				Renderer->GetTransform().SetLocalScale({ x,Renderer->GetTransform().GetLocalScale().y, Renderer->GetTransform().GetLocalScale().z });
			}
		}
		else if (Dir == "Up")
		{
			Renderer->ChangeFrameAnimation("WorldMap" + Name + "IdleUp");
			Renderer->ScaleToTexture();

		}
		else if (Dir == "Down")
		{
			Renderer->ChangeFrameAnimation("WorldMap" + Name + "IdleDown");
			Renderer->ScaleToTexture();
		}
	}

	else if (State == WorldMapCharacterState::Walk)
	{
		if (Dir == "Right")
		{
			Renderer->ChangeFrameAnimation("WorldMap" + Name + "WalkSide");
			Renderer->ScaleToTexture();
			Renderer->GetTransform().PixLocalPositiveX();
		}
		else if (Dir == "RightUp")
		{
			Renderer->ChangeFrameAnimation("WorldMap" + Name + "WalkDiagUp");
			Renderer->ScaleToTexture();
			Renderer->GetTransform().PixLocalPositiveX();

		}
		else if (Dir == "RightDown")
		{
			Renderer->ChangeFrameAnimation("WorldMap" + Name + "WalkDiagDown");
			Renderer->ScaleToTexture();
			Renderer->GetTransform().PixLocalPositiveX();

		}
		else if (Dir == "Left")
		{
			Renderer->ChangeFrameAnimation("WorldMap" + Name + "WalkSide");
			Renderer->ScaleToTexture();
			Renderer->GetTransform().PixLocalNegativeX();

		}
		else if (Dir == "LeftUp")
		{
			Renderer->ChangeFrameAnimation("WorldMap" + Name + "WalkDiagUp");
			Renderer->ScaleToTexture();
			Renderer->GetTransform().PixLocalNegativeX();

		}
		else if (Dir == "LeftDown")
		{
			Renderer->ChangeFrameAnimation("WorldMap" + Name + "WalkDiagDown");
			Renderer->ScaleToTexture();
			Renderer->GetTransform().PixLocalNegativeX();

		}
		else if (Dir == "Up")
		{
			Renderer->ChangeFrameAnimation("WorldMap" + Name + "WalkUp");
			Renderer->ScaleToTexture();

		}
		else if (Dir == "Down")
		{
			Renderer->ChangeFrameAnimation("WorldMap" + Name + "WalkDown");
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
