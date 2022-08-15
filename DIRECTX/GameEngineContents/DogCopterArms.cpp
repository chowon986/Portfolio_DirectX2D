#include "PreCompile.h"
#include "DogCopterArms.h"
#include "InGameMonsterAnimationControllerComponent.h"
#include "InGameMovementComponent.h"
#include "IInGameCharacterBase.h"
#include "DogCopter.h"

DogCopterArms::DogCopterArms()
	: Collision(nullptr)
	, Renderer(nullptr)
	, ElapsedTime(-7.0f)
	, AttackIntervalTime(3.0f)
	, CountTimeOnOff(true)
	, WristRenderer(nullptr)
	, State(InGameMonsterState::Idle)
	, AttackState(InGameMonsterAttackState::None)
	, LeaderState(InGameMonsterState::Idle)
	, LeaderAttackState(InGameMonsterAttackState::None)
	, Animation(nullptr)
{
}

DogCopterArms::~DogCopterArms()
{
}

void DogCopterArms::Start()
{
	// 애니메이션 생성
	{
		Renderer = CreateComponent<GameEngineTextureRenderer>();
		WristRenderer = CreateComponent<GameEngineTextureRenderer>();
		LowPadRenderer = CreateComponent<GameEngineTextureRenderer>();
		MidPadRenderer = CreateComponent<GameEngineTextureRenderer>();
		TopPadRenderer = CreateComponent<GameEngineTextureRenderer>();
		PawMergeRenderer = CreateComponent<GameEngineTextureRenderer>();

		Renderer->CreateFrameAnimationFolder("DogCopterIdleArms", FrameAnimation_DESC("DogCopterIdleArms", 0.1f)); // Idle Arms
		WristRenderer->CreateFrameAnimationFolder("DogCopterIdleWrist", FrameAnimation_DESC("DogCopterIdleWrist", 0.1f)); // Idle Wrist

		LowPadRenderer->CreateFrameAnimationFolder("LowPad", FrameAnimation_DESC("LowPad",0,0, 0.1f, false));
		MidPadRenderer->CreateFrameAnimationFolder("MidPad", FrameAnimation_DESC("MidPad",0, 0, 0.1f, false));
		TopPadRenderer->CreateFrameAnimationFolder("TopPad", FrameAnimation_DESC("TopPad",0,0, 0.1f, false));

		Renderer->ChangeFrameAnimation("DogCopterIdleArms");
		//WristRenderer->ChangeFrameAnimation("DogCopterIdleWrist");
		LowPadRenderer->ChangeFrameAnimation("LowPad");
		MidPadRenderer->ChangeFrameAnimation("MidPad");
		TopPadRenderer->ChangeFrameAnimation("TopPad");

		Renderer->GetTransform().SetLocalPosition({ 660, -360, (int)ZOrder::NPC - 1 });
		WristRenderer->GetTransform().SetLocalPosition({ 650, -360, (int)ZOrder::NPC - 1 });

		MidPadRenderer->GetTransform().SetLocalPosition({ 125, -350, (int)ZOrder::NPC - 1 });
		LowPadRenderer->GetTransform().SetLocalPosition({ 177, -560, (int)ZOrder::NPC - 1 });
		TopPadRenderer->GetTransform().SetLocalPosition({ 125, -180, (int)ZOrder::NPC - 1 });


		Renderer->SetScaleModeImage();
		WristRenderer->SetScaleModeImage();
		LowPadRenderer->SetScaleModeImage();
		MidPadRenderer->SetScaleModeImage();
		TopPadRenderer->SetScaleModeImage();

		SetRenderer(Renderer);
	}


	// 컴포넌트 생성
	{
		Animation = CreateComponent<InGameMonsterAnimationControllerComponent>();
		Animation->SetMonsterName("DogCopterArms");
	}

	srand(static_cast<unsigned int>(time(NULL)));
	SetHP(5);
	SetState(InGameMonsterState::Idle);
	SetAttackState(InGameMonsterAttackState::None);
}

void DogCopterArms::Update(float _DeltaTime)
{

	//if (CountTimeOnOff == true)
	//{
	//	ElapsedTime += _DeltaTime;
	//}

	//if (ElapsedTime >= AttackIntervalTime)
	//{
	//	ElapsedTime = 0.0f;
	//	CountTimeOnOff = false;
	//	Shoot();
	//}

	if (GetParent() != nullptr)
	{
		IInGameMonsterBase* LeaderCopterBase = dynamic_cast<IInGameMonsterBase*>(GetParent());
		LeaderState = LeaderCopterBase->GetState();

		if (LeaderState == InGameMonsterState::Idle)
		{
			Idle();
		}
		//else if(LeaderState == InGameMonsterState::)
	}
}

void DogCopterArms::TakeDamage()
{
}

void DogCopterArms::Prepare()
{
}

void DogCopterArms::Idle()
{
	SetState(InGameMonsterState::Idle);
}

void DogCopterArms::Shoot()
{
}

void DogCopterArms::Die()
{
	SetState(InGameMonsterState::Die);
}
