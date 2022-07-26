#include "PreCompile.h"
#include "WorldMapMugman.h"
#include "MovementComponent.h"
#include "WorldMapCharacterAnimationControllerComponent.h"

WorldMapMugman::WorldMapMugman()
	: Movement(nullptr)
	, Animation(nullptr)
	, WalkCheckInterval(0.1)
	, WalkCheckElapsedTime(0)
{

}

WorldMapMugman::~WorldMapMugman()
{
}

void WorldMapMugman::Start()
{
	if (false == GameEngineInput::GetInst()->IsKey("MoveLeft"))
	{
		GameEngineInput::GetInst()->CreateKey("MoveLeft", VK_LEFT);
		GameEngineInput::GetInst()->CreateKey("MoveRight", VK_RIGHT);
	}

	GameEngineTextureRenderer* Renderer = CreateComponent<GameEngineTextureRenderer>();
	SetRenderer(Renderer);

	// Idle
	Renderer->CreateFrameAnimationFolder("WorldMapMugmanIdleDiagDown", FrameAnimation_DESC("WorldMapChupheadIdleDiagDown", 0.1f));
	Renderer->CreateFrameAnimationFolder("WorldMapMugmanIdleDiagUp", FrameAnimation_DESC("WorldMapChupheadIdleDiagUp", 0.1f));
	Renderer->CreateFrameAnimationFolder("WorldMapMugmanIdleDown", FrameAnimation_DESC("WorldMapChupheadIdleDown", 0.1f));
	Renderer->CreateFrameAnimationFolder("WorldMapMugmanIdleDownB", FrameAnimation_DESC("WorldMapChupheadIdleDownB", 0.1f)); // Idle 상태로 지속 시 1번 발동
	Renderer->CreateFrameAnimationFolder("WorldMapMugmanIdleSide", FrameAnimation_DESC("WorldMapChupheadIdleSide", 0.1f));
	Renderer->CreateFrameAnimationFolder("WorldMapMugmanIdleSideB", FrameAnimation_DESC("WorldMapChupheadIdleSideB", 0.1f)); // Idle 상태로 지속 시 1번 발동
	Renderer->CreateFrameAnimationFolder("WorldMapMugmanIdleUp", FrameAnimation_DESC("WorldMapChupheadIdleUp", 0.1f));

	// Walk
	Renderer->CreateFrameAnimationFolder("WorldMapMugmanWalkDiagDown", FrameAnimation_DESC("WorldMapChupheadWalkDiagDown", 0.1f));
	Renderer->CreateFrameAnimationFolder("WorldMapMugmanWalkDiagUp", FrameAnimation_DESC("WorldMapChupheadWalkDiagUp", 0.1f));
	Renderer->CreateFrameAnimationFolder("WorldMapMugmanWalkDown", FrameAnimation_DESC("WorldMapChupheadWalkDown", 0.1f));
	Renderer->CreateFrameAnimationFolder("WorldMapMugmanWalkSide", FrameAnimation_DESC("WorldMapChupheadWalkSide", 0.1f));
	Renderer->CreateFrameAnimationFolder("WorldMapMugmanWalkUp", FrameAnimation_DESC("WorldMapChupheadWalkUp", 0.1f));

	// Win
	Renderer->CreateFrameAnimationFolder("WorldMapMugmanWin", FrameAnimation_DESC("WorldMapMugmanWin", 0.1f));

	SetState(WorldMapCharacterState::Idle);
	Renderer->ChangeFrameAnimation("WorldMapMugmanIdleDown");
	Renderer->ScaleToTexture();
	Renderer->SetPivot(PIVOTMODE::BOT);

	Movement = CreateComponent<MovementComponent>();
	Animation = CreateComponent<WorldMapCharacterAnimationControllerComponent>();
	Animation->SetCharacterName("Mugman");
}

void WorldMapMugman::Update(float _DeltaTime)
{
	GetLevel()->GetMainCameraActorTransform().SetLocalPosition({ GetTransform().GetLocalPosition().x + 6.0f, GetTransform().GetLocalPosition().y - 32 });

	if (true == GameEngineInput::GetInst()->IsPress("MoveLeft") ||
		true == GameEngineInput::GetInst()->IsPress("MoveRight") ||
		true == GameEngineInput::GetInst()->IsPress("MoveDown") ||
		true == GameEngineInput::GetInst()->IsPress("MoveUp"))
	{
		Walk();
	}
	else
	{
		Idle();
	}
}

void WorldMapMugman::Idle()
{
	SetState(WorldMapCharacterState::Idle);
	WalkCheckElapsedTime = 0;
}


void WorldMapMugman::Walk()
{
	WalkCheckElapsedTime += GameEngineTime::GetDeltaTime();
	if (WalkCheckElapsedTime > WalkCheckInterval)
	{
		WalkCheckElapsedTime = 0;
	}

	if (WalkCheckElapsedTime == 0)
	{
		if (true == GameEngineInput::GetInst()->IsPress("MoveLeft"))
		{
			if (true == GameEngineInput::GetInst()->IsPress("MoveUp"))
			{
				SetDirection("LeftUp");
			}
			else if (true == GameEngineInput::GetInst()->IsPress("MoveDown"))
			{
				SetDirection("LeftDown");
			}
			else
			{
				SetDirection("Left");
			}
		}
		else if (true == GameEngineInput::GetInst()->IsPress("MoveRight"))
		{
			if (true == GameEngineInput::GetInst()->IsPress("MoveUp"))
			{
				SetDirection("RightUp");
			}
			else if (true == GameEngineInput::GetInst()->IsPress("MoveDown"))
			{
				SetDirection("RightDown");
			}
			else
			{
				SetDirection("Right");
			}
		}
		else if (true == GameEngineInput::GetInst()->IsPress("MoveDown"))
		{
			SetDirection("Down");
		}
		else if (true == GameEngineInput::GetInst()->IsPress("MoveUp"))
		{
			SetDirection("Up");
		}
	}

	SetState(WorldMapCharacterState::Walk);
}