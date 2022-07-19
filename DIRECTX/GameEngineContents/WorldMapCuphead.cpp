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
	//Renderer->CreateFrameAnimationFolder("DiagDown", FrameAnimation_DESC("DiagDown", 0.1f));
	Renderer->CreateFrameAnimationFolder("DownA", FrameAnimation_DESC("DownA", 0.1f));
	//Renderer->CreateFrameAnimationFolder("DownA", FrameAnimation_DESC("DownA", 0.1f));
	//Renderer->CreateFrameAnimationFolder("DownA", FrameAnimation_DESC("DownA", 0.1f));
	Renderer->ChangeFrameAnimation("DownA");
	Renderer->GetTransform().SetLocalScale({ 53 ,99,100 });
}

void WorldMapCuphead::Update(float _DeltaTime)
{
	GetLevel()->GetMainCameraActorTransform().SetLocalPosition(GetTransform().GetLocalPosition());

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
	//if (Dir == "Right")
	//{
	//	Renderer->ChangeFrameAnimation()
	//}
}


void WorldMapCuphead::Walk()
{
	if (true == GameEngineInput::GetInst()->IsPress("MoveLeft"))
	{
		GetTransform().SetWorldMove(GetTransform().GetLeftVector() * Speed * GameEngineTime::GetDeltaTime());
	}

	if (true == GameEngineInput::GetInst()->IsPress("MoveRight"))
	{
		GetTransform().SetWorldMove(GetTransform().GetRightVector() * Speed * GameEngineTime::GetDeltaTime());
	}

	if (true == GameEngineInput::GetInst()->IsPress("MoveDown"))
	{
		GetTransform().SetWorldMove(GetTransform().GetDownVector() * Speed * GameEngineTime::GetDeltaTime());
	}

	if (true == GameEngineInput::GetInst()->IsPress("MoveUp"))
	{
		GetTransform().SetWorldMove(GetTransform().GetUpVector() * Speed * GameEngineTime::GetDeltaTime());
	}
}