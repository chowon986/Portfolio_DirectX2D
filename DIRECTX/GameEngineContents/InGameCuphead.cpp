#include "PreCompile.h"
#include "InGameCuphead.h"
#include "InGameCharacterAnimationControllerComponent.h"
#include "InGameCharacterMovementCompmonent.h"

InGameCuphead::InGameCuphead()
{
}

InGameCuphead::~InGameCuphead()
{
}

void InGameCuphead::Start()
{
	if (false == GameEngineInput::GetInst()->IsKey("Aim"))
	{
		GameEngineInput::GetInst()->CreateKey("Aim", 'A');
	}

	GameEngineTextureRenderer* Renderer = CreateComponent<GameEngineTextureRenderer>();
	SetRenderer(Renderer);

	// Aim
	Renderer->CreateFrameAnimationFolder("IngameCupheadAimDiagDown", FrameAnimation_DESC("IngameCupheadAimDiagDown", 0.1f));
	Renderer->CreateFrameAnimationFolder("IngameCupheadAimDiagUp", FrameAnimation_DESC("IngameCupheadAimDiagUp", 0.1f));
	Renderer->CreateFrameAnimationFolder("IngameCupheadAimDown", FrameAnimation_DESC("IngameCupheadAimDown", 0.1f));
	Renderer->CreateFrameAnimationFolder("IngameCupheadAimStraight", FrameAnimation_DESC("IngameCupheadAimStraight", 0.1f));
	Renderer->CreateFrameAnimationFolder("IngameCupheadAimUp", FrameAnimation_DESC("IngameCupheadAimUp", 0.1f));

	// Dash
	Renderer->CreateFrameAnimationFolder("IngameCupheadDashGround", FrameAnimation_DESC("IngameCupheadDashGround", 0.1f));
	Renderer->CreateFrameAnimationFolder("IngameCupheadDashAir", FrameAnimation_DESC("IngameCupheadDashAir", 0.1f));

	// Intro
	Renderer->CreateFrameAnimationFolder("IngameCupheadIntro", FrameAnimation_DESC("IngameCupheadIntro", 0.1f));

	// Jump
	Renderer->CreateFrameAnimationFolder("IngameCupheadJump", FrameAnimation_DESC("IngameCupheadJump", 0.1f));

	// Parry
	Renderer->CreateFrameAnimationFolder("IngameCupheadParryHand", FrameAnimation_DESC("IngameCupheadParryHand", 0.1f));

	// Run
	Renderer->CreateFrameAnimationFolder("IngameCupheadRun", FrameAnimation_DESC("IngameCupheadRun", 0.1f));

	// Shoot
	Renderer->CreateFrameAnimationFolder("IngameCupheadRunShooting", FrameAnimation_DESC("IngameCupheadRunShooting", 0.1f));
	Renderer->CreateFrameAnimationFolder("IngameCupheadShootDiagDown", FrameAnimation_DESC("IngameCupheadShootDiagDown", 0.1f));
	Renderer->CreateFrameAnimationFolder("IngameCupheadShootDiagUp", FrameAnimation_DESC("IngameCupheadShootDiagUp", 0.1f));
	Renderer->CreateFrameAnimationFolder("IngameCupheadShootDown", FrameAnimation_DESC("IngameCupheadShootDown", 0.1f));
	Renderer->CreateFrameAnimationFolder("IngameCupheadShootStraight", FrameAnimation_DESC("IngameCupheadShootStraight", 0.1f));
	Renderer->CreateFrameAnimationFolder("IngameCupheadShootUp", FrameAnimation_DESC("IngameCupheadShootUp", 0.1f));

	// TakeDamage
	Renderer->CreateFrameAnimationFolder("IngameCupheadTakeDamageAir", FrameAnimation_DESC("IngameCupheadTakeDamageAir", 0.1f));
	Renderer->CreateFrameAnimationFolder("IngameCupheadTakeDamageGround", FrameAnimation_DESC("IngameCupheadTakeDamageGround", 0.1f));

	// Idle
	Renderer->CreateFrameAnimationFolder("IngameCupheadIdle", FrameAnimation_DESC("IngameCupheadIdle", 0.1f));
	Renderer->CreateFrameAnimationFolder("IngameCupheadIdleDownStart", FrameAnimation_DESC("InGameCupheadIdleDownStart", 0, 7, 0.1f, true));
	Renderer->CreateFrameAnimationFolder("IngameCupheadIdleDown", FrameAnimation_DESC("IngameCupheadIdleDown", 0, 3, 0.1f, true));
	Renderer->CreateFrameAnimationFolder("IngameCupheadIdleDownTurn", FrameAnimation_DESC("InGameCupheadIdleDownTurn", 0, 0, 0.1f, true));

	SetState(InGameCharacterState::Idle);
	Renderer->ChangeFrameAnimation("IngameCupheadIdle");
	Renderer->ScaleToTexture();
	Renderer->SetPivot(PIVOTMODE::BOT);

	Movement = CreateComponent<InGameCharacterMovementCompmonent>();
	Animation = CreateComponent<InGameCharacterAnimationControllerComponent>();
	Animation->SetCharacterName("Cuphead");
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

	if (true == GameEngineInput::GetInst()->IsPress("MoveLeft"))
	{
		SetHorizontalDirection("Left");
	}
	else if (true == GameEngineInput::GetInst()->IsPress("MoveRight"))
	{
		SetHorizontalDirection("Right");
	}
	else
	{
		SetHorizontalDirection("Center");
	}

	
	if (true == GameEngineInput::GetInst()->IsPress("MoveUp"))
	{
		SetVerticalDirection("Up");
	}
	else if (true == GameEngineInput::GetInst()->IsPress("MoveDown"))
	{
		SetVerticalDirection("Down");
	}
	else
	{
		SetVerticalDirection("Center");
	}

	if (true == GameEngineInput::GetInst()->IsPress("Aim"))
	{
		Aim();
	}
	else if (true == GameEngineInput::GetInst()->IsPress("MoveLeft") ||
		true == GameEngineInput::GetInst()->IsPress("MoveRight"))
	{
		Walk();
	}
	else if (true == GameEngineInput::GetInst()->IsPress("MoveDown"))
	{
		Duck();
	}
	else
	{
		Idle();
	}
}

void InGameCuphead::Walk()
{
	SetState(InGameCharacterState::Walk);
}

void InGameCuphead::Idle()
{
	SetState(InGameCharacterState::Idle);
}

void InGameCuphead::Aim()
{
	SetState(InGameCharacterState::Aim);
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
	SetState(InGameCharacterState::Duck);
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

