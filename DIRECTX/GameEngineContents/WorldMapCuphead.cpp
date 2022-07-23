#include "PreCompile.h"
#include "WorldMapCuphead.h"

WorldMapCuphead::WorldMapCuphead()
	: Renderer(nullptr)
	, Speed(200)
{

}

WorldMapCuphead::~WorldMapCuphead()
{
}

void WorldMapCuphead::SetState(WorldMapCupheadState _State)
{
	State = _State;
}

WorldMapCupheadState WorldMapCuphead::GetState()
{
	return State;
}

void WorldMapCuphead::Start()
{
	if (false == GameEngineInput::GetInst()->IsKey("MoveLeft"))
	{
		GameEngineInput::GetInst()->CreateKey("MoveLeft", VK_LEFT);
		GameEngineInput::GetInst()->CreateKey("MoveRight", VK_RIGHT);
	}

	Renderer = CreateComponent<GameEngineTextureRenderer>();
	Renderer->CreateFrameAnimationFolder("DiagDown", FrameAnimation_DESC("WorldMapChupheadWalkDiagDown", 0.1f));
	Renderer->CreateFrameAnimationFolder("DiagUp", FrameAnimation_DESC("WorldMapChupheadWalkDiagUp", 0.1f));
	Renderer->CreateFrameAnimationFolder("Down", FrameAnimation_DESC("WorldMapChupheadIdleDown", 0.1f));
	Renderer->CreateFrameAnimationFolder("WalkDown", FrameAnimation_DESC("WorldMapChupheadWalkDown", 0.05f));
	Renderer->CreateFrameAnimationFolder("WalkSide", FrameAnimation_DESC("WorldMapChupheadWalkSide", 0.05f));
	Renderer->CreateFrameAnimationFolder("WalkUp", FrameAnimation_DESC("WorldMapChupheadWalkUp", 0.05f));
	Renderer->ChangeFrameAnimation("Down");
	Renderer->ScaleToTexture();
	SetState(WorldMapCupheadState::Idle);
	Dir = "Down";
}

void WorldMapCuphead::Update(float _DeltaTime)
{
	
	GetLevel()->GetMainCameraActorTransform().SetLocalPosition({ GetTransform().GetLocalPosition().x+6.0f, GetTransform().GetLocalPosition().y - 32});

	if (true == GameEngineInput::GetInst()->IsPress("MoveLeft") ||
		true == GameEngineInput::GetInst()->IsPress("MoveRight") ||
		true == GameEngineInput::GetInst()->IsPress("MoveDown") ||
		true == GameEngineInput::GetInst()->IsPress("MoveUp"))
	{
		SetState(WorldMapCupheadState::Walk);
	}
	else
	{
		SetState(WorldMapCupheadState::Idle);
	}


	switch (State)
	{
	case WorldMapCupheadState::Idle:
		Idle();
		break;
	case WorldMapCupheadState::Walk:
		Walk();
		break;
	}

}

void WorldMapCuphead::Idle()
{
	if (Dir == "Right")
	{
		Renderer->ChangeFrameAnimation("Side");
	}
	else if(Dir == "Left")
	{
		Renderer->ChangeFrameAnimation("WalkSide");
		Renderer->GetTransform().SetLocalScale({ -53 ,99,100 });
	}
	else if (Dir == "Up")
	{
		Renderer->ChangeFrameAnimation("Up");
	}
	else if (Dir == "Down")
	{
		Renderer->ChangeFrameAnimation("Down");
	}
}


void WorldMapCuphead::Walk()
{
	if (true == GameEngineInput::GetInst()->IsPress("MoveLeft"))
	{
		Renderer->ChangeFrameAnimation("WalkSide");
		if (Renderer->GetTransform().GetLocalScale().x > 0)
		{
			Renderer->GetTransform().SetLocalScale({ -66,85,100 });
		}
		GetTransform().SetWorldMove(GetTransform().GetLeftVector() * Speed * GameEngineTime::GetDeltaTime());
	}

	if (true == GameEngineInput::GetInst()->IsPress("MoveRight"))
	{
		Renderer->ChangeFrameAnimation("WalkSide");
		if (Renderer->GetTransform().GetLocalScale().x < 0)
		{
			Renderer->GetTransform().SetLocalScale({ 66,85,100 });
		}
		GetTransform().SetWorldMove(GetTransform().GetRightVector() * Speed * GameEngineTime::GetDeltaTime());
	}

	if (true == GameEngineInput::GetInst()->IsPress("MoveDown"))
	{
		Renderer->ChangeFrameAnimation("WalkDown");
		Renderer->GetTransform().SetLocalScale({ 66,85,100 });

		GetTransform().SetWorldMove(GetTransform().GetDownVector() * Speed * GameEngineTime::GetDeltaTime());
	}

	if (true == GameEngineInput::GetInst()->IsPress("MoveUp"))
	{
		Renderer->ChangeFrameAnimation("WalkUp");
		Renderer->GetTransform().SetLocalScale({ 66,85,100 });

		GetTransform().SetWorldMove(GetTransform().GetUpVector() * Speed * GameEngineTime::GetDeltaTime());
	}
}