#include "PreCompile.h"
#include "Canteen.h"
#include "InGameMonsterAnimationControllerComponent.h"
#include "InGameMovementComponent.h"
#include "YarnballShooter.h"
#include "TattooShooter.h"
#include "IInGameCharacterBase.h"
#include "BowWowShooter.h"

Canteen::Canteen()
	: Renderer(nullptr)
	, AttackState(InGameMonsterAttackState::None)
	, Animation(nullptr)
	, Collision(nullptr)
{
}

Canteen::~Canteen()
{
}

void Canteen::Start()
{
	// 애니메이션 순서 : Intro -> Idle -> Blink -> 
	{
		Renderer = CreateComponent<GameEngineTextureRenderer>();
		Renderer->CreateFrameAnimationFolder("CanteenIntro", FrameAnimation_DESC("CanteenIntro", 0.2f)); // Prepare
		Renderer->CreateFrameAnimationFolder("CanteenIdle", FrameAnimation_DESC("CanteenIdle", 0.2f)); // Idle
		Renderer->CreateFrameAnimationFolder("CanteenBlink", FrameAnimation_DESC("CanteenBlink", 0.2f)); // Blink
		Renderer->CreateFrameAnimationFolder("CanteenCheer", FrameAnimation_DESC("CanteenCheer", 0.2f)); // phase 바뀌면
		Renderer->CreateFrameAnimationFolder("CanteenLookAround", FrameAnimation_DESC("CanteenLookAround", 0.2f)); // 움직이면 ? 또는 blink 끝나면?
		Renderer->CreateFrameAnimationFolder("CanteenLookUp", FrameAnimation_DESC("CanteenLookUp", 0.2f)); // 움직이다 멈추면

		Renderer->CreateFrameAnimationFolder("CanteenLookUpLeft", FrameAnimation_DESC("CanteenLookUpLeft", 0.2f)); 
		Renderer->CreateFrameAnimationFolder("CanteenLookUpLeftArchUp", FrameAnimation_DESC("CanteenLookUpLeftArchUp", 0.2f)); 
		Renderer->CreateFrameAnimationFolder("CanteenLookUpRight", FrameAnimation_DESC("CanteenLookUpRight", 0.2f));
		Renderer->CreateFrameAnimationFolder("CanteenLookUpRightArchUp", FrameAnimation_DESC("CanteenLookUpRightArchUp", 0.2f)); 
		Renderer->CreateFrameAnimationFolder("CanteenTakeDamage", FrameAnimation_DESC("CanteenTakeDamage", 0.2f)); 
		Renderer->CreateFrameAnimationFolder("CanteenWin", FrameAnimation_DESC("CanteenWin", 0.2f));

		Renderer->CreateFrameAnimationFolder("CanteenLookDown", FrameAnimation_DESC("CanteenLookDown", 0.2f)); // phase 2
		Renderer->CreateFrameAnimationFolder("CanteenLookDownLeft", FrameAnimation_DESC("CanteenLookDownLeft", 0.2f)); // phase 2
		Renderer->CreateFrameAnimationFolder("CanteenLookDownRight", FrameAnimation_DESC("CanteenLookDownRight", 0.2f)); // phase2

		Renderer->AnimationBindEnd("CanteenIntro", std::bind(&Canteen::OnPrepareAnimationFinished, this, std::placeholders::_1));
		Renderer->AnimationBindEnd("CanteenIdle", std::bind(&Canteen::OnIdleAnimationFinished, this, std::placeholders::_1));
		Renderer->AnimationBindEnd("CanteenBlink", std::bind(&Canteen::OnBlinkAnimationFinished, this, std::placeholders::_1));

		Renderer->AnimationBindEnd("CanteenLookAround", std::bind(&Canteen::OnLookAnimationFinished, this, std::placeholders::_1));
		Renderer->AnimationBindEnd("CanteenLookUp", std::bind(&Canteen::OnLookAnimationFinished, this, std::placeholders::_1));
		Renderer->AnimationBindEnd("CanteenLookUpLeft", std::bind(&Canteen::OnLookAnimationFinished, this, std::placeholders::_1));
		Renderer->AnimationBindEnd("CanteenLookUpLeftArchUp", std::bind(&Canteen::OnLookAnimationFinished, this, std::placeholders::_1));
		Renderer->AnimationBindEnd("CanteenLookUpRight", std::bind(&Canteen::OnLookAnimationFinished, this, std::placeholders::_1));
		Renderer->AnimationBindEnd("CanteenLookUpRightArchUp", std::bind(&Canteen::OnLookAnimationFinished, this, std::placeholders::_1));
		Renderer->AnimationBindEnd("CanteenLookDown", std::bind(&Canteen::OnLookAnimationFinished, this, std::placeholders::_1));
		Renderer->AnimationBindEnd("CanteenLookDownLeft", std::bind(&Canteen::OnLookAnimationFinished, this, std::placeholders::_1));
		Renderer->AnimationBindEnd("CanteenLookDownRight", std::bind(&Canteen::OnLookAnimationFinished, this, std::placeholders::_1));


		Renderer->ChangeFrameAnimation("CanteenIntro");
	
		SetRenderer(Renderer);
		SetState(InGameMonsterState::Prepare);
	}

	// 컴포넌트 생성
	{
		Animation = CreateComponent<InGameMonsterAnimationControllerComponent>();
		Animation->SetMonsterName("Canteen");
	}

	srand(time(NULL));
}

void Canteen::Update(float _DeltaTime)
{
	Renderer->ScaleToTexture();
}

void Canteen::TakeDamage()
{
	SetState(InGameMonsterState::TakeDamage);
}

void Canteen::Prepare()
{
	SetState(InGameMonsterState::Prepare);
}

void Canteen::Idle()
{
	SetState(InGameMonsterState::Idle);
}

void Canteen::Shoot()
{
}

void Canteen::Die()
{
	SetState(InGameMonsterState::Die);
}

void Canteen::Blink()
{
	SetState(InGameMonsterState::Blink);
}

void Canteen::Look()
{
	SetState(InGameMonsterState::Look);
}

void Canteen::OnPrepareAnimationFinished(const FrameAnimation_DESC& _Info)
{
	Idle();
}

void Canteen::OnIdleAnimationFinished(const FrameAnimation_DESC& _Info)
{
	Blink();
}

void Canteen::OnBlinkAnimationFinished(const FrameAnimation_DESC& _Info)
{
	Look();
}

void Canteen::OnLookAnimationFinished(const FrameAnimation_DESC& _Info)
{
	Idle();
}
