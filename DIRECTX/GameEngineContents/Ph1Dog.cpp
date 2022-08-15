#include "PreCompile.h"
#include "Ph1Dog.h"
#include "InGameMonsterAnimationControllerComponent.h"
#include "InGameMovementComponent.h"
#include "YarnballShooter.h"
#include "TattooShooter.h"
#include "BulldogPlane.h"
#include "IInGameCharacterBase.h"
#include "TennisballShooter.h"

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
	,AttackState(InGameMonsterAttackState::None)
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

		Renderer->AnimationBindEnd("Ph1DogAttack3", std::bind(&Ph1Dog::OnAttackAnimationFrameFinished, this, std::placeholders::_1));
		Renderer->AnimationBindEnd("Ph1DogAttack4", std::bind(&Ph1Dog::OnAttackAnimationFrameFinished, this, std::placeholders::_1));

		Renderer->ChangeFrameAnimation("Ph1DogIdle");

		Renderer->ScaleToTexture();

		Renderer->SetPivot(PIVOTMODE::BOT);

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
	Renderer->ScaleToTexture();

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
	int RandomAttack = (rand() % 2);
	++RandomAttack;
	AnimationDirectionSwtich();
	if(RandomAttack == 1)
	{
		if (IsAnimationDiretionRight == true)
		{
			GetTransform().PixLocalPositiveX();
			GetTransform().SetLocalPosition({ 863, 125 });
		}
		else
		{
			GetTransform().PixLocalNegativeX();
			GetTransform().SetLocalPosition({ 417, 125 });
		}

		SetState(InGameMonsterState::Attack3);// Å«°Å
	}
	else
	{
		if (IsAnimationDiretionRight == true)
		{
			GetTransform().PixLocalPositiveX();
			GetTransform().SetLocalPosition({ 1162, 155 });

		}
		else
		{
			GetTransform().PixLocalNegativeX();
			GetTransform().SetLocalPosition({ 116, 155 });
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
	else
	{
		SetAttackState(InGameMonsterAttackState::None);
	}
}

void Ph1Dog::OnAttack2AnimationFrameChanged(const FrameAnimation_DESC& _Info) // ÀÛÀº Ä­
{
	if (_Info.CurFrame == 6)
	{
		SetAttackState(InGameMonsterAttackState::TennisBall);
	}
	else
	{
		SetAttackState(InGameMonsterAttackState::None);
	}
}

void Ph1Dog::OnAttackAnimationFrameFinished(const FrameAnimation_DESC& _Info)
{
	Idle();
}

bool Ph1Dog::AnimationDirectionSwtich()
{
	IsAnimationDiretionRight = !IsAnimationDiretionRight;
	return IsAnimationDiretionRight;
}
