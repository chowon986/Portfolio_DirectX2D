#include "PreCompile.h"
#include "InGameCuphead.h"
#include "InGameCharacterAnimationControllerComponent.h"
#include "InGameCharacterMovementCompmonent.h"
#include "PeaShooter.h"

InGameCuphead::InGameCuphead()
	: IsPrepareAnimationEnd(false)
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
	Renderer->AnimationBindEnd("IngameCupheadIntro", &InGameCuphead::OnPrepareAnimationEnded, this);

	// Jump
	Renderer->CreateFrameAnimationFolder("IngameCupheadJump", FrameAnimation_DESC("IngameCupheadJump", 0.1f));

	// Parry
	Renderer->CreateFrameAnimationFolder("IngameCupheadParryHand", FrameAnimation_DESC("IngameCupheadParryHand", 0.1f));

	// Run
	Renderer->CreateFrameAnimationFolder("IngameCupheadRun", FrameAnimation_DESC("IngameCupheadRun", 0.05f));

	// Shoot
	Renderer->CreateFrameAnimationFolder("IngameCupheadShootUp", FrameAnimation_DESC("IngameCupheadShootUp", 0.1f));
	Renderer->CreateFrameAnimationFolder("IngameCupheadShootDiagUp", FrameAnimation_DESC("IngameCupheadShootDiagUp", 0.1f));
	Renderer->CreateFrameAnimationFolder("IngameCupheadShootStraight", FrameAnimation_DESC("IngameCupheadShootStraight", 0.1f));
	Renderer->CreateFrameAnimationFolder("IngameCupheadShootDiagDown", FrameAnimation_DESC("IngameCupheadShootDiagDown", 0.1f));
	Renderer->CreateFrameAnimationFolder("IngameCupheadShootDown", FrameAnimation_DESC("IngameCupheadShootDown", 0.1f));
	Renderer->CreateFrameAnimationFolder("IngameCupheadRunShootStraight", FrameAnimation_DESC("IngameCupheadRunShootStraight", 0.1f));
	Renderer->CreateFrameAnimationFolder("IngameCupheadRunShootDiagUp", FrameAnimation_DESC("IngameCupheadRunShootDiagUp", 0.1f));
	Renderer->CreateFrameAnimationFolder("IngameCupheadDuckShoot", FrameAnimation_DESC("IngameCupheadDuckShoot", 0.1f));

	// TakeDamage
	Renderer->CreateFrameAnimationFolder("IngameCupheadTakeDamageAir", FrameAnimation_DESC("IngameCupheadTakeDamageAir", 0.1f));
	Renderer->CreateFrameAnimationFolder("IngameCupheadTakeDamageGround", FrameAnimation_DESC("IngameCupheadTakeDamageGround", 0.1f));

	// Idle
	Renderer->CreateFrameAnimationFolder("IngameCupheadIdle", FrameAnimation_DESC("IngameCupheadIdle", 0.1f));
	Renderer->CreateFrameAnimationFolder("IngameCupheadIdleDownStart", FrameAnimation_DESC("InGameCupheadIdleDownStart", 0, 7, 0.05f, true));
	Renderer->CreateFrameAnimationFolder("IngameCupheadIdleDown", FrameAnimation_DESC("IngameCupheadIdleDown", 0, 8, 0.05f, true));
	Renderer->CreateFrameAnimationFolder("IngameCupheadIdleDownTurn", FrameAnimation_DESC("InGameCupheadIdleDownTurn", 0, 0, 0.05f, true));

	SetState(InGameCharacterState::Prepare);
	Renderer->ChangeFrameAnimation("IngameCupheadIntro");
	Renderer->ScaleToTexture();
	Renderer->SetPivot(PIVOTMODE::BOT);

	Movement = CreateComponent<InGameCharacterMovementCompmonent>();
	Animation = CreateComponent<InGameCharacterAnimationControllerComponent>();
	Animation->SetCharacterName("Cuphead");
	PeaShooter* Shooter = GetLevel()->CreateActor<PeaShooter>();
	Shooter->SetParent(this);
}

void InGameCuphead::Update(float _DeltaTime)
{
	if (IsPrepareAnimationEnd == false)
	{
		return;
	}

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
	GetLevel()->GetMainCameraActorTransform().SetLocalPosition({0, 0 });

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

	//if (true == GameEngineInput::GetInst()->IsDown("Dash"))
	//{
	//	Dash();
	//}

	if (true == GameEngineInput::GetInst()->IsPress("Aim"))
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

	if (true == GameEngineInput::GetInst()->IsPress("Shoot"))
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
	IsPrepareAnimationEnd = true;
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
	//SetState(InGameCharacterState::Dash);
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
