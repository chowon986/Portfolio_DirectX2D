#include "PreCompile.h"
#include "SaltBaker.h"
#include "SaltBakerShooter.h"
#include "InGameMovementComponent.h"
#include "InGameMonsterAnimationControllerComponent.h"

SaltBaker::SaltBaker()
	: Renderer(nullptr)
	, State(InGameMonsterState::Idle)
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
	Renderer->CreateFrameAnimationFolder("SaltBakerIntro", FrameAnimation_DESC("BulldogIdle", 0.1f));
	Renderer->CreateFrameAnimationFolder("SaltBakerIdle", FrameAnimation_DESC("BulldogIdle", 0.1f));
	Renderer->CreateFrameAnimationFolder("SaltBakerAttack3", FrameAnimation_DESC("BulldogAttack1", 0.1f));
	Renderer->AnimationBindFrame("SaltBakerAttack3", std::bind(&SaltBaker::Test, this, std::placeholders::_1));
	Renderer->SetScaleModeImage();
	Renderer->ChangeFrameAnimation("SaltBakerAttack3");

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
	//SetState(InGameMonsterState::Attack5);
	//SetAttackState(InGameMonsterAttackState::Attack5);
	SetState(InGameMonsterState::Attack3);
	SetAttackState(InGameMonsterAttackState::Attack3);
}

void SaltBaker::Die()
{
	SetState(InGameMonsterState::Die);
}

void SaltBaker::Test(const FrameAnimation_DESC& _Info)
{
	if (_Info.CurFrame == 3)
	{
		Shoot();
	}
	else if (_Info.CurFrame == 5)
	{
		Shoot();
	}
	else if (_Info.CurFrame == 7)
	{
		Shoot();
	}
	else
	{
		SetAttackState(InGameMonsterAttackState::None);
	}
}
