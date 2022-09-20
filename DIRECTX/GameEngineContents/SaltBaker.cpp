#include "PreCompile.h"
#include "SaltBaker.h"
#include "SaltBakerShooter.h"
#include "InGameMovementComponent.h"
#include "InGameMonsterAnimationControllerComponent.h"
#include "PepperShooter.h"
#include "InGameLevelBase.h"
#include <GameEngineBase/GameEngineRandom.h>

SaltBaker::SaltBaker()
	: Renderer(nullptr)
	, State(InGameMonsterState::Prepare)
	, AttackState(InGameMonsterAttackState::None)
	, Collision(nullptr)
	, TimeCountOn(false)
	, CanAttackIntervalTime(3.0f)
	, ElapsedTime(0.0f)
{
}

SaltBaker::~SaltBaker()
{
}

void SaltBaker::Start()
{
	Renderer = CreateComponent<GameEngineTextureRenderer>();
	Renderer->CreateFrameAnimationFolder("SaltBakerIntro", FrameAnimation_DESC("SaltBakerIntro", 0.05f));
	Renderer->CreateFrameAnimationFolder("SaltBakerAttack1", FrameAnimation_DESC("SaltBakerAttack1", 0.05f));
	Renderer->CreateFrameAnimationFolder("SaltBakerAttack2", FrameAnimation_DESC("SaltBakerAttack2", 0.05f));
	Renderer->CreateFrameAnimationFolder("SaltBakerAttack3", FrameAnimation_DESC("SaltBakerAttack3", 0.05f));
	Renderer->CreateFrameAnimationFolder("SaltBakerAttack4", FrameAnimation_DESC("SaltBakerAttack4", 0.05f));
	Renderer->CreateFrameAnimationFolder("SaltBakerAttack5", FrameAnimation_DESC("SaltBakerAttack5", 0.05f));
	Renderer->CreateFrameAnimationFolder("SaltBakerAttack6", FrameAnimation_DESC("SaltBakerAttack6", 0.05f));
	Renderer->CreateFrameAnimationFolder("SaltBakerPhase2Intro", FrameAnimation_DESC("SaltBakerPhase2Intro", 0.05f));
	Renderer->CreateFrameAnimationFolder("SaltBakerPhase2", FrameAnimation_DESC("SaltBakerPhase2", 0.05f));
	Renderer->CreateFrameAnimationFolder("SaltBakerIdle", FrameAnimation_DESC("SaltBakerIdle", 0.05f));
	Renderer->CreateFrameAnimationFolder("SaltBakerTakeDamage", FrameAnimation_DESC("SaltBakerIdle", 0.05f));

	Renderer->AnimationBindFrame("SaltBakerIntro", std::bind(&SaltBaker::OnIntroAnimationFrameChanged, this, std::placeholders::_1));
	Renderer->AnimationBindFrame("SaltBakerAttack1", std::bind(&SaltBaker::OnAttack1AnimationFrameChanged, this, std::placeholders::_1));
	Renderer->AnimationBindFrame("SaltBakerAttack2", std::bind(&SaltBaker::OnAttack2AnimationFrameChanged, this, std::placeholders::_1));
	Renderer->AnimationBindFrame("SaltBakerAttack3", std::bind(&SaltBaker::OnAttack3AnimationFrameChanged, this, std::placeholders::_1));
	Renderer->AnimationBindFrame("SaltBakerAttack4", std::bind(&SaltBaker::OnAttack4AnimationFrameChanged, this, std::placeholders::_1));
	Renderer->AnimationBindFrame("SaltBakerPhase2Intro", std::bind(&SaltBaker::OnSaltBakerPhase2IntroFrameChanged, this, std::placeholders::_1));
	Renderer->AnimationBindFrame("SaltBakerPhase2", std::bind(&SaltBaker::OnSaltBakerPhase2FrameChanged, this, std::placeholders::_1));
	Renderer->AnimationBindFrame("SaltBakerAttack5", std::bind(&SaltBaker::OnSaltBakerAttack5FrameChanged, this, std::placeholders::_1));
	Renderer->AnimationBindFrame("SaltBakerAttack6", std::bind(&SaltBaker::OnSaltBakerAttack6FrameChanged, this, std::placeholders::_1));
	Renderer->SetScaleModeImage();
	Renderer->ChangeFrameAnimation("SaltBakerIntro");

	SetRenderer(Renderer);

	InGameMovementComponent* Movement = CreateComponent<InGameMovementComponent>();
	InGameMonsterAnimationControllerComponent* Animation = CreateComponent<InGameMonsterAnimationControllerComponent>();
	Animation->SetMonsterName("SaltBaker");

	// 총 생성
	{
		SaltBakerShooter* SaltBakerGun = GetLevel()->CreateActor<SaltBakerShooter>();
		SaltBakerGun->SetParent(this);
	}
}

void SaltBaker::Update(float _DeltaTime)
{
	if (Level->GetPhase() == Phase::Phase2 &&
		GetState() == InGameMonsterState::Idle)
	{
		TimeCountOn = true;
	}
	else
	{
		TimeCountOn = false;
	}

	if (true == TimeCountOn)
	{
		ElapsedTime += _DeltaTime;
	}

	if (ElapsedTime > CanAttackIntervalTime)
	{
		ElapsedTime - CanAttackIntervalTime;

		int RandomAttackNum = GameEngineRandom::MainRandom.RandomInt(0, 1);

		if (RandomAttackNum == 0)
		{
			SetState(InGameMonsterState::Attack5);
			//SetAttackState(InGameMonsterAttackState::Attack5); 손을 만들어서 손이 set해줘야 할 것 같음
		}
		else
		{
			SetState(InGameMonsterState::Attack6);
			//SetAttackState(InGameMonsterAttackState::Attack6);
		}
	}
}

void SaltBaker::TakeDamage()
{
	SetState(InGameMonsterState::TakeDamage);
}

void SaltBaker::Prepare()
{
	SetState(InGameMonsterState::Prepare);
}

void SaltBaker::Idle()
{
	SetState(InGameMonsterState::Idle);
}

void SaltBaker::Shoot()
{
}

void SaltBaker::Die()
{
	SetState(InGameMonsterState::Die);
}

void SaltBaker::OnIntroAnimationFrameChanged(const FrameAnimation_DESC& _Info)
{
	if (_Info.CurFrame == 42)
	{
		SetState(InGameMonsterState::Prepare);
		SetAttackState(InGameMonsterAttackState::Attack2);
	}
	else if (_Info.CurFrame == 62)
	{
		SetState(InGameMonsterState::Attack3);
	}
}

void SaltBaker::OnAttack1AnimationFrameChanged(const FrameAnimation_DESC& _Info)
{
	if (_Info.CurFrame == 26)
	{
		SetAttackState(InGameMonsterAttackState::Attack1);
	}
	else if (_Info.CurFrame == 44)
	{
		SetState(InGameMonsterState::Attack4);
	}
}

void SaltBaker::OnAttack2AnimationFrameChanged(const FrameAnimation_DESC& _Info)
{
	if (_Info.CurFrame == 122)
	{
		SetAttackState(InGameMonsterAttackState::Attack2);
	}
	else if (_Info.CurFrame == 147)
	{
		SetState(InGameMonsterState::Attack1);
	}
}

void SaltBaker::OnAttack3AnimationFrameChanged(const FrameAnimation_DESC& _Info)
{
	if (_Info.CurFrame == 104)
	{
		SetAttackState(InGameMonsterAttackState::Attack3);
	}
	else if (_Info.CurFrame == 133)
	{
		SetState(InGameMonsterState::Attack1);
	}
}

void SaltBaker::OnAttack4AnimationFrameChanged(const FrameAnimation_DESC& _Info)
{
	if (_Info.CurFrame == 101)
	{
		SetAttackState(InGameMonsterAttackState::Attack4);
	}
	else if (_Info.CurFrame == 122)
	{
		if (GetHP() <= 0)
		{
			SetState(InGameMonsterState::MoveToPhase2);
			SetAttackState(InGameMonsterAttackState::None);
		}
		else
		{
			SetState(InGameMonsterState::Attack2);
		}
	}
}

void SaltBaker::OnSaltBakerPhase2IntroFrameChanged(const FrameAnimation_DESC& _Info)
{
	if (_Info.CurFrame == 108)
	{
		if (nullptr != BackgroundRenderer)
		{
			BackgroundRenderer->SetTexture("MoveKitchen.png");
		}
	}

	if (_Info.CurFrame == 146)
	{
		if (Level = dynamic_cast<InGameLevelBase*>(GetLevel()))
		{
			Level->SetPhase(Phase::Phase2);
		}
		SetState(InGameMonsterState::Phase2);
		Renderer->SetPivot(PIVOTMODE::RIGHT);
		Renderer->SetPivotToVector(float4{ 680.0f, 60.0f,Renderer->GetTransform().GetLocalPosition().z });
	}

	if (_Info.CurFrame >= 109)
	{
		BackgroundRenderer->GetTransform().SetWorldMove(float4::DOWN * GameEngineTime::GetDeltaTime() * 500);
	}
	
}

void SaltBaker::OnSaltBakerPhase2FrameChanged(const FrameAnimation_DESC& _Info)
{
	if (_Info.CurFrame == 36)
	{
		{
			PepperShooter* Pepper = GetLevel()->CreateActor<PepperShooter>();
			Pepper->SetParent(this);
			Pepper->GetTransform().SetWorldPosition({ 100.0f, -500.0f, GetTransform().GetWorldPosition().z - 1 });
			Pepper->SetDeathNum(0);
		}
		{
			PepperShooter* Pepper = GetLevel()->CreateActor<PepperShooter>();
			Pepper->SetParent(this);
			Pepper->GetTransform().SetWorldPosition({ 1180.0f, -120.0f, GetTransform().GetWorldPosition().z - 1 });
			Pepper->SetDeathNum(1);
		}
		{
			PepperShooter* Pepper = GetLevel()->CreateActor<PepperShooter>();
			Pepper->SetParent(this);
			Pepper->GetTransform().SetWorldPosition({ 100.0f, -120.0f, GetTransform().GetWorldPosition().z - 1 });
			Pepper->SetDeathNum(2);
		}
		{
			PepperShooter* Pepper = GetLevel()->CreateActor<PepperShooter>();
			Pepper->SetParent(this);
			Pepper->GetTransform().SetWorldPosition({ 1180.0f, -500.0f, GetTransform().GetWorldPosition().z - 1 });
			Pepper->SetDeathNum(3);
		}
	}

	if (_Info.CurFrame == 75)
	{
		SetState(InGameMonsterState::Idle);
	}
}

void SaltBaker::OnSaltBakerAttack5FrameChanged(const FrameAnimation_DESC& _Info)
{
	if (_Info.CurFrame == 43)
	{
		SetState(InGameMonsterState::Idle);
	}
}

void SaltBaker::OnSaltBakerAttack6FrameChanged(const FrameAnimation_DESC& _Info)
{
	if (_Info.CurFrame == 46)
	{
		SetState(InGameMonsterState::Idle);
	}
}
