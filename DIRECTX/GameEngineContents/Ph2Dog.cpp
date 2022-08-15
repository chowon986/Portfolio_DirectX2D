#include "PreCompile.h"
#include "Ph2Dog.h"
#include "InGameMonsterAnimationControllerComponent.h"
#include "InGameMovementComponent.h"
#include "YarnballShooter.h"
#include "TattooShooter.h"
#include "IInGameCharacterBase.h"
#include "BowWowShooter.h"

Ph2Dog::Ph2Dog()
	: Renderer(nullptr)
	, AttackState(InGameMonsterAttackState::None)
	, Animation(nullptr)
	, Collision(nullptr)
	, RotationAngle(0.0f)
	, State(InGameMonsterState::Idle)
	, Player(nullptr)
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
		Renderer->CreateFrameAnimationFolder("Ph2DogIdle", FrameAnimation_DESC("Ph2DogIdle", 0.1f)); // Idle
		Renderer->CreateFrameAnimationFolder("Ph2DogAttack5", FrameAnimation_DESC("Ph2DogAttack5", 0.1f)); // Idle

		Renderer->AnimationBindEnd("Ph2DogEnter", std::bind(&Ph2Dog::OnEnterAnimationFinished, this, std::placeholders::_1));
		Renderer->AnimationBindEnd("Ph2DogIntro", std::bind(&Ph2Dog::OnPrepareAnimationFinished, this, std::placeholders::_1));
		Renderer->AnimationBindEnd("Ph2DogIdle", std::bind(&Ph2Dog::OnIdleAnimationFinished, this, std::placeholders::_1));
		Renderer->AnimationBindEnd("Ph2DogAttack5", std::bind(&Ph2Dog::OnAttackAnimationFinished, this, std::placeholders::_1));

		Renderer->AnimationBindFrame("Ph2DogEnter", std::bind(&Ph2Dog::OnEnterAnimationFrameChanged, this, std::placeholders::_1));
		Renderer->AnimationBindFrame("Ph2DogIntro", std::bind(&Ph2Dog::OnPreapareAnimationFrameChanged, this, std::placeholders::_1));
		Renderer->AnimationBindFrame("Ph2DogAttack5", std::bind(&Ph2Dog::OnAttackAnimationFrameChanged, this, std::placeholders::_1));

		Renderer->ChangeFrameAnimation("Ph2DogEnter");

		Renderer->GetTransform().SetLocalPosition({ 300, 0, (int)ZOrder::NPC });

		SetRenderer(Renderer);
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
}

void Ph2Dog::Update(float _DeltaTime)
{
	Renderer->ScaleToTexture();
	RotationAngle += _DeltaTime;

	if (GetState() != InGameMonsterState::Prepare &&
		GetState() != InGameMonsterState::Enter)
	{
		GetTransform().SetLocalRotate({ 0, 0, 30 * _DeltaTime});
	}
	else
	{
		RotationAngle = 0.0f;
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
	SetState(InGameMonsterState::Idle);
}

void Ph2Dog::Shoot()
{
	float4 PlayerPos = Player->GetTransform().GetLocalPosition();
	if (GetTransform().GetLocalPosition().x > PlayerPos.x) // 몬스터가 플레이어보다 오른쪽
	{
		if (GetTransform().GetLocalPosition().y > PlayerPos.y) // 몬스터가 플레이어보다 위쪽
		{
			SetBowWowDirection(float4::LEFT + float4::DOWN);
		}
		else
		{
			SetBowWowDirection(float4::LEFT + float4::UP);
		}
	}

	else // 몬스터가 플레이어보다 왼쪽
	{
		if (GetTransform().GetLocalPosition().y > PlayerPos.y) // 몬스터가 플레이어보다 위쪽
		{
			SetBowWowDirection(float4::RIGHT + float4::DOWN);
		}
		else
		{
			SetBowWowDirection(float4::RIGHT + float4::UP);
		}
	}
	SetState(InGameMonsterState::Attack5);
}

void Ph2Dog::Die()
{
	SetState(InGameMonsterState::Die);
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

void Ph2Dog::OnAttackAnimationFrameChanged(const FrameAnimation_DESC& _Info)
{
	if (_Info.CurFrame == 2)
	{
		SetAttackState(InGameMonsterAttackState::BowWow);
	}
	else
	{
		SetAttackState(InGameMonsterAttackState::None);
	}
}

void Ph2Dog::OnEnterAnimationFinished(const FrameAnimation_DESC& _Info)
{
	Prepare();
}

void Ph2Dog::OnPrepareAnimationFinished(const FrameAnimation_DESC& _Info)
{
	Idle();
}

void Ph2Dog::OnIdleAnimationFinished(const FrameAnimation_DESC& _Info)
{
	Shoot();
}

void Ph2Dog::OnAttackAnimationFinished(const FrameAnimation_DESC& _Info)
{
	Idle();
}


