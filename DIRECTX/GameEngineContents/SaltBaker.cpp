#include "PreCompile.h"
#include "SaltBaker.h"
#include "SaltBakerShooter.h"
#include "InGameMovementComponent.h"
#include "InGameMonsterAnimationControllerComponent.h"
#include "PepperShooter.h"
#include "InGameLevelBase.h"
#include "LimeBullet.h"
#include "Chicken.h"
#include "ChickenPhysicsComponent.h"
#include "InGameCuphead.h"
#include <GameEngineBase/GameEngineRandom.h>
#include "SaltBakerLevel.h"

SaltBaker::SaltBaker()
	: Renderer(nullptr)
	, State(InGameMonsterState::Prepare)
	, AttackState(InGameMonsterAttackState::None)
	, Collision(nullptr)
	, TimeCountOn(false)
	, CanAttackIntervalTime(3.0f)
	, ElapsedTime(0.0f)
	, TakeDamageNum(-1)
{
}

SaltBaker::~SaltBaker()
{
}

void SaltBaker::Start()
{
	Renderer = CreateComponent<GameEngineTextureRenderer>();
	Renderer->CreateFrameAnimationFolder("SaltBakerIntro", FrameAnimation_DESC("SaltBakerIntro", 0.07f));
	Renderer->CreateFrameAnimationFolder("SaltBakerAttack1", FrameAnimation_DESC("SaltBakerAttack1", 0.07f));
	Renderer->CreateFrameAnimationFolder("SaltBakerAttack2", FrameAnimation_DESC("SaltBakerAttack2", 0.07f));
	Renderer->CreateFrameAnimationFolder("SaltBakerAttack3", FrameAnimation_DESC("SaltBakerAttack3", 0.07f));
	Renderer->CreateFrameAnimationFolder("SaltBakerAttack4", FrameAnimation_DESC("SaltBakerAttack4", 0.07f));
	Renderer->CreateFrameAnimationFolder("SaltBakerAttack5", FrameAnimation_DESC("SaltBakerAttack5", 0.07f));
	Renderer->CreateFrameAnimationFolder("SaltBakerAttack6", FrameAnimation_DESC("SaltBakerAttack6", 0.07f));
	Renderer->CreateFrameAnimationFolder("SaltBakerPhase2Intro", FrameAnimation_DESC("SaltBakerPhase2Intro", 0.07f));
	Renderer->CreateFrameAnimationFolder("SaltBakerPhase2", FrameAnimation_DESC("SaltBakerPhase2", 0.07f));
	Renderer->CreateFrameAnimationFolder("SaltBakerIdle", FrameAnimation_DESC("SaltBakerIdle", 0.07f));
	Renderer->CreateFrameAnimationFolder("SaltBakerTakeDamage0", FrameAnimation_DESC("SaltBakerTakeDamage0", 0.07f));
	Renderer->CreateFrameAnimationFolder("SaltBakerTakeDamage1", FrameAnimation_DESC("SaltBakerTakeDamage1", 0.07f));
	Renderer->CreateFrameAnimationFolder("SaltBakerTakeDamage2", FrameAnimation_DESC("SaltBakerTakeDamage2", 0.07f));
	Renderer->CreateFrameAnimationFolder("SaltBakerTakeDamage3", FrameAnimation_DESC("SaltBakerTakeDamage3", 0.07f));
	Renderer->CreateFrameAnimationFolder("SaltBakerDie", FrameAnimation_DESC("SaltBakerDeath", 0.07f));

	Renderer->AnimationBindFrame("SaltBakerIntro", std::bind(&SaltBaker::OnIntroAnimationFrameChanged, this, std::placeholders::_1));
	Renderer->AnimationBindFrame("SaltBakerAttack1", std::bind(&SaltBaker::OnAttack1AnimationFrameChanged, this, std::placeholders::_1));
	Renderer->AnimationBindFrame("SaltBakerAttack2", std::bind(&SaltBaker::OnAttack2AnimationFrameChanged, this, std::placeholders::_1));
	Renderer->AnimationBindFrame("SaltBakerAttack3", std::bind(&SaltBaker::OnAttack3AnimationFrameChanged, this, std::placeholders::_1));
	Renderer->AnimationBindFrame("SaltBakerAttack4", std::bind(&SaltBaker::OnAttack4AnimationFrameChanged, this, std::placeholders::_1));
	Renderer->AnimationBindFrame("SaltBakerPhase2Intro", std::bind(&SaltBaker::OnSaltBakerPhase2IntroFrameChanged, this, std::placeholders::_1));
	Renderer->AnimationBindFrame("SaltBakerPhase2", std::bind(&SaltBaker::OnSaltBakerPhase2FrameChanged, this, std::placeholders::_1));
	Renderer->AnimationBindFrame("SaltBakerAttack5", std::bind(&SaltBaker::OnSaltBakerAttack5FrameChanged, this, std::placeholders::_1));
	Renderer->AnimationBindFrame("SaltBakerAttack6", std::bind(&SaltBaker::OnSaltBakerAttack6FrameChanged, this, std::placeholders::_1));
	Renderer->AnimationBindFrame("SaltBakerTakeDamage0", std::bind(&SaltBaker::OnSaltBakerTakeDamageFrameChanged, this, std::placeholders::_1));
	Renderer->AnimationBindFrame("SaltBakerTakeDamage1", std::bind(&SaltBaker::OnSaltBakerTakeDamageFrameChanged, this, std::placeholders::_1));
	Renderer->AnimationBindFrame("SaltBakerTakeDamage2", std::bind(&SaltBaker::OnSaltBakerTakeDamageFrameChanged, this, std::placeholders::_1));
	Renderer->AnimationBindFrame("SaltBakerTakeDamage3", std::bind(&SaltBaker::OnSaltBakerTakeDamageFrameChanged, this, std::placeholders::_1));
	Renderer->AnimationBindFrame("SaltBakerDie", std::bind(&SaltBaker::OnSaltBakerDieAnimationFrameChanged, this, std::placeholders::_1));
	Renderer->SetScaleModeImage();
	Renderer->ChangeFrameAnimation("SaltBakerIntro");

	SetRenderer(Renderer);

	HandRenderer = CreateComponent<GameEngineTextureRenderer>();
	HandRenderer->SetTexture("Hand.png");
	HandRenderer->ScaleToTexture();
	HandRenderer->Off();

	InGameMovementComponent* Movement = CreateComponent<InGameMovementComponent>();
	InGameMonsterAnimationControllerComponent* Animation = CreateComponent<InGameMonsterAnimationControllerComponent>();
	Animation->SetMonsterName("SaltBaker");

	// 총 생성
	{
		SaltBakerShooter* SaltBakerGun = GetLevel()->CreateActor<SaltBakerShooter>();
		SaltBakerGun->SetParent(this);
	}

	Collision = CreateComponent<GameEngineCollision>();
	Collision->GetTransform().SetLocalScale({ 300.0f, 500.0f, 1.0f });
	Collision->GetTransform().SetLocalPosition({ 0.0f, 300.0f });

	WholeCollision = CreateComponent<GameEngineCollision>();
	WholeCollision->GetTransform().SetLocalScale({ 1280.0f, 720.0f, 1.0f });
	WholeCollision->GetTransform().SetLocalPosition({ 0.0f, 0.0f });
	WholeCollision->Off();
}

void SaltBaker::Update(float _DeltaTime)
{
	//GEngine::CollisionDebugOn();
	if (Level != nullptr)
	{
		if (Level->GetPhase() == Phase::Phase2 &&
			GetState() == InGameMonsterState::Idle)
		{
			if (GetHP() <= 0)
			{
				//SetState(InGameMonsterState::Die);
				//return;
			}

			if (SaltBakerLevel* DycstLevel = dynamic_cast<SaltBakerLevel*>(Level))
			{
				if (false == DycstLevel->GetChicken()->IsUpdate())
				{
					Chicken* Ph2Monster = DycstLevel->GetChicken();
					Ph2Monster->GetChickenPhysicsComponent()->SetGravity(-1.0f);
					Ph2Monster->GetRenderer()->ChangeFrameAnimation("ChickenAttack2");
					Ph2Monster->On();
				}
			}
			TimeCountOn = true;
		}
		else
		{
			TimeCountOn = false;
		}
	}
	if (true == TimeCountOn)
	{
		ElapsedTime += _DeltaTime;
	}

	if (ElapsedTime > CanAttackIntervalTime)
	{
		ElapsedTime -= CanAttackIntervalTime;

		int RandomAttackNum = GameEngineRandom::MainRandom.RandomInt(0, 1);
		
		if (RandomAttackNum == 0)
		{
			SetState(InGameMonsterState::Attack5);
			SetAttackState(InGameMonsterAttackState::Attack5); //손을 만들어서 손이 set해줘야 할 것 같음
		}
		else
		{
			SetState(InGameMonsterState::Attack6);
			SetAttackState(InGameMonsterAttackState::Attack6);
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

	if (_Info.CurFrame >= 50 && _Info.CurFrame < 57)
	{
		float4 CurPos = Collision->GetTransform().GetWorldPosition();
		Collision->GetTransform().SetWorldPosition(CurPos + float4::LEFT * 50);
	}

	if (_Info.CurFrame == 62)
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

	if (_Info.CurFrame >= 33 && _Info.CurFrame <= 40) 
	{
		float4 CurPos = Collision->GetTransform().GetWorldPosition();
		Collision->GetTransform().SetWorldPosition(CurPos + float4::RIGHT * 45);
	}

	if (_Info.CurFrame == 44)
	{
		SetState(InGameMonsterState::Attack4);
	}
}

void SaltBaker::OnAttack2AnimationFrameChanged(const FrameAnimation_DESC& _Info)
{
	if (_Info.CurFrame > 2 && _Info.CurFrame < 9)
	{
		float4 CurPos = Collision->GetTransform().GetWorldPosition();
		Collision->GetTransform().SetWorldPosition(CurPos + float4::LEFT * 105);
	}

	if (_Info.CurFrame > 42 && _Info.CurFrame < 53)
	{
		float4 CurPos = Collision->GetTransform().GetWorldPosition();
		Collision->GetTransform().SetWorldPosition(CurPos + float4::RIGHT * 30);
	}

	if (_Info.CurFrame > 95 && _Info.CurFrame < 105)
	{
		float4 CurPos = Collision->GetTransform().GetWorldPosition();
		Collision->GetTransform().SetWorldPosition(CurPos + float4::RIGHT * 50);
	}

	if (_Info.CurFrame > 110 && _Info.CurFrame < 125)
	{
		float4 CurPos = Collision->GetTransform().GetWorldPosition();
		Collision->GetTransform().SetWorldPosition(CurPos + float4::LEFT * 55);
	}

	if (_Info.CurFrame > 140 )
	{
		float4 CurPos = Collision->GetTransform().GetWorldPosition();
		Collision->GetTransform().SetWorldPosition(CurPos + float4::RIGHT * 40);
	}

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

	if (_Info.CurFrame >= 130)
	{
		float4 CurPos = Collision->GetTransform().GetWorldPosition();
		Collision->GetTransform().SetWorldPosition(CurPos + float4::RIGHT * 70);
	}

	if (_Info.CurFrame == 133)
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
	if (_Info.CurFrame < 10)
	{
		float4 CurPos = Collision->GetTransform().GetWorldPosition();
		Collision->GetTransform().SetWorldPosition(CurPos + float4::LEFT * 70);
	}

	if (_Info.CurFrame > 15 && _Info.CurFrame < 21)
	{
		float4 CurPos = Collision->GetTransform().GetWorldPosition();
		Collision->GetTransform().SetWorldPosition(CurPos + float4::RIGHT * 70);
	}

	if (_Info.CurFrame == 100)
	{
		WholeCollision->On();
		WholeCollision->IsCollision(CollisionType::CT_AABB2D, ObjectOrder::MONSTER_BULLET, CollisionType::CT_AABB2D, std::bind(&SaltBaker::OnDeathCollision, this, std::placeholders::_1, std::placeholders::_2));
	}

	if (_Info.CurFrame == 108)
	{
		if (nullptr != BackgroundRenderer)
		{
			BackgroundRenderer->SetTexture("MoveKitchen.png");
		}
	}

	if (_Info.CurFrame == 130)
	{
		if (InGameLevelBase* Level = dynamic_cast<InGameLevelBase*>(GetLevel()))
		{
			if (InGameCuphead* Cuphead = dynamic_cast<InGameCuphead*>(Level->GetPlayer()))
			{
				Cuphead->GetTransform().SetWorldPosition({ 500.0f, -350.0f,Cuphead->GetTransform().GetWorldPosition().z });
				Cuphead->On();
				Cuphead->CanFly = true;
			}

		}
	}

	if (_Info.CurFrame == 135)
	{
		if (InGameLevelBase* Level = dynamic_cast<InGameLevelBase*>(GetLevel()))
		{
			if (InGameCuphead* Cuphead = dynamic_cast<InGameCuphead*>(Level->GetPlayer()))
			{
				Cuphead->CanFly = false;
			}

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
		Renderer->SetPivotToVector(float4{ 680.0f, -60.0f,Renderer->GetTransform().GetLocalPosition().z });
	}

	if (_Info.CurFrame >= 109)
	{
		if (nullptr != BackgroundRenderer)
		{
			BackgroundRenderer->GetTransform().SetWorldMove(float4::DOWN * GameEngineTime::GetDeltaTime() * 500);
		}
	}

	if (_Info.CurFrame == 145)
	{
		HandRenderer->GetTransform().SetWorldPosition({ 640.0f, -360.0f, Renderer->GetTransform().GetWorldPosition().z - 1 });
		HandRenderer->On();
	}
	
}

void SaltBaker::OnSaltBakerPhase2FrameChanged(const FrameAnimation_DESC& _Info)
{
	if (_Info.CurFrame == 36)
	{
		{
			PepperShooter* Pepper = GetLevel()->CreateActor<PepperShooter>();
			Pepper->SetParent(this);
			Pepper->GetTransform().SetWorldPosition({ 100.0f, -120.0f, GetTransform().GetWorldPosition().z - 1 });
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
			Pepper->GetTransform().SetWorldPosition({ 100.0f, -500.0f, GetTransform().GetWorldPosition().z - 1 });
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

void SaltBaker::OnSaltBakerTakeDamageFrameChanged(const FrameAnimation_DESC& _Info)
{
	if (TakeDamageNum != -1)
	{
		if (TakeDamageNum == 0)
		{
			if (_Info.CurFrame == 16)
			{
				SetState(InGameMonsterState::Idle);
			}
		}

		if (TakeDamageNum == 1)
		{
			if (_Info.CurFrame == 17)
			{
				SetState(InGameMonsterState::Idle);
			}
		}

		if (TakeDamageNum == 2)
		{
			if (_Info.CurFrame == 18)
			{
				SetState(InGameMonsterState::Idle);
			}
		}

		if (TakeDamageNum == 3)
		{
			if (_Info.CurFrame == 15)
			{
				SetState(InGameMonsterState::Idle);
			}
		}
	}
}

void SaltBaker::OnSaltBakerDieAnimationFrameChanged(const FrameAnimation_DESC& _Info)
{
	if (_Info.CurFrame == 90)
	{
		Death();
		if (nullptr != Level)
		{
			Level->SetPhase(Phase::Phase3);
		}
	}
}

CollisionReturn SaltBaker::OnDeathCollision(GameEngineCollision* _This, GameEngineCollision* _Other)
{
	if (LimeBullet* Bullet = dynamic_cast<LimeBullet*>(_Other->GetParent()))
	{
		Bullet->Death();
	}

	if(InGameLevelBase* Level = dynamic_cast<InGameLevelBase*>(GetLevel()))
	{
		Level->GetPlayer()->Off();
	}

	_This->Off();

	return CollisionReturn::Break;
}
