#include "PreCompile.h"
#include "WorldMapCuphead.h"
#include "MovementComponent.h"
#include "WorldMapCharacterAnimationControllerComponent.h"
#include "ItemInventory.h"

WorldMapCuphead::WorldMapCuphead()
	: Movement(nullptr)
	, Animation(nullptr)
	, WalkCheckInterval(0.03)
	, WalkCheckElapsedTime(0)
	, InventoryOn(false)
{
}

WorldMapCuphead::~WorldMapCuphead()
{
}

void WorldMapCuphead::Start()
{

	{
		// 키보드 생성
		if (false == GameEngineInput::GetInst()->IsKey("MoveLeft"))
		{
			GameEngineInput::GetInst()->CreateKey("MoveLeft", VK_LEFT);
			GameEngineInput::GetInst()->CreateKey("MoveRight", VK_RIGHT);
			GameEngineInput::GetInst()->CreateKey("Enter", 'B');
		}

	}

	{
		// 애니메이션
		GameEngineTextureRenderer* Renderer = CreateComponent<GameEngineTextureRenderer>();
		SetRenderer(Renderer);

		// Idle
		Renderer->CreateFrameAnimationFolder("WorldMapCupheadIdleDiagDown", FrameAnimation_DESC("WorldMapChupheadIdleDiagDown", 0.1f));
		Renderer->CreateFrameAnimationFolder("WorldMapCupheadIdleDiagUp", FrameAnimation_DESC("WorldMapChupheadIdleDiagUp", 0.1f));
		Renderer->CreateFrameAnimationFolder("WorldMapCupheadIdleDown", FrameAnimation_DESC("WorldMapChupheadIdleDown", 0.1f));
		Renderer->CreateFrameAnimationFolder("WorldMapCupheadIdleDownB", FrameAnimation_DESC("WorldMapChupheadIdleDownB", 0.1f)); // Idle 상태로 지속 시 1번 발동
		Renderer->CreateFrameAnimationFolder("WorldMapCupheadIdleSide", FrameAnimation_DESC("WorldMapChupheadIdleSide", 0.1f));
		Renderer->CreateFrameAnimationFolder("WorldMapCupheadIdleSideB", FrameAnimation_DESC("WorldMapChupheadIdleSideB", 0.1f)); // Idle 상태로 지속 시 1번 발동
		Renderer->CreateFrameAnimationFolder("WorldMapCupheadIdleUp", FrameAnimation_DESC("WorldMapChupheadIdleUp", 0.1f));

		// Walk
		Renderer->CreateFrameAnimationFolder("WorldMapCupheadWalkDiagDown", FrameAnimation_DESC("WorldMapChupheadWalkDiagDown", 0.1f));
		Renderer->CreateFrameAnimationFolder("WorldMapCupheadWalkDiagUp", FrameAnimation_DESC("WorldMapChupheadWalkDiagUp", 0.1f));
		Renderer->CreateFrameAnimationFolder("WorldMapCupheadWalkDown", FrameAnimation_DESC("WorldMapChupheadWalkDown", 0.1f));
		Renderer->CreateFrameAnimationFolder("WorldMapCupheadWalkSide", FrameAnimation_DESC("WorldMapChupheadWalkSide", 0.1f));
		Renderer->CreateFrameAnimationFolder("WorldMapCupheadWalkUp", FrameAnimation_DESC("WorldMapChupheadWalkUp", 0.1f));

		// Win
		Renderer->CreateFrameAnimationFolder("WorldMapCupheadWin", FrameAnimation_DESC("WorldMapCupheadWin", 0.1f));

		SetState(WorldMapCharacterState::Idle);
		Renderer->ChangeFrameAnimation("WorldMapCupheadIdleDown");
		Renderer->ScaleToTexture();
		Renderer->SetPivot(PIVOTMODE::BOT);

		// EnterRenderer
		EnterRenderer = CreateComponent<GameEngineTextureRenderer>();
		EnterRenderer->SetTexture("BBox.png");
		EnterRenderer->ScaleToTexture();
		EnterRenderer->GetTransform().SetLocalPosition({ 0.0f, 110.0f });
		EnterRenderer->Off();
	}

	{
		// 충돌
		Collision = CreateComponent<GameEngineCollision>();
		SetCollision(Collision);
		Collision->GetTransform().SetLocalScale({ 100.0f, 100.0f, 1.0f });
		Collision->ChangeOrder(ObjectOrder::PC);
	}

	{
		// 컴포넌트
		Movement = CreateComponent<MovementComponent>();
		Animation = CreateComponent<WorldMapCharacterAnimationControllerComponent>();
		Animation->SetCharacterName("Cuphead");
	}
}

void WorldMapCuphead::Update(float _DeltaTime)
{
	if (Inventory->IsUpdate())
	{
		InventoryOn = true;
	}
	else
	{
		InventoryOn = false;
	}

	GetLevel()->GetMainCameraActorTransform().SetLocalPosition({ GetTransform().GetLocalPosition().x + 6.0f, GetTransform().GetLocalPosition().y - 32 });

	if (false == Collision->IsCollision(CollisionType::CT_AABB2D, ObjectOrder::NPC, CollisionType::CT_AABB2D,
		std::bind(&WorldMapCuphead::CanPortalCollision, this, std::placeholders::_1, std::placeholders::_2)))
	{
		EnterRenderer->Off();
	}
	else
	{
		EnterRenderer->On();
	}

	if (true == GameEngineInput::GetInst()->IsPress("MoveLeft") ||
		true == GameEngineInput::GetInst()->IsPress("MoveRight") ||
		true == GameEngineInput::GetInst()->IsPress("MoveDown") ||
		true == GameEngineInput::GetInst()->IsPress("MoveUp"))
	{
		if (InventoryOn == false)
		{
		Walk();
		}
	}
	else
	{
		Idle();
	}
}

void WorldMapCuphead::Idle()
{
	SetState(WorldMapCharacterState::Idle);
	WalkCheckElapsedTime = 0;
}

bool WorldMapCuphead::CanPortalCollision(GameEngineCollision* _This, GameEngineCollision* _Other)
{
	return true;
}

void WorldMapCuphead::Walk()
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