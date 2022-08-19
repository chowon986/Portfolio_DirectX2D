#include "PreCompile.h"
#include "Ph2Dog.h"
#include "InGamePh2DogAnimationControllerComponent.h"
#include "InGameMovementComponent.h"
#include "YarnballShooter.h"
#include "TattooShooter.h"
#include "IInGameCharacterBase.h"
#include "BowWowShooter.h"
#include <math.h>

Ph2Dog::Ph2Dog()
	: Renderer(nullptr)
	, AttackState(InGameMonsterAttackState::None)
	, Animation(nullptr)
	, Collision(nullptr)
	, RotationAngle(0.0f)
	, State(InGamePh2DogState::None)
	, Player(nullptr)
	, OnceCheck(false)
{
}

Ph2Dog::~Ph2Dog()
{
}

void Ph2Dog::Start()
{
	// IntroTop : 위 -> 오른쪽 -> 아래 -> 왼쪽
	// IntroRight : 오른쪽 -> 아래 -> 왼쪽 -> 위
	// IntroBottom : 아래 -> 왼쪽 -> 위 -> 오른쪽
	// IntroLeft : 왼쪽 -> 위쪽 -> 오른쪽 -> 아래

	{
		Renderer = CreateComponent<GameEngineTextureRenderer>();
		Renderer->CreateFrameAnimationFolder("Ph2DogIntroTop", FrameAnimation_DESC("Ph2DogIntroTop", 0.1f));
		Renderer->CreateFrameAnimationFolder("Ph2DogIntroRight", FrameAnimation_DESC("Ph2DogIntroRight", 0.1f));
		Renderer->CreateFrameAnimationFolder("Ph2DogIntroBottom", FrameAnimation_DESC("Ph2DogIntroBottom", 0.1f));
		Renderer->CreateFrameAnimationFolder("Ph2DogIntroLeft", FrameAnimation_DESC("Ph2DogIntroLeft", 0.1f));

		Renderer->CreateFrameAnimationFolder("Ph2DogIdle1", FrameAnimation_DESC("Ph2DogIdle1", 0.06f));
		Renderer->CreateFrameAnimationFolder("Ph2DogIdle2", FrameAnimation_DESC("Ph2DogIdle2", 0.06f));
		Renderer->CreateFrameAnimationFolder("Ph2DogIdle3", FrameAnimation_DESC("Ph2DogIdle3", 0.06f));
		Renderer->CreateFrameAnimationFolder("Ph2DogIdle4", FrameAnimation_DESC("Ph2DogIdle4", 0.06f));
		Renderer->CreateFrameAnimationFolder("Ph2DogIdle5", FrameAnimation_DESC("Ph2DogIdle5", 0.06f));
		Renderer->CreateFrameAnimationFolder("Ph2DogIdle6", FrameAnimation_DESC("Ph2DogIdle6", 0.06f));
		Renderer->CreateFrameAnimationFolder("Ph2DogIdle7", FrameAnimation_DESC("Ph2DogIdle7", 0.06f));
		Renderer->CreateFrameAnimationFolder("Ph2DogIdle8", FrameAnimation_DESC("Ph2DogIdle8", 0.06f));
		Renderer->CreateFrameAnimationFolder("Ph2DogIdle9", FrameAnimation_DESC("Ph2DogIdle9", 0.06f));

		Renderer->CreateFrameAnimationFolder("Ph2DogPain1", FrameAnimation_DESC("Ph2DogPain1", 0.1f));
		Renderer->CreateFrameAnimationFolder("Ph2DogPain2", FrameAnimation_DESC("Ph2DogPain2", 0.1f));
		Renderer->CreateFrameAnimationFolder("Ph2DogPain3", FrameAnimation_DESC("Ph2DogPain3", 0.1f));
		Renderer->CreateFrameAnimationFolder("Ph2DogPain4", FrameAnimation_DESC("Ph2DogPain4", 0.1f));
		Renderer->CreateFrameAnimationFolder("Ph2DogPain5", FrameAnimation_DESC("Ph2DogPain5", 0.1f));
		Renderer->CreateFrameAnimationFolder("Ph2DogPain6", FrameAnimation_DESC("Ph2DogPain6", 0.1f));
		Renderer->CreateFrameAnimationFolder("Ph2DogPain7", FrameAnimation_DESC("Ph2DogPain7", 0.1f));
		Renderer->CreateFrameAnimationFolder("Ph2DogPain8", FrameAnimation_DESC("Ph2DogPain8", 0.1f));
		Renderer->CreateFrameAnimationFolder("Ph2DogPain9", FrameAnimation_DESC("Ph2DogPain9", 0.1f));

		Renderer->CreateFrameAnimationFolder("Ph2DogAttack1", FrameAnimation_DESC("Ph2DogAttack1", 0.06f));
		Renderer->CreateFrameAnimationFolder("Ph2DogAttack2", FrameAnimation_DESC("Ph2DogAttack2", 0.06f));
		Renderer->CreateFrameAnimationFolder("Ph2DogAttack3", FrameAnimation_DESC("Ph2DogAttack3", 0.06f));
		Renderer->CreateFrameAnimationFolder("Ph2DogAttack4", FrameAnimation_DESC("Ph2DogAttack4", 0.06f));
		Renderer->CreateFrameAnimationFolder("Ph2DogAttack5", FrameAnimation_DESC("Ph2DogAttack5", 0.06f));
		Renderer->CreateFrameAnimationFolder("Ph2DogAttack6", FrameAnimation_DESC("Ph2DogAttack6", 0.06f));
		Renderer->CreateFrameAnimationFolder("Ph2DogAttack7", FrameAnimation_DESC("Ph2DogAttack7", 0.06f));
		Renderer->CreateFrameAnimationFolder("Ph2DogAttack8", FrameAnimation_DESC("Ph2DogAttack8", 0.06f));
		Renderer->CreateFrameAnimationFolder("Ph2DogAttack9", FrameAnimation_DESC("Ph2DogAttack9", 0.06f));

		Renderer->AnimationBindFrame("Ph2DogAttack1", std::bind(&Ph2Dog::OnAttackAnimationFrameChanged, this, std::placeholders::_1));
		Renderer->AnimationBindFrame("Ph2DogAttack2", std::bind(&Ph2Dog::OnAttackAnimationFrameChanged, this, std::placeholders::_1));
		Renderer->AnimationBindFrame("Ph2DogAttack3", std::bind(&Ph2Dog::OnAttackAnimationFrameChanged, this, std::placeholders::_1));
		Renderer->AnimationBindFrame("Ph2DogAttack4", std::bind(&Ph2Dog::OnAttackAnimationFrameChanged, this, std::placeholders::_1));
		Renderer->AnimationBindFrame("Ph2DogAttack5", std::bind(&Ph2Dog::OnAttackAnimationFrameChanged, this, std::placeholders::_1));
		Renderer->AnimationBindFrame("Ph2DogAttack6", std::bind(&Ph2Dog::OnAttackAnimationFrameChanged, this, std::placeholders::_1));
		Renderer->AnimationBindFrame("Ph2DogAttack7", std::bind(&Ph2Dog::OnAttackAnimationFrameChanged, this, std::placeholders::_1));
		Renderer->AnimationBindFrame("Ph2DogAttack8", std::bind(&Ph2Dog::OnAttackAnimationFrameChanged, this, std::placeholders::_1));
		Renderer->AnimationBindFrame("Ph2DogAttack9", std::bind(&Ph2Dog::OnAttackAnimationFrameChanged, this, std::placeholders::_1));

		Renderer->AnimationBindFrame("Ph2DogIdle1", std::bind(&Ph2Dog::OnIdleAnimaitionFrameChanged, this, std::placeholders::_1));
		Renderer->AnimationBindFrame("Ph2DogIdle2", std::bind(&Ph2Dog::OnIdleAnimaitionFrameChanged, this, std::placeholders::_1));
		Renderer->AnimationBindFrame("Ph2DogIdle3", std::bind(&Ph2Dog::OnIdleAnimaitionFrameChanged, this, std::placeholders::_1));
		Renderer->AnimationBindFrame("Ph2DogIdle4", std::bind(&Ph2Dog::OnIdleAnimaitionFrameChanged, this, std::placeholders::_1));
		Renderer->AnimationBindFrame("Ph2DogIdle5", std::bind(&Ph2Dog::OnIdleAnimaitionFrameChanged, this, std::placeholders::_1));
		Renderer->AnimationBindFrame("Ph2DogIdle6", std::bind(&Ph2Dog::OnIdleAnimaitionFrameChanged, this, std::placeholders::_1));
		Renderer->AnimationBindFrame("Ph2DogIdle7", std::bind(&Ph2Dog::OnIdleAnimaitionFrameChanged, this, std::placeholders::_1));
		Renderer->AnimationBindFrame("Ph2DogIdle8", std::bind(&Ph2Dog::OnIdleAnimaitionFrameChanged, this, std::placeholders::_1));
		Renderer->AnimationBindFrame("Ph2DogIdle9", std::bind(&Ph2Dog::OnIdleAnimaitionFrameChanged, this, std::placeholders::_1));


		Renderer->AnimationBindEnd("Ph2DogIntroTop", std::bind(&Ph2Dog::OnAnimaitionFinished, this, std::placeholders::_1));
		Renderer->AnimationBindEnd("Ph2DogIntroRight", std::bind(&Ph2Dog::OnAnimaitionFinished, this, std::placeholders::_1));
		Renderer->AnimationBindEnd("Ph2DogIntroBottom", std::bind(&Ph2Dog::OnAnimaitionFinished, this, std::placeholders::_1));
		Renderer->AnimationBindEnd("Ph2DogIntroLeft", std::bind(&Ph2Dog::OnAnimaitionFinished, this, std::placeholders::_1));

		Renderer->AnimationBindEnd("Ph2DogAttack1", std::bind(&Ph2Dog::OnAnimaitionFinished, this, std::placeholders::_1));
		Renderer->AnimationBindEnd("Ph2DogAttack2", std::bind(&Ph2Dog::OnAnimaitionFinished, this, std::placeholders::_1));
		Renderer->AnimationBindEnd("Ph2DogAttack3", std::bind(&Ph2Dog::OnAnimaitionFinished, this, std::placeholders::_1));
		Renderer->AnimationBindEnd("Ph2DogAttack4", std::bind(&Ph2Dog::OnAnimaitionFinished, this, std::placeholders::_1));
		Renderer->AnimationBindEnd("Ph2DogAttack5", std::bind(&Ph2Dog::OnAnimaitionFinished, this, std::placeholders::_1));
		Renderer->AnimationBindEnd("Ph2DogAttack6", std::bind(&Ph2Dog::OnAnimaitionFinished, this, std::placeholders::_1));
		Renderer->AnimationBindEnd("Ph2DogAttack7", std::bind(&Ph2Dog::OnAnimaitionFinished, this, std::placeholders::_1));
		Renderer->AnimationBindEnd("Ph2DogAttack8", std::bind(&Ph2Dog::OnAnimaitionFinished, this, std::placeholders::_1));
		Renderer->AnimationBindEnd("Ph2DogAttack9", std::bind(&Ph2Dog::OnAnimaitionFinished, this, std::placeholders::_1));

		Renderer->AnimationBindEnd("Ph2DogPain1", std::bind(&Ph2Dog::OnAnimaitionFinished, this, std::placeholders::_1));
		Renderer->AnimationBindEnd("Ph2DogPain2", std::bind(&Ph2Dog::OnAnimaitionFinished, this, std::placeholders::_1));
		Renderer->AnimationBindEnd("Ph2DogPain3", std::bind(&Ph2Dog::OnAnimaitionFinished, this, std::placeholders::_1));
		Renderer->AnimationBindEnd("Ph2DogPain4", std::bind(&Ph2Dog::OnAnimaitionFinished, this, std::placeholders::_1));
		Renderer->AnimationBindEnd("Ph2DogPain5", std::bind(&Ph2Dog::OnAnimaitionFinished, this, std::placeholders::_1));
		Renderer->AnimationBindEnd("Ph2DogPain6", std::bind(&Ph2Dog::OnAnimaitionFinished, this, std::placeholders::_1));
		Renderer->AnimationBindEnd("Ph2DogPain7", std::bind(&Ph2Dog::OnAnimaitionFinished, this, std::placeholders::_1));
		Renderer->AnimationBindEnd("Ph2DogPain8", std::bind(&Ph2Dog::OnAnimaitionFinished, this, std::placeholders::_1));
		Renderer->AnimationBindEnd("Ph2DogPain9", std::bind(&Ph2Dog::OnAnimaitionFinished, this, std::placeholders::_1));
		
		Renderer->AnimationBindEnd("Ph2DogIdle1", std::bind(&Ph2Dog::OnIdleAnimaitionFinished, this, std::placeholders::_1));
		Renderer->AnimationBindEnd("Ph2DogIdle2", std::bind(&Ph2Dog::OnIdleAnimaitionFinished, this, std::placeholders::_1));
		Renderer->AnimationBindEnd("Ph2DogIdle3", std::bind(&Ph2Dog::OnIdleAnimaitionFinished, this, std::placeholders::_1));
		Renderer->AnimationBindEnd("Ph2DogIdle4", std::bind(&Ph2Dog::OnIdleAnimaitionFinished, this, std::placeholders::_1));
		Renderer->AnimationBindEnd("Ph2DogIdle5", std::bind(&Ph2Dog::OnIdleAnimaitionFinished, this, std::placeholders::_1));
		Renderer->AnimationBindEnd("Ph2DogIdle6", std::bind(&Ph2Dog::OnIdleAnimaitionFinished, this, std::placeholders::_1));
		Renderer->AnimationBindEnd("Ph2DogIdle7", std::bind(&Ph2Dog::OnIdleAnimaitionFinished, this, std::placeholders::_1));
		Renderer->AnimationBindEnd("Ph2DogIdle8", std::bind(&Ph2Dog::OnIdleAnimaitionFinished, this, std::placeholders::_1));
		Renderer->AnimationBindEnd("Ph2DogIdle9", std::bind(&Ph2Dog::OnIdleAnimaitionFinished, this, std::placeholders::_1));

		Renderer->ChangeFrameAnimation("Ph2DogIntroTop");
		Renderer->GetTransform().SetLocalPosition({ 0, 0, (int)ZOrder::UI + 1 });
		Renderer->SetScaleModeImage();
		SetRenderer(Renderer);
	}


	// 컴포넌트 생성
	{
		Animation = CreateComponent<InGamePh2DogAnimationControllerComponent>();
		Animation->SetMonsterName("Ph2Dog");

		// Collision
		Collision = CreateComponent<GameEngineCollision>();
		Collision->SetParent(this);
		Collision->GetTransform().SetLocalScale({ 100.0f, 100.0f, 1.0f });
		Collision->ChangeOrder(ObjectOrder::MONSTER);
	}


	// 총 생성
	{
		BowWowShooter* BowWowGun = GetLevel()->CreateActor<BowWowShooter>();
		BowWowGun->SetParent(this);
	}

	srand(time(NULL));
	SetHP(5);
}

void Ph2Dog::Update(float _DeltaTime)
{
	if (OnceCheck == false)
	{
		if (GetPh2DogState() == InGamePh2DogState::Prepare1)
		{			
			SetStartAngle(90.0f * GameEngineMath::DegreeToRadian);
			double TestX = GetXFromAngle(GetStartAngle());
			double TestY = GetYFromAngle(GetStartAngle());
			GetTransform().SetWorldPosition({ static_cast<float>(TestX + 640.0f), static_cast<float>(TestY - 360.0f) });
		}
		else if (GetPh2DogState() == InGamePh2DogState::Prepare2)
		{
			SetStartAngle(0.0f * GameEngineMath::DegreeToRadian);
			double TestX = GetXFromAngle(GetStartAngle());
			double TestY = GetYFromAngle(GetStartAngle());
			GetTransform().SetWorldPosition({ static_cast<float>(TestX + 640.0f), static_cast<float>(TestY - 360.0f) });
		}
		else if (GetPh2DogState() == InGamePh2DogState::Prepare3)
		{
			SetStartAngle(270.0f * GameEngineMath::DegreeToRadian);
			double TestX = GetXFromAngle(GetStartAngle());
			double TestY = GetYFromAngle(GetStartAngle());
			GetTransform().SetWorldPosition({ static_cast<float>(TestX + 640.0f), static_cast<float>(TestY - 360.0f) });
		}
		else if (GetPh2DogState() == InGamePh2DogState::Prepare4)
		{
			SetStartAngle(180.0f * GameEngineMath::DegreeToRadian);
			double TestX = GetXFromAngle(GetStartAngle());
			double TestY = GetYFromAngle(GetStartAngle());
			GetTransform().SetWorldPosition({ static_cast<float>(TestX + 640.0f), static_cast<float>(TestY - 360.0f) });
		}

		OnceCheck = true;
	}


	if (GetPh2DogState() == InGamePh2DogState::Idle ||
		GetPh2DogState() == InGamePh2DogState::Attack)
	{

		if (Angle >= 6.28319f)
		{
			Angle = 0.0f;
		}
		Angle += _DeltaTime;

		double TestX = GetXFromAngle(Angle + GetStartAngle());
		double TestY = GetYFromAngle(Angle + GetStartAngle());

		GetTransform().SetWorldPosition({ static_cast<float>(TestX + 640.0f), static_cast<float>(TestY - 360.0f) });
	}
	if (true == Collision->IsCollision(CollisionType::CT_AABB2D, ObjectOrder::PC_BULLET, CollisionType::CT_AABB2D,
		std::bind(&Ph2Dog::OnTakeDamage, this, std::placeholders::_1, std::placeholders::_2)))
	{
		SetHP(GetHP() - 1);
		TakeDamage();
	}
}

bool Ph2Dog::SetStartPos()
{
	OnceCheck = true;
	return OnceCheck;
}

bool Ph2Dog::OnTakeDamage(GameEngineCollision* _This, GameEngineCollision* _Other)
{
	return true;
}

void Ph2Dog::TakeDamage()
{
	SetPh2DogState(InGamePh2DogState::TakeDamage);
}

void Ph2Dog::Prepare()
{
	SetPh2DogState(InGamePh2DogState::Prepare1);
}

void Ph2Dog::Idle()
{
	SetPh2DogState(InGamePh2DogState::Idle);
}

void Ph2Dog::Shoot()
{
	SetPh2DogState(InGamePh2DogState::Attack);
}

void Ph2Dog::Die()
{
	SetPh2DogState(InGamePh2DogState::Die);
}

void Ph2Dog::None()
{
	SetPh2DogState(InGamePh2DogState::None);
}

double Ph2Dog::GetXFromAngle(double Angle)
{
	return cosf(Angle) * 550;
}

double Ph2Dog::GetYFromAngle(double Angle)
{
	return sinf(Angle) * 300;
}

void Ph2Dog::SetPlayer(IInGameCharacterBase* _Player)
{
	Player = _Player; 
}

void Ph2Dog::OnAnimaitionFinished(const FrameAnimation_DESC& _Info) 
{
	Idle();
}

void Ph2Dog::OnIdleAnimaitionFinished(const FrameAnimation_DESC& _Info)
{
	int RandomAction = rand() % 5;
	++RandomAction;

	if (RandomAction == 1)
	{
		float4 PlayerPos = Player->GetRenderer()->GetTransform().GetWorldPosition();
		float4 MyPos = GetRenderer()->GetTransform().GetWorldPosition();
		float4 Direction = float4({ (PlayerPos - MyPos) / (PlayerPos - MyPos) });
		SetBowWowDirection(Direction);
		Shoot();
	}
	else
	{
		SetPh2DogState(InGamePh2DogState::None);
		Idle();
	}
}

void Ph2Dog::OnIdleAnimaitionFrameChanged(const FrameAnimation_DESC& _Info)
{
}

void Ph2Dog::OnAttackAnimationFrameChanged(const FrameAnimation_DESC& _Info)
{
	if (_Info.CurFrame == 2)
	{
		if (Player != nullptr)
		{

		SetAttackState(InGameMonsterAttackState::BowWow);

		}
	}
	else
	{
		SetAttackState(InGameMonsterAttackState::None);
	}
}