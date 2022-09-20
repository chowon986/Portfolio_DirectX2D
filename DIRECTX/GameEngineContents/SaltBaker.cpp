#include "PreCompile.h"
#include "SaltBaker.h"
#include "SaltBakerShooter.h"
#include "InGameMovementComponent.h"
#include "InGameMonsterAnimationControllerComponent.h"

SaltBaker::SaltBaker()
	: Renderer(nullptr)
	, State(InGameMonsterState::Prepare)
	, AttackState(InGameMonsterAttackState::None)
	, Collision(nullptr)
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
	Renderer->CreateFrameAnimationFolder("SaltBakerPhase2Intro", FrameAnimation_DESC("SaltBakerPhase2Intro", 0.05f));
	Renderer->AnimationBindFrame("SaltBakerIntro", std::bind(&SaltBaker::OnIntroAnimationFrameChanged, this, std::placeholders::_1));
	Renderer->AnimationBindFrame("SaltBakerAttack1", std::bind(&SaltBaker::OnAttack1AnimationFrameChanged, this, std::placeholders::_1));
	Renderer->AnimationBindFrame("SaltBakerAttack2", std::bind(&SaltBaker::OnAttack2AnimationFrameChanged, this, std::placeholders::_1));
	Renderer->AnimationBindFrame("SaltBakerAttack3", std::bind(&SaltBaker::OnAttack3AnimationFrameChanged, this, std::placeholders::_1));
	Renderer->AnimationBindFrame("SaltBakerAttack4", std::bind(&SaltBaker::OnAttack4AnimationFrameChanged, this, std::placeholders::_1));
	Renderer->AnimationBindFrame("SaltBakerPhase2Intro", std::bind(&SaltBaker::OnSaltBakerPhase2IntroFrameChanged, this, std::placeholders::_1));
	Renderer->SetScaleModeImage();
	Renderer->ChangeFrameAnimation("SaltBakerIntro");

	SetRenderer(Renderer);

	InGameMovementComponent* Movement = CreateComponent<InGameMovementComponent>();
	InGameMonsterAnimationControllerComponent* Animation = CreateComponent<InGameMonsterAnimationControllerComponent>();
	Animation->SetMonsterName("SaltBaker");

	// �� ����
	{
		SaltBakerShooter* SaltBakerGun = GetLevel()->CreateActor<SaltBakerShooter>();
		SaltBakerGun->SetParent(this);
	}
}

void SaltBaker::Update(float _DeltaTime)
{
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
	else if (_Info.CurFrame >= 109)
	{
		BackgroundRenderer->GetTransform().SetWorldMove(float4::DOWN * GameEngineTime::GetDeltaTime() * 500);
	}
}
