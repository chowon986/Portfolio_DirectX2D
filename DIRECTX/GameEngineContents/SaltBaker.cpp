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
	Renderer->CreateFrameAnimationFolder("SaltBakerAttack1", FrameAnimation_DESC("SaltBakerAttack1", 0.1f));
	Renderer->CreateFrameAnimationFolder("SaltBakerIntro", FrameAnimation_DESC("SaltBakerIntro", 0.1f));
	Renderer->CreateFrameAnimationFolder("SaltBakerAttack3", FrameAnimation_DESC("SaltBakerAttack3", 0.1f));
	Renderer->CreateFrameAnimationFolder("SaltBakerAttack4", FrameAnimation_DESC("SaltBakerAttack4", 0.1f));
	Renderer->AnimationBindFrame("SaltBakerAttack1", std::bind(&SaltBaker::OnAttack1AnimationFrameChanged, this, std::placeholders::_1));
	Renderer->AnimationBindFrame("SaltBakerIntro", std::bind(&SaltBaker::OnIntroAnimationFrameChanged, this, std::placeholders::_1));
	Renderer->AnimationBindFrame("SaltBakerAttack3", std::bind(&SaltBaker::OnAttack3AnimationFrameChanged, this, std::placeholders::_1));
	Renderer->AnimationBindFrame("SaltBakerAttack4", std::bind(&SaltBaker::OnAttack4AnimationFrameChanged, this, std::placeholders::_1));
	Renderer->SetScaleModeImage();
	Renderer->ChangeFrameAnimation("SaltBakerIntro");

	SetRenderer(Renderer);

	InGameMovementComponent* Movement = CreateComponent<InGameMovementComponent>();
	InGameMonsterAnimationControllerComponent* Animation = CreateComponent<InGameMonsterAnimationControllerComponent>();
	Animation->SetMonsterName("SaltBaker");

	// ÃÑ »ý¼º
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

void SaltBaker::OnAttack3AnimationFrameChanged(const FrameAnimation_DESC& _Info)
{
	if(_Info.CurFrame == 104)
	{
		SetAttackState(InGameMonsterAttackState::Attack3);
	}
	else if (_Info.CurFrame == 133)
	{
		SetState(InGameMonsterState::Attack1);
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

void SaltBaker::OnAttack4AnimationFrameChanged(const FrameAnimation_DESC& _Info)
{
	if (_Info.CurFrame == 101)
	{
		SetAttackState(InGameMonsterAttackState::Attack4);
	}
}
