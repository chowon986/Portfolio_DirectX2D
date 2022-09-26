#include "PreCompile.h"
#include "Chicken.h"
#include "SaltBakerLevel.h"
#include "InGameCuphead.h"
#include "SaltBaker.h"
#include "ChickenPhysicsComponent.h"
#include "InGameMonsterAnimationControllerComponent.h"

Chicken::Chicken()
	: CanAttack(false)
	, LerpTime(0.0f)
	, PlayerPosX(0.0f)
	, BeforePhase(Phase::Ready)
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
	Renderer->CreateFrameAnimationFolder("ChickenVanish", FrameAnimation_DESC("ChickenVanish", 0.07f,false));


	Renderer->CreateFrameAnimationFolder("ChickenPhase2Intro", FrameAnimation_DESC("ChickenPhase2Intro", 0.07f));
	Renderer->CreateFrameAnimationFolder("ChickenPhase2Idle", FrameAnimation_DESC("ChickenPhase2Idle", 0.07f));
	Renderer->CreateFrameAnimationFolder("ChickenPrepareAttack2", FrameAnimation_DESC("ChickenPrepareAttack2", 0.07f));
	Renderer->CreateFrameAnimationFolder("ChickenAttack2", FrameAnimation_DESC("ChickenAttack2", 0.07f));
	Renderer->CreateFrameAnimationFolder("ChickenAttackFinish2", FrameAnimation_DESC("ChickenAttackFinish2", 0.07f));
	Renderer->CreateFrameAnimationFolder("ChickenDie", FrameAnimation_DESC("ChickenDeath", 0.07f));

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
	Renderer->AnimationBindFrame("ChickenVanish", std::bind(&Chicken::OnChickenVanishAnimationFrameChanged, this, std::placeholders::_1));
	Renderer->AnimationBindFrame("ChickenPhase2Intro", std::bind(&Chicken::OnChickenPhase2IntroAnimationFrameChanged, this, std::placeholders::_1));
	Renderer->AnimationBindFrame("ChickenPhase2Idle", std::bind(&Chicken::OnChickenPhase2IdleAnimationFrameChanged, this, std::placeholders::_1));
	Renderer->AnimationBindFrame("ChickenPrepareAttack2", std::bind(&Chicken::OnChickenPrepareAttack2AnimationFrameChanged, this, std::placeholders::_1));
	Renderer->AnimationBindFrame("ChickenAttack2", std::bind(&Chicken::OnChickenAttack2AnimationFrameChanged, this, std::placeholders::_1));
	Renderer->AnimationBindFrame("ChickenAttackFinish2", std::bind(&Chicken::OnChickenAttackFinish2AnimationFrameChanged, this, std::placeholders::_1));

	Renderer->SetPivotToVector(float4::UP * 5);

	Collision = CreateComponent<GameEngineCollision>();
	Collision->GetTransform().SetLocalScale({ 100.0f, 100.0f, 1.0f });
	Collision->ChangeOrder(ObjectOrder::MONSTER_BULLET2);
}

void Chicken::Update(float _DeltaTime)
{
	AttackIntervalTime += _DeltaTime;
	LerpTime += _DeltaTime;

	if (Level = dynamic_cast<SaltBakerLevel*>(GetLevel()))
	{
		if (Level->GetPhase() != BeforePhase)
		{
			BeforePhase = Level->GetPhase();

			if (Level->GetPhase() == Phase::Phase1)
			{
				Physics->SetGravity(1.0f);
			}
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

void Chicken::PrepareAttack2()
{
	SetState(InGameMonsterState::PrepareAttack2);
}

void Chicken::Phase2Idle()
{
	SetState(InGameMonsterState::Phase2Idle);
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

void Chicken::OnChickenAttack2AnimationFrameChanged(const FrameAnimation_DESC& _Info)
{
	if (true == Physics->IsOnGround)
	{
		SetState(InGameMonsterState::AttackFinish2);
	}
}

void Chicken::OnChickenAttackFinish2AnimationFrameChanged(const FrameAnimation_DESC& _Info)
{
	if (_Info.CurFrame == 15)
	{
		Phase2Idle();
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
	if (_Info.CurFrame == 5)
	{
		if (SaltBakerLevel* Level = dynamic_cast<SaltBakerLevel*>(GetLevel()))
		{
			if (SaltBaker* Boss = dynamic_cast<SaltBaker*>(Level->GetSaltBaker()))
			{
				if (Boss->GetState() == InGameMonsterState::MoveToPhase2)
				{
					if (true == Physics->IsOnGround)
					{
						Renderer->ChangeFrameAnimation("ChickenVanish");
					}
				}
			}
		}
	}

	if (_Info.CurFrame == 11)
	{
		PrepareAttack1();
	}
}

void Chicken::OnChickenVanishAnimationFrameChanged(const FrameAnimation_DESC& _Info)
{
	if (_Info.CurFrame == 6)
	{
		Off();
	}
}

void Chicken::OnChickenPhase2IntroAnimationFrameChanged(const FrameAnimation_DESC& _Info)
{
	if (_Info.CurFrame == 14)
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

	if (_Info.CurFrame == 34)
	{
		Phase2Idle();
	}
}

void Chicken::OnChickenPhase2IdleAnimationFrameChanged(const FrameAnimation_DESC& _Info)
{
	if (_Info.CurFrame == 15)
	{
		PrepareAttack2();
	}
}

void Chicken::OnChickenPrepareAttack2AnimationFrameChanged(const FrameAnimation_DESC& _Info)
{
	if (_Info.CurFrame == 11)
	{
		Physics->Reset();

		if (SaltBakerLevel* Level = dynamic_cast<SaltBakerLevel*>(GetLevel()))
		{
			if (Level->GetPhase() == Phase::Phase2)
			{
				Physics->AddForce(8.5f); // 아래->위
			}

			if (InGameCuphead* Player = dynamic_cast<InGameCuphead*>(Level->GetPlayer()))
			{
				PlayerPosX = Player->GetTransform().GetWorldPosition().x;
			}
		}
	}

	if (_Info.CurFrame == 12)
	{
		SetState(InGameMonsterState::Attack2);
	}
}

