#include "PreCompile.h"
#include "WorldMapCuphead.h"
#include "MovementComponent.h"
#include "WorldMapCharacterAnimationControllerComponent.h"
#include "ItemInventory.h"
#include "CharacterScore.h"
#include "NewsCat.h"
#include "WorldMapLevel.h"

WorldMapCuphead::WorldMapCuphead()
	: Movement(nullptr)
	, Animation(nullptr)
	, WalkCheckInterval(0.03f)
	, WalkCheckElapsedTime(0.0f)
	, InventoryOn(false)
	, SoundOnceCheckA(false)
	, SoundOnceCheckB(false)
{
}

WorldMapCuphead::~WorldMapCuphead()
{
}

void WorldMapCuphead::Start()
{
	{
		// 애니메이션
		Renderer = CreateComponent<GameEngineTextureRenderer>();
		SetRenderer(Renderer);

		// Idle
		Renderer->CreateFrameAnimationFolder("WorldMapCupheadIdleDiagDown", FrameAnimation_DESC("WorldMapChupheadIdleDiagDown", 0.05f));
		Renderer->CreateFrameAnimationFolder("WorldMapCupheadIdleDiagUp", FrameAnimation_DESC("WorldMapChupheadIdleDiagUp", 0.05f));
		Renderer->CreateFrameAnimationFolder("WorldMapCupheadIdleDown", FrameAnimation_DESC("WorldMapChupheadIdleDown", 0.05f));
		Renderer->CreateFrameAnimationFolder("WorldMapCupheadIdleDownB", FrameAnimation_DESC("WorldMapChupheadIdleDownB", 0.05f)); // Idle 상태로 지속 시 1번 발동
		Renderer->CreateFrameAnimationFolder("WorldMapCupheadIdleSide", FrameAnimation_DESC("WorldMapChupheadIdleSide", 0.05f));
		Renderer->CreateFrameAnimationFolder("WorldMapCupheadIdleSideB", FrameAnimation_DESC("WorldMapChupheadIdleSideB", 0.05f)); // Idle 상태로 지속 시 1번 발동
		Renderer->CreateFrameAnimationFolder("WorldMapCupheadIdleUp", FrameAnimation_DESC("WorldMapChupheadIdleUp", 0.05f));

		// Walk
		Renderer->CreateFrameAnimationFolder("WorldMapCupheadWalkDiagDown", FrameAnimation_DESC("WorldMapChupheadWalkDiagDown", 0.05f));
		Renderer->CreateFrameAnimationFolder("WorldMapCupheadWalkDiagUp", FrameAnimation_DESC("WorldMapChupheadWalkDiagUp", 0.05f));
		Renderer->CreateFrameAnimationFolder("WorldMapCupheadWalkDown", FrameAnimation_DESC("WorldMapChupheadWalkDown", 0.05f));
		Renderer->CreateFrameAnimationFolder("WorldMapCupheadWalkSide", FrameAnimation_DESC("WorldMapChupheadWalkSide", 0.05f));
		Renderer->CreateFrameAnimationFolder("WorldMapCupheadWalkUp", FrameAnimation_DESC("WorldMapChupheadWalkUp", 0.05f));

		// Win
		Renderer->CreateFrameAnimationFolder("WorldMapCupheadWin", FrameAnimation_DESC("WorldMapCupheadWin", 0.05f));

		Renderer->AnimationBindFrame("WorldMapCupheadWin", std::bind(&WorldMapCuphead::OnWorldMapCupheadWinAnimationFrameChanged, this, std::placeholders::_1));

		SetState(WorldMapCharacterState::Idle);
		Renderer->ChangeFrameAnimation("WorldMapCupheadIdleDown");
		Renderer->SetScaleModeImage();
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
		Collision->GetTransform().SetLocalScale({ 80.0f, 80.0f, 1.0f });
		Collision->GetTransform().SetLocalPosition({ 0.0f, 40.0f, 1.0f });
		Collision->ChangeOrder(ObjectOrder::PC);
	}

	{
		// 컴포넌트
		Movement = CreateComponent<MovementComponent>();
		Animation = CreateComponent<WorldMapCharacterAnimationControllerComponent>();
		Animation->SetCharacterName("Cuphead");
	}

	//DustRenderer = CreateComponent<GameEngineTextureRenderer>();
	//DustRenderer->
}

void WorldMapCuphead::Win()
{
	SetState(WorldMapCharacterState::Win);
}

void WorldMapCuphead::Update(float _DeltaTime)
{
	std::list<GameEngineActor*> Actors = GetLevel()->GetGroup(GameObjectGroup::CharacterScore);
	for (GameEngineActor* Actor : Actors)
	{
		if (CharacterScore* _Score = dynamic_cast<CharacterScore*>(Actor))
		{
			Score = _Score;
		}
	}

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
		SoundOnceCheckA = false;
		if (false == SoundOnceCheckB)
		{
			GameEngineSound::SoundPlayOneShot("sfx_WorldMap_LevelSelect_BubbleAppear.wav");
			SoundOnceCheckB = true;
		}
	}

	Collision->IsCollision(CollisionType::CT_AABB2D, ObjectOrder::NPC, CollisionType::CT_AABB2D,
		std::bind(&WorldMapCuphead::CanPortalCollision, this, std::placeholders::_1, std::placeholders::_2));


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
	else if (Score != nullptr && true == Score->Win)
	{
		if (WorldMapLevel* Level = dynamic_cast<WorldMapLevel*>(GetLevel()))
		{
			Level->Win();
		}
		Win();
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

CollisionReturn WorldMapCuphead::CanPortalCollision(GameEngineCollision* _This, GameEngineCollision* _Other)
{
	if (false == SoundOnceCheckA)
	{
		GameEngineSound::SoundPlayOneShot("sfx_WorldMap_LevelSelect_BubbleAppear.wav");
		SoundOnceCheckA = true;
		SoundOnceCheckB = false;
	}	

	EnterRenderer->On();

	if (NewsCat* Cat = dynamic_cast<NewsCat*>(_Other->GetParent()))
	{
		if (Cat->GetState() == NewsCatState::Talk)
		{
			EnterRenderer->Off();
		}
	}

	return CollisionReturn::Break;
}

void WorldMapCuphead::OnWorldMapCupheadWinAnimationFrameChanged(const FrameAnimation_DESC& _Info)
{
	if (_Info.CurFrame == 23)
	{
		Idle();
		if (WorldMapLevel* Level = dynamic_cast<WorldMapLevel*>(GetLevel()))
		{
			Level->GivePineApple();
		}
		Score->Win = false;
	}
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