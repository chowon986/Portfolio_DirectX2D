#include "PreCompile.h"
#include "InGameCuphead.h"
#include "InGameCharacterAnimationControllerComponent.h"
#include "InGameCharacterMovementCompmonent.h"
#include "PeaShooter.h"
#include "SpreadShooter.h"

InGameCuphead::InGameCuphead()
	: IsInputEnabled(false)
	, Animation(nullptr)
	, Movement(nullptr)
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
		GameEngineInput::GetInst()->CreateKey("Shoot", VK_LSHIFT);
		GameEngineInput::GetInst()->CreateKey("Dash", 'Z');
	}

	Renderer = CreateComponent<GameEngineTextureRenderer>();
	SetRenderer(Renderer);

	// Aim (v)
	Renderer->CreateFrameAnimation("IngameCupheadAimDiagDown", FrameAnimation_DESC("Cup.png", 180, 184, 0.1f, true));
	Renderer->CreateFrameAnimation("IngameCupheadAimDiagUp", FrameAnimation_DESC("Cup.png", 186, 190, 0.1f, true));
	Renderer->CreateFrameAnimation("IngameCupheadAimDown", FrameAnimation_DESC("Cup.png", 192, 196, 0.1f, true));
	Renderer->CreateFrameAnimation("IngameCupheadAimStraight", FrameAnimation_DESC("Cup.png", 200, 204, 0.1f, true));
	Renderer->CreateFrameAnimation("IngameCupheadAimUp", FrameAnimation_DESC("Cup.png", 206, 210, 0.1f, true));
	//Renderer->CreateFrameAnimationFolder("IngameCupheadAimDiagDown", FrameAnimation_DESC("IngameCupheadAimDiagDown", 0.1f));
	//Renderer->CreateFrameAnimationFolder("IngameCupheadAimDiagUp", FrameAnimation_DESC("IngameCupheadAimDiagUp", 0.1f));
	//Renderer->CreateFrameAnimationFolder("IngameCupheadAimDown", FrameAnimation_DESC("IngameCupheadAimDown", 0.1f));
	//Renderer->CreateFrameAnimationFolder("IngameCupheadAimStraight", FrameAnimation_DESC("IngameCupheadAimStraight", 0.1f));
	//Renderer->CreateFrameAnimationFolder("IngameCupheadAimUp", FrameAnimation_DESC("IngameCupheadAimUp", 0.1f));

	// Dash
	Renderer->CreateFrameAnimation("IngameCupheadDash", FrameAnimation_DESC("Cup_Dash.png", 0, 7, 0.1f, true));
	Renderer->AnimationBindEnd("IngameCupheadDash", &InGameCuphead::OnDashAnimationEnded, this);

	//Renderer->CreateFrameAnimationFolder("IngameCupheadDash", FrameAnimation_DESC("IngameCupheadDash", 0.05f));

	// Intro (v)
	Renderer->CreateFrameAnimation("IngameCupheadIntro", FrameAnimation_DESC("Cup.png", 220, 247, 0.1f, true));
	Renderer->AnimationBindEnd("IngameCupheadIntro", &InGameCuphead::OnPrepareAnimationEnded, this);
	//Renderer->CreateFrameAnimationFolder("IngameCupheadIntro", FrameAnimation_DESC("IngameCupheadIntro", 0.1f));

	// Jump (v)
	Renderer->CreateFrameAnimation("IngameCupheadJump", FrameAnimation_DESC("Cup.png", 20, 27, 0.1f, true));
	//Renderer->CreateFrameAnimationFolder("IngameCupheadJump", FrameAnimation_DESC("IngameCupheadJump", 0.1f));

	// Parry (v)
	Renderer->CreateFrameAnimation("IngameCupheadParryHand", FrameAnimation_DESC("Cup.png", 120, 127, 0.1f, true));
	//Renderer->CreateFrameAnimationFolder("IngameCupheadParryHand", FrameAnimation_DESC("IngameCupheadParryHand", 0.1f));

	// Run (v)
	//Renderer->CreateFrameAnimationFolder("IngameCupheadRun", FrameAnimation_DESC("IngameCupheadRun", 0.05f));
	Renderer->CreateFrameAnimation("IngameCupheadRun", FrameAnimation_DESC("Cup.png", 40, 55, 0.1f, true));

	// Shoot (v)
	Renderer->CreateFrameAnimation("IngameCupheadRunShootStraight", FrameAnimation_DESC("Cup.png", 60, 75, 0.1f, true));
	Renderer->CreateFrameAnimation("IngameCupheadRunShootDiagUp", FrameAnimation_DESC("Cup.png", 80, 95, 0.1f, true));
	Renderer->CreateFrameAnimation("IngameCupheadShootStraight", FrameAnimation_DESC("Cup.png", 100, 102, 0.1f, true));
	Renderer->CreateFrameAnimation("IngameCupheadShootDiagDown", FrameAnimation_DESC("Cup.png", 104, 106, 0.1f, true));
	Renderer->CreateFrameAnimation("IngameCupheadShootDiagUp", FrameAnimation_DESC("Cup.png", 108, 110, 0.1f, true));
	Renderer->CreateFrameAnimation("IngameCupheadShootDown", FrameAnimation_DESC("Cup.png", 112, 114, 0.1f, true));
	Renderer->CreateFrameAnimation("IngameCupheadShootUp", FrameAnimation_DESC("Cup.png", 116, 118, 0.1f, true));
	Renderer->CreateFrameAnimation("IngameCupheadDuckShoot", FrameAnimation_DESC("Cup.png", 174, 176, 0.1f, true));
	
	//Renderer->CreateFrameAnimationFolder("IngameCupheadShootUp", FrameAnimation_DESC("IngameCupheadShootUp", 0.1f));
	//Renderer->CreateFrameAnimationFolder("IngameCupheadShootDiagUp", FrameAnimation_DESC("IngameCupheadShootDiagUp", 0.1f));
	//Renderer->CreateFrameAnimationFolder("IngameCupheadShootStraight", FrameAnimation_DESC("IngameCupheadShootStraight", 0.1f));
	//Renderer->CreateFrameAnimationFolder("IngameCupheadShootDiagDown", FrameAnimation_DESC("IngameCupheadShootDiagDown", 0.1f));
	//Renderer->CreateFrameAnimationFolder("IngameCupheadShootDown", FrameAnimation_DESC("IngameCupheadShootDown", 0.1f));
	//Renderer->CreateFrameAnimationFolder("IngameCupheadRunShootStraight", FrameAnimation_DESC("IngameCupheadRunShootStraight", 0.1f));
	//Renderer->CreateFrameAnimationFolder("IngameCupheadRunShootDiagUp", FrameAnimation_DESC("IngameCupheadRunShootDiagUp", 0.1f));
	//Renderer->CreateFrameAnimationFolder("IngameCupheadDuckShoot", FrameAnimation_DESC("IngameCupheadDuckShoot", 0.1f));

	// TakeDamage (v)
	Renderer->CreateFrameAnimation("IngameCupheadTakeDamage", FrameAnimation_DESC("Cup.png", 28, 33, 0.1f, true));

	//Renderer->CreateFrameAnimationFolder("IngameCupheadTakeDamageAir", FrameAnimation_DESC("IngameCupheadTakeDamageAir", 0.1f));
	//Renderer->CreateFrameAnimationFolder("IngameCupheadTakeDamageGround", FrameAnimation_DESC("IngameCupheadTakeDamageGround", 0.1f));

	// Idle (v)
	Renderer->CreateFrameAnimation("IngameCupheadIdle", FrameAnimation_DESC("Cup.png", 0, 7, 0.1f, true));
	Renderer->CreateFrameAnimation("IngameCupheadIdleDownStart", FrameAnimation_DESC("Cup.png", 160, 166, 0.1f, true));
	Renderer->CreateFrameAnimation("IngameCupheadIdleDown", FrameAnimation_DESC("Cup.png", 168, 172, 0.1f, true));
	Renderer->CreateFrameAnimation("IngameCupheadIdleDownTurn", FrameAnimation_DESC("Cup.png", 159, 159, 0.1f, true));
	
	//Renderer->CreateFrameAnimationFolder("IngameCupheadIdleDownStart", FrameAnimation_DESC("InGameCupheadIdleDownStart", 0, 7, 0.05f, true));
	//Renderer->CreateFrameAnimationFolder("IngameCupheadIdleDown", FrameAnimation_DESC("IngameCupheadIdleDown", 0, 8, 0.05f, true));
	//Renderer->CreateFrameAnimationFolder("IngameCupheadIdleDownTurn", FrameAnimation_DESC("InGameCupheadIdleDownTurn", 0, 0, 0.05f, true));
	//
	//Renderer->CreateFrameAnimationFolder("IngameCupheadIdle", FrameAnimation_DESC("IngameCupheadIdle", 0.1f));

	SetState(InGameCharacterState::Prepare);
	Renderer->ChangeFrameAnimation("IngameCupheadIntro");
	Renderer->SetPivot(PIVOTMODE::BOT);

	Movement = CreateComponent<InGameCharacterMovementCompmonent>();
	Animation = CreateComponent<InGameCharacterAnimationControllerComponent>();
	Animation->SetCharacterName("Cuphead");
	//PeaShooter* Shooter = GetLevel()->CreateActor<PeaShooter>();
	//Shooter->SetParent(this);

	SpreadShooter* Shooter = GetLevel()->CreateActor<SpreadShooter>();
	Shooter->SetParent(this);
}

void InGameCuphead::Update(float _DeltaTime)
{
	if (IsInputEnabled == false)
	{
		return;
	}

	// 키보드로 가능한 애들
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
	GetLevel()->GetMainCameraActorTransform().SetLocalPosition({ 0, 0 });

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



	if (true == GameEngineInput::GetInst()->IsDown("Dash"))
	{
		IsInputEnabled = false;
		Dash();
	}

	else if (true == GameEngineInput::GetInst()->IsPress("Aim"))
	{
		Aim();
	}

	else if (true == GameEngineInput::GetInst()->IsPress("MoveDown"))
	{
		Duck(); 
	}

	else if (true == GameEngineInput::GetInst()->IsPress("MoveLeft") ||
	         true == GameEngineInput::GetInst()->IsPress("MoveRight"))
	{
		Walk();
	}

	else
	{
		Idle();
	}

	if (true == GameEngineInput::GetInst()->IsPress("Shoot") &&
		GetState() != InGameCharacterState::Dash)
	{
		Shoot();
	}
	else
	{
		SetAttackState(InGameCharacterAttackState::None);
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

void InGameCuphead::OnPrepareAnimationEnded(const FrameAnimation_DESC& _Info)
{
	IsInputEnabled = true;
}

void InGameCuphead::OnDashAnimationEnded(const FrameAnimation_DESC& _Info)
{
	IsInputEnabled = true;
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
	SetState(InGameCharacterState::Dash);
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
	SetState(InGameCharacterState::Prepare);
}

void InGameCuphead::Run()
{
}

void InGameCuphead::Shoot()
{
	SetAttackState(InGameCharacterAttackState::Shoot);
}

void InGameCuphead::SpecialAttack()
{
}

void InGameCuphead::SuperAttack()
{
}
