#include "PreCompile.h"
#include "Ph1Dog.h"
#include "InGameMonsterAnimationControllerComponent.h"
#include "InGameMovementComponent.h"
#include "YarnballShooter.h"
#include "TattooShooter.h"
#include "BulldogPlane.h"
#include "IInGameCharacterBase.h"
#include "TennisballShooter.h"
#include <GameEngineBase/GameEngineRandom.h>

Ph1Dog::Ph1Dog()
	: Collision(nullptr)
	, Renderer(nullptr)
	, MoveWithPlaneOn(false)
	, ElapsedTime(-7.0f)
	, AttackIntervalTime(3.0f)
	, CountTimeOnOff(true)
	, IsAnimationDiretionRight(true)
	, Plane(nullptr)
	, Animation(nullptr)
	, AttackState(InGameMonsterAttackState::None)
	, Movement(nullptr)
	, State(InGameMonsterState::Idle)
{
}

Ph1Dog::~Ph1Dog()
{
}

void Ph1Dog::Start()
{
	// ¾Ö´Ï¸ÞÀÌ¼Ç »ý¼º
	{
		Renderer = CreateComponent<GameEngineTextureRenderer>();

		Renderer->CreateFrameAnimationFolder("Ph1DogIdle", FrameAnimation_DESC("PH1DogIdle", 0.1f)); // Idle
		Renderer->CreateFrameAnimationFolder("Ph1DogAttack3", FrameAnimation_DESC("PH1DogAttack1", 0.1f, false)); // Å« Ä­
		Renderer->CreateFrameAnimationFolder("Ph1DogAttack4", FrameAnimation_DESC("PH1DogAttack2", 0.1f, false)); // ÀÛÀº Ä­

		Renderer->AnimationBindFrame("Ph1DogAttack3", std::bind(&Ph1Dog::OnAttack1AnimationFrameChanged, this, std::placeholders::_1));
		Renderer->AnimationBindFrame("Ph1DogAttack4", std::bind(&Ph1Dog::OnAttack2AnimationFrameChanged, this, std::placeholders::_1));

		Renderer->ChangeFrameAnimation("Ph1DogIdle");

		Renderer->SetScaleModeImage();

		SetRenderer(Renderer);
	}


	// ÄÄÆ÷³ÍÆ® »ý¼º
	{
		Animation = CreateComponent<InGameMonsterAnimationControllerComponent>();
		Animation->SetMonsterName("Ph1Dog");
	}


	// ÃÑ »ý¼º
	{
		TennisballShooter* TennisballGun = GetLevel()->CreateActor<TennisballShooter>();
		TennisballGun->SetParent(this);
	}

	srand(time(NULL));
	SetHP(5);
}

void Ph1Dog::Update(float _DeltaTime)
{

	if (MoveWithPlaneOn == false)
	{
		if (nullptr != GetParent<BulldogPlane>())
		{
			Plane = GetParent<BulldogPlane>();
			MoveWithPlaneOn = true;
		}
	}

	if (CountTimeOnOff == true)
	{
		ElapsedTime += _DeltaTime;
	}

	if (ElapsedTime >= AttackIntervalTime)
	{
		ElapsedTime = 0.0f;
		CountTimeOnOff = false;
		Shoot();
	}
}

void Ph1Dog::TakeDamage()
{
}

void Ph1Dog::Prepare()
{
}

void Ph1Dog::Idle()
{
	CountTimeOnOff = true;
	SetState(InGameMonsterState::Idle);
}

void Ph1Dog::Shoot()
{
	int RandomAttack = GameEngineRandom::MainRandom.RandomInt(0, 1);
	AnimationDirectionSwtich();
	if(RandomAttack == 1)
	{
		if (IsAnimationDiretionRight == true)
		{
			GetTransform().PixLocalPositiveX();
			GetTransform().SetLocalPosition({ 858, 188 });
		}
		else
		{
			GetTransform().PixLocalNegativeX();
			GetTransform().SetLocalPosition({ 431, 188 });
		}

		SetState(InGameMonsterState::Attack3);// Å«°Å
	}
	else
	{
		if (IsAnimationDiretionRight == true)
		{
			GetTransform().PixLocalPositiveX();
			GetTransform().SetLocalPosition({ 1158, 260 });

		}
		else
		{
			GetTransform().PixLocalNegativeX();
			GetTransform().SetLocalPosition({ 122, 260 });
		}
		SetState(InGameMonsterState::Attack4); // ÀÛÀºS
	}
}

void Ph1Dog::Die()
{
	SetState(InGameMonsterState::Die);
}

void Ph1Dog::OnAttack1AnimationFrameChanged(const FrameAnimation_DESC& _Info) // Å« Ä­
{
	if (_Info.CurFrame == 5)
	{
		SetAttackState(InGameMonsterAttackState::TennisBall);
	}
	else if (_Info.CurFrame == 10)
	{
		Idle();
	}
	else
	{
		SetAttackState(InGameMonsterAttackState::None);
	}
}

void Ph1Dog::OnAttack2AnimationFrameChanged(const FrameAnimation_DESC& _Info) // ÀÛÀº Ä­
{
	if (_Info.CurFrame == 5)
	{
		SetAttackState(InGameMonsterAttackState::TennisBall);
	}
	else if (_Info.CurFrame == 10)
	{
		Idle();
	}
	else
	{
		SetAttackState(InGameMonsterAttackState::None);
	}
}

bool Ph1Dog::AnimationDirectionSwtich()
{
	IsAnimationDiretionRight = !IsAnimationDiretionRight;
	return IsAnimationDiretionRight;
}
