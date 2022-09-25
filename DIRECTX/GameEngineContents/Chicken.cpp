#include "PreCompile.h"
#include "Chicken.h"
#include "SaltBakerLevel.h"
#include "InGameCuphead.h"
#include "ChickenPhysicsComponent.h"
#include "InGameMonsterAnimationControllerComponent.h"

Chicken::Chicken()
	: CanAttack(false)
	, LerpTime(0.0f)
	, PlayerPosX(0.0f)
{
}

Chicken::~Chicken()
{
}

void Chicken::Start()
{
	Renderer = CreateComponent<GameEngineTextureRenderer>();
	Renderer->CreateFrameAnimationFolder("ChickenIntro", FrameAnimation_DESC("ChickenIntro", 0.07f));
	Renderer->CreateFrameAnimationFolder("ChickenPrepareAttack1", FrameAnimation_DESC("ChickenJumpUp", 0.07f));
	Renderer->CreateFrameAnimationFolder("ChickenAttack1", FrameAnimation_DESC("ChickenSpin", 0.07f));
	Renderer->CreateFrameAnimationFolder("ChickenAttackFinish1", FrameAnimation_DESC("ChickenJumpDown", 0.07f));
	Renderer->CreateFrameAnimationFolder("ChickenIdle", FrameAnimation_DESC("ChickenIdle", 0.07f));
	Renderer->SetScaleModeImage();
	Renderer->ChangeFrameAnimation("ChickenIntro");

	SetRenderer(Renderer);

	SetChickenPhysicsComponent(CreateComponent<ChickenPhysicsComponent>());
	Physics->SetMass(0.1f);

	InGameMonsterAnimationControllerComponent* Animation = CreateComponent<InGameMonsterAnimationControllerComponent>();
	Animation->SetMonsterName("Chicken");

	Renderer->AnimationBindFrame("ChickenIntro", std::bind(&Chicken::OnChickenIntroAnimationFrameChanged, this, std::placeholders::_1));
	Renderer->AnimationBindFrame("ChickenPrepareAttack1", std::bind(&Chicken::OnChickenPrepareAttack1AnimationFrameChanged, this, std::placeholders::_1));
	Renderer->AnimationBindFrame("ChickenAttack1", std::bind(&Chicken::OnChickenAttack1AnimationFrameChanged, this, std::placeholders::_1));
	Renderer->AnimationBindFrame("ChickenAttackFinish1", std::bind(&Chicken::OnChickenAttackFinish1AnimationFrameChanged, this, std::placeholders::_1));
	Renderer->AnimationBindFrame("ChickenIdle", std::bind(&Chicken::OnChickenIdleAnimationFrameChanged, this, std::placeholders::_1));

	Renderer->SetPivotToVector(float4::UP * 5);

}

void Chicken::Update(float _DeltaTime)
{
	AttackIntervalTime += _DeltaTime;
	LerpTime += _DeltaTime;

	if (Level = dynamic_cast<SaltBakerLevel*>(GetLevel()))
	{
		if (Level->GetPhase() == Phase::Phase1)
		{
			Physics->SetGravity(1.0f);
		}
		else if (Level->GetPhase() == Phase::Phase2)
		{
			Physics->SetGravity(-1.0f);
		}
	}

	if (false == Physics->IsOnGround)
	{
		float Time = LerpTime / 2500;
		float4 CurPos = GetTransform().GetWorldPosition();

		if (PlayerPosX != 0.0f)
		{
			float DestPosX = GameEngineMath::LerpLimit(CurPos.x, PlayerPosX, Time);
			GetTransform().SetLocalPosition(float4({ DestPosX, CurPos.y, CurPos.z }));
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
	SetState(InGameMonsterState::Attack3);
}

void Chicken::Die()
{
	SetState(InGameMonsterState::Die);
}

void Chicken::SetChickenPhysicsComponent(ChickenPhysicsComponent* _Physics)
{
	Physics = _Physics;
}

void Chicken::PrepareAttack1()
{
	SetState(InGameMonsterState::PrepareAttack1);
}

void Chicken::OnChickenIntroAnimationFrameChanged(const FrameAnimation_DESC& _Info)
{
	if (_Info.CurFrame == 17)
	{
		PrepareAttack1();
	}
}

void Chicken::OnChickenPrepareAttack1AnimationFrameChanged(const FrameAnimation_DESC& _Info)
{
	if (_Info.CurFrame == 18)
	{
		Physics->Reset();

		if (SaltBakerLevel* Level = dynamic_cast<SaltBakerLevel*>(GetLevel()))
		{
			if (Level->GetPhase() == Phase::Phase1)
			{
				Physics->AddForce(-8.5f); // 아래->위
			}
			else if (Level->GetPhase() == Phase::Phase2)
			{
				Physics->AddForce(8.5f); // 아래->위
			}

			if (InGameCuphead* Player = dynamic_cast<InGameCuphead*>(Level->GetPlayer()))
			{
				PlayerPosX = Player->GetTransform().GetWorldPosition().x;
			}
		}
	}

	if (_Info.CurFrame == 19)
	{
		SetState(InGameMonsterState::Attack1);
	}
}

void Chicken::OnChickenAttack1AnimationFrameChanged(const FrameAnimation_DESC& _Info)
{
	if (_Info.CurFrame == 9)
	{
		SetState(InGameMonsterState::AttackFinish1);
	}
}

void Chicken::OnChickenAttackFinish1AnimationFrameChanged(const FrameAnimation_DESC& _Info)
{
	if (_Info.CurFrame == 10)
	{
		if (true != Physics->IsOnGround)
		{
			Renderer->CurAnimationPauseOn();
		}
		else if (true == Physics->IsOnGround)
		{
			if (true == Renderer->IsCurAnimationPause())
			{
				Renderer->CurAnimationPauseOff();
			}
		}
	}

	if (_Info.CurFrame == 15)
	{
		Idle();
	}
}

void Chicken::OnChickenIdleAnimationFrameChanged(const FrameAnimation_DESC& _Info)
{
	if (_Info.CurFrame == 11)
	{
		PrepareAttack1();
	}
}

