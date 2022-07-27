#include "PreCompile.h"
#include "WorldMapCuphead.h"
#include "MovementComponent.h"
#include "WorldMapCharacterAnimationControllerComponent.h"

WorldMapCuphead::WorldMapCuphead()
	: Movement(nullptr)
	, Animation(nullptr)
	, WalkCheckInterval(0.05)
	, WalkCheckElapsedTime(0)
{

}

WorldMapCuphead::~WorldMapCuphead()
{
}

void WorldMapCuphead::Start()
{
	if (false == GameEngineInput::GetInst()->IsKey("MoveLeft"))
	{
		GameEngineInput::GetInst()->CreateKey("MoveLeft", VK_LEFT);
		GameEngineInput::GetInst()->CreateKey("MoveRight", VK_RIGHT);
	}

	GameEngineTextureRenderer* Renderer = CreateComponent<GameEngineTextureRenderer>();
	SetRenderer(Renderer);

	// Idle
	Renderer->CreateFrameAnimationFolder("WorldMapCupheadIdleDiagDown", FrameAnimation_DESC("WorldMapChupheadIdleDiagDown", 0.1f));
	Renderer->CreateFrameAnimationFolder("WorldMapCupheadIdleDiagUp", FrameAnimation_DESC("WorldMapChupheadIdleDiagUp", 0.1f));
	Renderer->CreateFrameAnimationFolder("WorldMapCupheadIdleDown", FrameAnimation_DESC("WorldMapChupheadIdleDown", 0.1f));
	Renderer->CreateFrameAnimationFolder("WorldMapCupheadIdleDownB", FrameAnimation_DESC("WorldMapChupheadIdleDownB", 0.1f)); // Idle ���·� ���� �� 1�� �ߵ�
	Renderer->CreateFrameAnimationFolder("WorldMapCupheadIdleSide", FrameAnimation_DESC("WorldMapChupheadIdleSide", 0.1f));
	Renderer->CreateFrameAnimationFolder("WorldMapCupheadIdleSideB", FrameAnimation_DESC("WorldMapChupheadIdleSideB", 0.1f)); // Idle ���·� ���� �� 1�� �ߵ�
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

	Movement = CreateComponent<MovementComponent>();
	Animation = CreateComponent<WorldMapCharacterAnimationControllerComponent>();
	Animation->SetCharacterName("Cuphead");
}

void WorldMapCuphead::Update(float _DeltaTime)
{
	GetLevel()->GetMainCameraActorTransform().SetLocalPosition({ GetTransform().GetLocalPosition().x+6.0f, GetTransform().GetLocalPosition().y - 32});

	GroundCheck();
}

void WorldMapCuphead::Idle()
{
	SetState(WorldMapCharacterState::Idle);
	WalkCheckElapsedTime = 0;
}

void WorldMapCuphead::GroundCheck()
{
	GameEngineTexture* ColMapTexture = GetColMapImage()->GetCurTexture();
	if (nullptr == ColMapTexture)
	{
		MsgBoxAssert("�ݸ��� �������� �ʽ��ϴ�.");
	}

	float4 Color = ColMapTexture->GetPixel(GetTransform().GetWorldPosition().ix(), -GetTransform().GetWorldPosition().iy());
	float4 Black = { 0.0f, 0.0f, 0.0f, 1.0f };
	float4 White = { 1.0f, 1.0f, 1.0f, 1.0f };

	float4 RightColor = ColMapTexture->GetPixel(GetTransform().GetWorldPosition().ix() + 5, GetTransform().GetWorldPosition().iy());
	float4 LeftColor = ColMapTexture->GetPixel(GetTransform().GetWorldPosition().ix() - 5, GetTransform().GetWorldPosition().iy());
	float4 DownColor = ColMapTexture->GetPixel(GetTransform().GetWorldPosition().ix(), GetTransform().GetWorldPosition().iy() - 1);
	float4 UpColor = ColMapTexture->GetPixel(GetTransform().GetWorldPosition().ix(), GetTransform().GetWorldPosition().iy() + 1);

	//while (true == RightColor.CompareInt4D(White))// ||
	//	/*true == LeftColor.CompareInt4D(White) ||
	//	true == DownColor.CompareInt4D(White) ||
	//	true == UpColor.CompareInt4D(White))*/
	//{

	//}

	if (true == Color.CompareInt4D(Black))
	{
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