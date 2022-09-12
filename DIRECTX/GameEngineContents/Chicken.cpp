#include "PreCompile.h"
#include "Chicken.h"
#include "ChickenPhysicsComponent.h"
#include "InGameMonsterAnimationControllerComponent.h"

Chicken::Chicken()
{
}

Chicken::~Chicken()
{
}

void Chicken::Start()
{
	Renderer = CreateComponent<GameEngineTextureRenderer>();
	Renderer->CreateFrameAnimationFolder("ChickenIntro", FrameAnimation_DESC("PeashotIntro", 0.1f));
	Renderer->CreateFrameAnimationFolder("ChickenIdle", FrameAnimation_DESC("PeashotIntro", 0.1f));
	Renderer->CreateFrameAnimationFolder("ChickenAttack3", FrameAnimation_DESC("PeashotIntro", 0.1f));
	Renderer->SetScaleModeImage();
	Renderer->ChangeFrameAnimation("ChickenIdle");

	SetRenderer(Renderer);

	SetChickenPhysicsComponent(CreateComponent<ChickenPhysicsComponent>());

	InGameMonsterAnimationControllerComponent* Animation = CreateComponent<InGameMonsterAnimationControllerComponent>();
	Animation->SetMonsterName("Chicken");
}

void Chicken::Update(float _DeltaTime)
{
	AttackIntervalTime += _DeltaTime;
	if /*(GetState() == InGameMonsterState::Idle &&*/( Physics->IsOnGround == true)
	{
		if (AttackIntervalTime > 2.0f)
		{
			AttackIntervalTime = 0.0f;
			Shoot();
			Physics->IsOnGround = false;
		}
	}
}

void Chicken::TakeDamage()
{
	SetState(InGameMonsterState::TakeDamage);
}

void Chicken::Prepare()
{
	SetState(InGameMonsterState::Prepare);
}

void Chicken::Idle()
{
	SetState(InGameMonsterState::Idle);
}

void Chicken::Shoot()
{
	//SetState(InGameMonsterState::Attack1);
	//SetAttackState(InGameMonsterAttackState::Attack1);
	SetState(InGameMonsterState::Attack3);
	Physics->Reset();
	Physics->AddForce(-300);
}

void Chicken::Die()
{
	SetState(InGameMonsterState::Die);
}

void Chicken::SetChickenPhysicsComponent(ChickenPhysicsComponent* _Physics)
{
	Physics = _Physics;
}
