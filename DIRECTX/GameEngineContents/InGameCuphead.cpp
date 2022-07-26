#include "PreCompile.h"
#include "InGameCuphead.h"

InGameCuphead::InGameCuphead()
{
}

InGameCuphead::~InGameCuphead()
{
}

void InGameCuphead::Start()
{
	//if (false == GameEngineInput::GetInst()->IsKey("Dash"))
	//{
	//	// 키 생성 만들기
	//}

	GameEngineTextureRenderer* Renderer = CreateComponent<GameEngineTextureRenderer>();

	// Idle
	Renderer->CreateFrameAnimationFolder("InGameCupheadIdleDiagDown", FrameAnimation_DESC("InGameCupheadIdleDiagDown", 0.1f));
	Renderer->CreateFrameAnimationFolder("InGameCupheadIdleDiagUp", FrameAnimation_DESC("InGameCupheadIdleDiagUp", 0.1f));
	Renderer->CreateFrameAnimationFolder("InGameCupheadIdleDown", FrameAnimation_DESC("InGameCupheadIdleDown", 0.1f));
	Renderer->CreateFrameAnimationFolder("InGameCupheadIdleSide", FrameAnimation_DESC("InGameCupheadIdleSide", 0.1f));
	Renderer->CreateFrameAnimationFolder("InGameCupheadIdleUp", FrameAnimation_DESC("InGameCupheadIdleUp", 0.1f));
										  
	// Walk								  
	Renderer->CreateFrameAnimationFolder("InGameCupheadWalkDiagDown", FrameAnimation_DESC("WorldMapChupheadWalkDiagDown", 0.1f));
	Renderer->CreateFrameAnimationFolder("InGameCupheadWalkDiagUp", FrameAnimation_DESC("WorldMapChupheadWalkDiagUp", 0.1f));
	Renderer->CreateFrameAnimationFolder("InGameCupheadWalkDown", FrameAnimation_DESC("WorldMapChupheadWalkDown", 0.1f));
	Renderer->CreateFrameAnimationFolder("InGameCupheadWalkSide", FrameAnimation_DESC("WorldMapChupheadWalkSide", 0.1f));
	Renderer->CreateFrameAnimationFolder("InGameCupheadWalkUp", FrameAnimation_DESC("WorldMapChupheadWalkUp", 0.1f));

	// Win
	Renderer->CreateFrameAnimationFolder("WorldMapCupheadWin", FrameAnimation_DESC("WorldMapCupheadWin", 0.1f));

	SetState(InGameCharacterState::Idle);
	Renderer->ChangeFrameAnimation("WorldMapCupheadIdleDown");
	Renderer->ScaleToTexture();
	Renderer->SetPivot(PIVOTMODE::BOT);
}

void InGameCuphead::Update(float _DeltaTime)
{
	// 키보드로 가능한 애들
	//Aim
	//Dash
	//Duck
	//Jumpable
	//Parriable
	//Runable
	//Shootable
	//SpecialAttackable
	//SuperIAttackable
	//SuperIIAttackable
	//SuperIIIAttackable
	//Walkable
	
	// 불가능한 애들
	//TakeDamage
	//Die
	//Preparable
	//Idleable

	GetLevel()->GetMainCameraActorTransform().SetLocalPosition({ GetTransform().GetLocalPosition().x, GetTransform().GetLocalPosition().y });

	if (true == GameEngineInput::GetInst()->IsPress("MoveLeft") ||
		true == GameEngineInput::GetInst()->IsPress("MoveRight"))
	{
		Walk();
	}
	else
	{
		Idle();
	}
}

void InGameCuphead::Walk()
{
	//WalkCheckElapsedTime += GameEngineTime::GetDeltaTime();
	//if (WalkCheckElapsedTime > WalkCheckInterval)
	//{
	//	WalkCheckElapsedTime = 0;
	//}

	//if (WalkCheckElapsedTime == 0)
	//{
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
	//}

	SetState(InGameCharacterState::Walk);
}

void InGameCuphead::Idle()
{
	SetState(InGameCharacterState::Idle);
}

void InGameCuphead::Aim()
{
}

void InGameCuphead::TakeDamage()
{
}

void InGameCuphead::Dash()
{
}

void InGameCuphead::Die()
{
}

void InGameCuphead::Duck()
{
}

void InGameCuphead::Jump()
{
}

void InGameCuphead::Parry()
{
}

void InGameCuphead::Prepare()
{
}

void InGameCuphead::Run()
{
}

void InGameCuphead::Shoot()
{
}

void InGameCuphead::SpecialAttack()
{
}

void InGameCuphead::SuperIAttack()
{
}

void InGameCuphead::SuperIIAttack()
{
}

void InGameCuphead::SuperIIIAttack()
{
}

