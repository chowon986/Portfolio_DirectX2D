#include "PreCompile.h"
#include "InGameCuphead.h"
#include "InGameCharacterAnimationControllerComponent.h"
#include "InGameCharacterMovementCompmonent.h"
#include "PhysicsComponent.h"
#include "PeaShooter.h"
#include "SpreadShooter.h"
#include "ConvergeShooter.h"
#include "BoomerangShooter.h"
#include "ChargerShooter.h"

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
		GameEngineInput::GetInst()->CreateKey("Jump", VK_CONTROL);
		GameEngineInput::GetInst()->CreateKey("Dash", 'Z');
	}

	Renderer = CreateComponent<GameEngineTextureRenderer>();
	SetRenderer(Renderer);

	// Aim
	Renderer->CreateFrameAnimationCutTexture("IngameCupheadAimDiagDown", FrameAnimation_DESC("Cup.png", 180, 184, 0.1f, true));
	Renderer->CreateFrameAnimationCutTexture("IngameCupheadAimDiagUp", FrameAnimation_DESC("Cup.png", 186, 190, 0.1f, true));
	Renderer->CreateFrameAnimationCutTexture("IngameCupheadAimDown", FrameAnimation_DESC("Cup.png", 192, 196, 0.1f, true));
	Renderer->CreateFrameAnimationCutTexture("IngameCupheadAimStraight", FrameAnimation_DESC("Cup.png", 200, 204, 0.1f, true));
	Renderer->CreateFrameAnimationCutTexture("IngameCupheadAimUp", FrameAnimation_DESC("Cup.png", 206, 210, 0.1f, true));

	// Dash
	Renderer->CreateFrameAnimationCutTexture("IngameCupheadDash", FrameAnimation_DESC("Cup_Dash.png", 0, 7, 0.1f, true));
	Renderer->AnimationBindEnd("IngameCupheadDash", std::bind(&InGameCuphead::OnDashAnimationEnded, this, std::placeholders::_1));

	// Intro
	Renderer->CreateFrameAnimationCutTexture("IngameCupheadIntro", FrameAnimation_DESC("Cup.png", 220, 247, 0.1f, true));
	Renderer->AnimationBindEnd("IngameCupheadIntro", std::bind(&InGameCuphead::OnPrepareAnimationEnded, this, std::placeholders::_1));

	// Jump
	Renderer->CreateFrameAnimationCutTexture("IngameCupheadJump", FrameAnimation_DESC("Cup.png", 20, 27, 0.05f, true));

	// Parry
	Renderer->CreateFrameAnimationCutTexture("IngameCupheadParryHand", FrameAnimation_DESC("Cup.png", 120, 127, 0.1f, true));

	// Run
	Renderer->CreateFrameAnimationCutTexture("IngameCupheadRun", FrameAnimation_DESC("Cup.png", 40, 55, 0.1f, true));

	// Shoot
	Renderer->CreateFrameAnimationCutTexture("IngameCupheadRunShootStraight", FrameAnimation_DESC("Cup.png", 60, 75, 0.1f, true));
	Renderer->CreateFrameAnimationCutTexture("IngameCupheadRunShootDiagUp", FrameAnimation_DESC("Cup.png", 80, 95, 0.1f, true));
	Renderer->CreateFrameAnimationCutTexture("IngameCupheadShootStraight", FrameAnimation_DESC("Cup.png", 100, 102, 0.1f, true));
	Renderer->CreateFrameAnimationCutTexture("IngameCupheadShootDiagDown", FrameAnimation_DESC("Cup.png", 104, 106, 0.1f, true));
	Renderer->CreateFrameAnimationCutTexture("IngameCupheadShootDiagUp", FrameAnimation_DESC("Cup.png", 108, 110, 0.1f, true));
	Renderer->CreateFrameAnimationCutTexture("IngameCupheadShootDown", FrameAnimation_DESC("Cup.png", 112, 114, 0.1f, true));
	Renderer->CreateFrameAnimationCutTexture("IngameCupheadShootUp", FrameAnimation_DESC("Cup.png", 116, 118, 0.1f, true));
	Renderer->CreateFrameAnimationCutTexture("IngameCupheadDuckShoot", FrameAnimation_DESC("Cup.png", 174, 176, 0.1f, true));

	// TakeDamage
	Renderer->CreateFrameAnimationCutTexture("IngameCupheadTakeDamage", FrameAnimation_DESC("Cup.png", 28, 33, 0.1f, true));

	// Idle
	Renderer->CreateFrameAnimationCutTexture("IngameCupheadIdle", FrameAnimation_DESC("Cup.png", 0, 7, 0.1f, true));
	Renderer->CreateFrameAnimationCutTexture("IngameCupheadIdleDownStart", FrameAnimation_DESC("Cup.png", 160, 166, 0.1f, true));
	Renderer->CreateFrameAnimationCutTexture("IngameCupheadIdleDown", FrameAnimation_DESC("Cup.png", 168, 172, 0.1f, true));
	Renderer->CreateFrameAnimationCutTexture("IngameCupheadIdleDownTurn", FrameAnimation_DESC("Cup.png", 159, 159, 0.1f, true));

	{
		// Collision
		Collision = CreateComponent<GameEngineCollision>();
		Collision->SetParent(this);
		Collision->GetTransform().SetLocalScale({ 100.0f, 100.0f, 1.0f });
		Collision->ChangeOrder(ObjectOrder::PC);
	}

	SetState(InGameCharacterState::Prepare);
	Renderer->ChangeFrameAnimation("IngameCupheadIntro");
	Renderer->ScaleToCutTexture(0);
	Renderer->SetPivot(PIVOTMODE::BOT);

	Movement = CreateComponent<InGameCharacterMovementCompmonent>();
	SetPhysicsComponent(CreateComponent<PhysicsComponent>());
	Animation = CreateComponent<InGameCharacterAnimationControllerComponent>();
	Animation->SetCharacterName("Cuphead");

	{
		// รั
		
		//PeaShooter* Shooter = GetLevel()->CreateActor<PeaShooter>();
		//Shooter->SetParent(this);

		//SpreadShooter* Shooter = GetLevel()->CreateActor<SpreadShooter>();
		//Shooter->SetParent(this);

		//ConvergeShooter* Shooter = GetLevel()->CreateActor<ConvergeShooter>();
		//Shooter->SetParent(this);

		BoomerangShooter* Shooter = GetLevel()->CreateActor<BoomerangShooter>();
		Shooter->SetParent(this);

		//ChargerShooter* Shooter = GetLevel()->CreateActor<ChargerShooter>();
		//Shooter->SetParent(this);
	}
}

void InGameCuphead::Update(float _DeltaTime)
{
	if (true == GetLevel()->GetMainCameraActor()->IsFreeCameraMode())
	{
		return;
	}

	GetLevel()->GetMainCameraActorTransform().SetLocalPosition({ 640, -360 });

	if (IsInputEnabled == false)
	{
		return;
	}

	UpdateDirection();
	UpdateState();

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
	SetState(InGameCharacterState::Jump);
	GetPhysicsComponent()->Reset();
	GetPhysicsComponent()->AddForce(55);
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

void InGameCuphead::UpdateState()
{
	if (true == GameEngineInput::GetInst()->IsDown("Dash"))
	{
		IsInputEnabled = false;
		Dash();
	}

	else if (true == GameEngineInput::GetInst()->IsDown("Jump"))
	{
		Jump();
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
}

void InGameCuphead::UpdateDirection()
{
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
}
