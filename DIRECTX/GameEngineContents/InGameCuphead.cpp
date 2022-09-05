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
	, IsOpenScoreBoard(false)
	, Collision(nullptr)
	, Renderer(nullptr)
	, OnParriable(false)
	, AlphaOn(true)
	, CanTakeDamageElapsedTime(0.0f)
	, CanTakeDamageIntervalTime(1.0f)
{
}

InGameCuphead::~InGameCuphead()
{
}

void InGameCuphead::Start()
{
	IInGameCharacterBase::Start();
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
	Renderer->CreateFrameAnimationCutTexture("IngameCupheadParry", FrameAnimation_DESC("Cup.png", 120, 127, 0.05f, true));
	Renderer->AnimationBindEnd("IngameCupheadParry", std::bind(&InGameCuphead::OnParryAnimationFrameEnd, this, std::placeholders::_1));
	Renderer->AnimationBindStart("IngameCupheadParry", std::bind(&InGameCuphead::OnParryAnimationFrameStarted, this, std::placeholders::_1));

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
	Renderer->AnimationBindEnd("IngameCupheadTakeDamage", std::bind(&InGameCuphead::OnTakeDamageAnimationEnded, this, std::placeholders::_1));

	// Die
	Renderer->CreateFrameAnimationCutTexture("IngameCupheadGhost", FrameAnimation_DESC("Cup.png", 140, 155, 0.1f, true));
	Renderer->AnimationBindEnd("IngameCupheadGhost", std::bind(&InGameCuphead::OnGhostAnimationEnded, this, std::placeholders::_1));

	// Idle
	Renderer->CreateFrameAnimationCutTexture("IngameCupheadIdle", FrameAnimation_DESC("Cup.png", 0, 7, 0.1f, true));
	Renderer->CreateFrameAnimationCutTexture("IngameCupheadIdleDownStart", FrameAnimation_DESC("Cup.png", 160, 166, 0.1f, true));
	Renderer->CreateFrameAnimationCutTexture("IngameCupheadIdleDown", FrameAnimation_DESC("Cup.png", 168, 172, 0.1f, true));
	Renderer->CreateFrameAnimationCutTexture("IngameCupheadIdleDownTurn", FrameAnimation_DESC("Cup.png", 159, 159, 0.1f, true));

	Renderer->AnimationBindStart("IngameCupheadRunShootStraight", std::bind(&InGameCuphead::OnShootAnimationFrameStarted, this, std::placeholders::_1));
	Renderer->AnimationBindStart("IngameCupheadRunShootDiagUp", std::bind(&InGameCuphead::OnShootAnimationFrameStarted, this, std::placeholders::_1));
	Renderer->AnimationBindStart("IngameCupheadShootStraight", std::bind(&InGameCuphead::OnShootAnimationFrameStarted, this, std::placeholders::_1));
	Renderer->AnimationBindStart("IngameCupheadShootDiagDown", std::bind(&InGameCuphead::OnShootAnimationFrameStarted, this, std::placeholders::_1));
	Renderer->AnimationBindStart("IngameCupheadShootDiagUp", std::bind(&InGameCuphead::OnShootAnimationFrameStarted, this, std::placeholders::_1));
	Renderer->AnimationBindStart("IngameCupheadShootDown", std::bind(&InGameCuphead::OnShootAnimationFrameStarted, this, std::placeholders::_1));
	Renderer->AnimationBindStart("IngameCupheadShootUp", std::bind(&InGameCuphead::OnShootAnimationFrameStarted, this, std::placeholders::_1));
	Renderer->AnimationBindStart("IngameCupheadDuckShoot", std::bind(&InGameCuphead::OnShootAnimationFrameStarted, this, std::placeholders::_1));

	Renderer->AnimationBindFrame("IngameCupheadRunShootStraight", std::bind(&InGameCuphead::OnShootAnimationFrameChanged, this, std::placeholders::_1));
	Renderer->AnimationBindFrame("IngameCupheadRunShootDiagUp", std::bind(&InGameCuphead::OnShootAnimationFrameChanged, this, std::placeholders::_1));
	Renderer->AnimationBindFrame("IngameCupheadShootStraight", std::bind(&InGameCuphead::OnShootAnimationFrameChanged, this, std::placeholders::_1));
	Renderer->AnimationBindFrame("IngameCupheadShootDiagDown", std::bind(&InGameCuphead::OnShootAnimationFrameChanged, this, std::placeholders::_1));
	Renderer->AnimationBindFrame("IngameCupheadShootDiagUp", std::bind(&InGameCuphead::OnShootAnimationFrameChanged, this, std::placeholders::_1));
	Renderer->AnimationBindFrame("IngameCupheadShootDown", std::bind(&InGameCuphead::OnShootAnimationFrameChanged, this, std::placeholders::_1));
	Renderer->AnimationBindFrame("IngameCupheadShootUp", std::bind(&InGameCuphead::OnShootAnimationFrameChanged, this, std::placeholders::_1));
	Renderer->AnimationBindFrame("IngameCupheadDuckShoot", std::bind(&InGameCuphead::OnShootAnimationFrameChanged, this, std::placeholders::_1));


	SetHP(5);

	{
		// Collision
		MainCollision = CreateComponent<GameEngineCollision>();
		MainCollision->ChangeOrder(ObjectOrder::PC);
		MainCollision->GetTransform().SetLocalScale({ 100.0f, 100.0f, 1.0f });
		MainCollision->GetTransform().SetLocalPosition({ 0.0f, 60.0f });
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

		PeaShooter* Shooter = GetLevel()->CreateActor<PeaShooter>();
		Shooter->SetParent(this);

		//SpreadShooter* Shooter = GetLevel()->CreateActor<SpreadShooter>();
		//Shooter->SetParent(this);

		//ConvergeShooter* Shooter = GetLevel()->CreateActor<ConvergeShooter>();
		//Shooter->SetParent(this);

		//BoomerangShooter* Shooter = GetLevel()->CreateActor<BoomerangShooter>();
		//Shooter->SetParent(this);

		//ChargerShooter* Shooter = GetLevel()->CreateActor<ChargerShooter>();
		//Shooter->SetParent(this);
	}

	//GetLevel()->PushRenderer(Renderer, CAMERAORDER::ROTATECAMERA);
}

void InGameCuphead::Update(float _DeltaTime)
{
	IInGameCharacterBase::Update(_DeltaTime);
	OnCollisionDebug();
	CheckCollision();

	CanTakeDamageElapsedTime += _DeltaTime;

	if (true == GetLevel()->GetMainCameraActor()->IsFreeCameraMode())
	{
		return;
	}

	if (IsInputEnabled == false)
	{
		return;
	}

	if (GetState() == InGameCharacterState::TakeDamage)
	{
		AlphaOnOffChangeSwitch();
	}
	else
	{
		Renderer->On();
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

void InGameCuphead::OnTakeDamageAnimationEnded(const FrameAnimation_DESC& _Info)
{
	IsInputEnabled = true;
}

void InGameCuphead::OnGhostAnimationEnded(const FrameAnimation_DESC& _Info)
{
	if (IsInputEnabled == false)
	{
		IsInputEnabled = true;
	}

	OpenScoreBoard();
}

void InGameCuphead::OnShootAnimationFrameChanged(const FrameAnimation_DESC& _Info)
{
	FrameAnimation_DESC* Info = const_cast<FrameAnimation_DESC*>(&_Info);
	Info->Inter = 0.1f;
	if (Info->CurFrame == 2)
	{
		SetShooterState(InGameCharacterShooterState::BasicShot);
	}
	else
	{
		SetShooterState(InGameCharacterShooterState::None);
	}
}

void InGameCuphead::OnShootAnimationFrameStarted(const FrameAnimation_DESC& _Info)
{

}


void InGameCuphead::Aim()
{
	SetState(InGameCharacterState::Aim);
}

void InGameCuphead::TakeDamage()
{
	IsInputEnabled = false;
	SetState(InGameCharacterState::TakeDamage);
}

void InGameCuphead::Dash()
{
	SetState(InGameCharacterState::Dash);
}

void InGameCuphead::Die()
{
	if (GetHP() <= 0)
	{
		SetState(InGameCharacterState::Die);
	}
}

void InGameCuphead::Duck()
{
	SetState(InGameCharacterState::Duck);
}

void InGameCuphead::Jump()
{
	SetState(InGameCharacterState::Jump);
	GetPhysicsComponent()->Reset();
	GetPhysicsComponent()->AddForce(50);
}

void InGameCuphead::Parry()
{
	SetState(InGameCharacterState::Parry);
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
		if (GetIsOnGround() == true)
		{
			Jump();
		}
		else
		{
			Parry();
		}
	}

	else if (OnParriable == true)
	{
		Parry();
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
		if (GetIsOnGround() == true)
		{
			Idle();
		}
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

void InGameCuphead::CheckCollision()
{
	if (OnParriable == true)
	{
		MainCollision->IsCollision(CollisionType::CT_AABB2D, ObjectOrder::PARRIABLEOBJECT, CollisionType::CT_AABB2D,
			std::bind(&InGameCuphead::OnParry, this, std::placeholders::_1, std::placeholders::_2));
	}
	else
	{
		MainCollision->IsCollision(CollisionType::CT_AABB2D, ObjectOrder::PARRIABLEOBJECT, CollisionType::CT_AABB2D,
			std::bind(&InGameCuphead::OnTakeDamage, this, std::placeholders::_1, std::placeholders::_2));
	}

	MainCollision->IsCollision(CollisionType::CT_AABB2D, ObjectOrder::MONSTER_BULLET, CollisionType::CT_AABB2D,
		std::bind(&InGameCuphead::OnTakeDamage, this, std::placeholders::_1, std::placeholders::_2));
	MainCollision->IsCollision(CollisionType::CT_AABB2D, ObjectOrder::MONSTER, CollisionType::CT_AABB2D,
		std::bind(&InGameCuphead::OnTakeDamage, this, std::placeholders::_1, std::placeholders::_2));
}

bool InGameCuphead::GetIsOpenScoreBoard()
{
	return IsOpenScoreBoard;
}

bool InGameCuphead::OnTakeDamage(GameEngineCollision* _This, GameEngineCollision* _Other)
{
	if (CanTakeDamageIntervalTime < CanTakeDamageElapsedTime)
	{
		CanTakeDamageElapsedTime = 0.0f;
		TakeDamage();
	}
	return false;
}

bool InGameCuphead::OnParry(GameEngineCollision* _This, GameEngineCollision* _Other)
{
	int a = 0;
	return false;
}

void InGameCuphead::AlphaOnOffChangeSwitch()
{

}

void InGameCuphead::OnParryAnimationFrameEnd(const FrameAnimation_DESC& _Info)
{
	OnParriable = false;
	Idle();
}

void InGameCuphead::OnParryAnimationFrameStarted(const FrameAnimation_DESC& _Info)
{
	OnParriable = true;
}

void InGameCuphead::OnCollisionDebug()
{
	//GameEngineDebug::DrawBox(MainCollision->GetTransform(), { 1.0f, 0.0f,0.0f, 0.5f });
}

void InGameCuphead::OpenScoreBoard()
{
	IsOpenScoreBoard = true;
}
