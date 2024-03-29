#include "PreCompile.h"
#include "WorldMapMugman.h"
#include "MovementComponent.h"
#include "WorldMapCharacterAnimationControllerComponent.h"

WorldMapMugman::WorldMapMugman()
	: Movement(nullptr)
	, Animation(nullptr)
	, WalkCheckInterval(0.1f)
	, WalkCheckElapsedTime(0.0f)
{

}

WorldMapMugman::~WorldMapMugman()
{
}

void WorldMapMugman::Start()
{
	GameEngineTextureRenderer* Renderer = CreateComponent<GameEngineTextureRenderer>();
	SetRenderer(Renderer);

	// Idle
	Renderer->CreateFrameAnimationFolder("WorldMapMugmanIdleDiagDown", FrameAnimation_DESC("WorldMapMugmanIdleDiagDown", 0.1f));
	Renderer->CreateFrameAnimationFolder("WorldMapMugmanIdleDiagUp", FrameAnimation_DESC("WorldMapMugmanIdleDiagUp", 0.1f));
	Renderer->CreateFrameAnimationFolder("WorldMapMugmanIdleDown", FrameAnimation_DESC("WorldMapMugmanIdleDown", 0.1f));
	Renderer->CreateFrameAnimationFolder("WorldMapMugmanIdleDownB", FrameAnimation_DESC("WorldMapMugmanIdleDownB", 0.1f)); // Idle 상태로 지속 시 1번 발동
	Renderer->CreateFrameAnimationFolder("WorldMapMugmanIdleSide", FrameAnimation_DESC("WorldMapMugmanIdleSide", 0.1f));
	Renderer->CreateFrameAnimationFolder("WorldMapMugmanIdleSideB", FrameAnimation_DESC("WorldMapMugmanIdleSideB", 0.1f)); // Idle 상태로 지속 시 1번 발동
	Renderer->CreateFrameAnimationFolder("WorldMapMugmanIdleUp", FrameAnimation_DESC("WorldMapMugmanIdleUp", 0.1f));

	// Walk
	Renderer->CreateFrameAnimationFolder("WorldMapMugmanWalkDiagDown", FrameAnimation_DESC("WorldMapMugmanWalkDiagDown", 0.1f));
	Renderer->CreateFrameAnimationFolder("WorldMapMugmanWalkDiagUp", FrameAnimation_DESC("WorldMapMugmanWalkDiagUp", 0.1f));
	Renderer->CreateFrameAnimationFolder("WorldMapMugmanWalkDown", FrameAnimation_DESC("WorldMapMugmanWalkDown", 0.1f));
	Renderer->CreateFrameAnimationFolder("WorldMapMugmanWalkSide", FrameAnimation_DESC("WorldMapMugmanWalkSide", 0.1f));
	Renderer->CreateFrameAnimationFolder("WorldMapMugmanWalkUp", FrameAnimation_DESC("WorldMapMugmanWalkUp", 0.1f));

	// Win
	Renderer->CreateFrameAnimationFolder("WorldMapMugmanWin", FrameAnimation_DESC("WorldMapMugmanWin", 0.1f));

	SetState(WorldMapCharacterState::Idle);
	Renderer->ChangeFrameAnimation("WorldMapMugmanIdleDown");
	Renderer->ScaleToTexture();
	Renderer->SetPivot(PIVOTMODE::BOT);

	// EnterRenderer
	EnterRenderer = CreateComponent<GameEngineTextureRenderer>();
	EnterRenderer->SetTexture("BBox.png");
	EnterRenderer->ScaleToTexture();
	EnterRenderer->GetTransform().SetLocalPosition({ 0.0f, 110.0f });
	EnterRenderer->Off();

	{
		// 충돌
		Collision = CreateComponent<GameEngineCollision>();
		SetCollision(Collision);
		Collision->SetParent(this);
		Collision->GetTransform().SetLocalScale({ 100.0f, 100.0f, 1.0f });
		Collision->ChangeOrder(ObjectOrder::PC);
	}

	Movement = CreateComponent<MovementComponent>();
	Animation = CreateComponent<WorldMapCharacterAnimationControllerComponent>();
	Animation->SetCharacterName("Mugman");
}

void WorldMapMugman::Update(float _DeltaTime)
{
	GetLevel()->GetMainCameraActorTransform().SetLocalPosition({ GetTransform().GetLocalPosition().x + 6.0f, GetTransform().GetLocalPosition().y - 32 });

	EnterRenderer->Off();

	Collision->IsCollision(CollisionType::CT_AABB2D, ObjectOrder::NPC, CollisionType::CT_AABB2D,
		std::bind(&WorldMapMugman::CanPortalCollision, this, std::placeholders::_1, std::placeholders::_2));

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

CollisionReturn WorldMapMugman::CanPortalCollision(GameEngineCollision* _This, GameEngineCollision* _Other)
{
	EnterRenderer->On();

	return CollisionReturn::ContinueCheck;
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