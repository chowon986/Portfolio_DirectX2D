#include "PreCompile.h"
#include "Ph2Dog.h"
#include "InGameMonsterAnimationControllerComponent.h"
#include "InGameMovementComponent.h"
#include "YarnballShooter.h"
#include "TattooShooter.h"
#include "IInGameCharacterBase.h"
#include "BowWowShooter.h"

Ph2Dog::Ph2Dog()
	: Collision(nullptr)
	, Renderer(nullptr)
	, ElapsedTime(-5.0f)
	, AttackIntervalTime(2.0f)
	, CountTimeOnOff(false)
{
}

Ph2Dog::~Ph2Dog()
{
}

void Ph2Dog::Start()
{
	// 애니메이션 생성
	{
		Renderer = CreateComponent<GameEngineTextureRenderer>();
		Renderer->CreateFrameAnimationFolder("Ph2DogEnter", FrameAnimation_DESC("Ph2DogEnter", 0.1f)); // Intro
		Renderer->CreateFrameAnimationFolder("Ph2DogIntro", FrameAnimation_DESC("Ph2DogIntro", 0.1f)); // Prepare

		Renderer->AnimationBindEnd("Ph2DogEnter", std::bind(&Ph2Dog::OnEnterAnimationFinished, this, std::placeholders::_1));
		Renderer->AnimationBindFrame("Ph2DogEnter", std::bind(&Ph2Dog::OnEnterAnimationFrameChanged, this, std::placeholders::_1));
		Renderer->AnimationBindEnd("Ph2DogIntro", std::bind(&Ph2Dog::OnPrepareAnimationFinished, this, std::placeholders::_1));
		Renderer->AnimationBindFrame("Ph2DogIntro", std::bind(&Ph2Dog::OnPreapareAnimationFrameChanged, this, std::placeholders::_1));

		Renderer->ChangeFrameAnimation("Ph2DogEnter");
	}


	// 컴포넌트 생성
	{
		Animation = CreateComponent<InGameMonsterAnimationControllerComponent>();
		Animation->SetMonsterName("Ph2Dog");
	}


	// 총 생성
	{
		BowWowShooter* BowWowGun = GetLevel()->CreateActor<BowWowShooter>();
		BowWowGun->SetParent(this);
	}

	srand(time(NULL));
	SetHP(5);
	SetState(InGameMonsterState::Idle);
	SetAttackState(InGameMonsterAttackState::None);
}

void Ph2Dog::Update(float _DeltaTime)
{
	Renderer->ScaleToTexture();

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

void Ph2Dog::TakeDamage()
{
}

void Ph2Dog::Prepare()
{
	SetState(InGameMonsterState::Prepare);
}

void Ph2Dog::Idle()
{
	CountTimeOnOff = true;
	SetState(InGameMonsterState::Idle);
}

void Ph2Dog::Shoot()
{
	//int RandomAttack = (rand() % 2);
	//++RandomAttack;
	//if (RandomAttack == 1)
	//{
	//	if (IsAnimationDiretionRight == true)
	//	{
	//		GetTransform().PixLocalPositiveX();
	//		GetTransform().SetLocalPosition({ 863, 125 });
	//	}
	//	else
	//	{
	//		GetTransform().PixLocalNegativeX();
	//		GetTransform().SetLocalPosition({ 417, 125 });
	//	}

	//	SetState(InGameMonsterState::Attack3);// 큰거
	//}
	//else
	//{
	//	if (IsAnimationDiretionRight == true)
	//	{
	//		GetTransform().PixLocalPositiveX();
	//		GetTransform().SetLocalPosition({ 1162, 155 });

	//	}
	//	else
	//	{
	//		GetTransform().PixLocalNegativeX();
	//		GetTransform().SetLocalPosition({ 116, 155 });
	//	}
	//	SetState(InGameMonsterState::Attack4); // 작은S
	//}
}

void Ph2Dog::Die()
{
	SetState(InGameMonsterState::Die);
}

void Ph2Dog::OnEnterAnimationFinished(const FrameAnimation_DESC& _Info)
{
	Prepare();
}

void Ph2Dog::OnEnterAnimationFrameChanged(const FrameAnimation_DESC& _Info)
{
	//if (_Info.CurFrame == 1)
	//{
	//	StartPos = GetTransform().GetLocalPosition();
	//	EndPos = float4(640, 360); // 고민 해 보기
	//	MoveSpeed = 100.0f;
	//	MoveToEndPos(StartPos, EndPos);
	//}
}

void Ph2Dog::OnPreapareAnimationFrameChanged(const FrameAnimation_DESC& _Info)
{
	//if (_Info.CurFrame == 1)
	//{
	//	StartPos = float4(640, 360);  // 고민 해 보기
	//	EndPos = GetTransform().GetLocalPosition();
	//	MoveSpeed = 100.0f;
	//	MoveToEndPos(StartPos, EndPos);
	//}
}

void Ph2Dog::OnPrepareAnimationFinished(const FrameAnimation_DESC& _Info)
{
	Idle();
}
