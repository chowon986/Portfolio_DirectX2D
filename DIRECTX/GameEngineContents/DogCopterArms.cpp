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
		LeftLowPadRenderer = CreateComponent<GameEngineTextureRenderer>();
		LeftMidPadRenderer = CreateComponent<GameEngineTextureRenderer>();
		LeftTopPadRenderer = CreateComponent<GameEngineTextureRenderer>();
		RightLowPadRenderer = CreateComponent<GameEngineTextureRenderer>();
		RightMidPadRenderer = CreateComponent<GameEngineTextureRenderer>();
		RightTopPadRenderer = CreateComponent<GameEngineTextureRenderer>();
		PawMergeRenderer = CreateComponent<GameEngineTextureRenderer>();
		LeftHandRenderer = CreateComponent<GameEngineTextureRenderer>();
		RightHandRenderer = CreateComponent<GameEngineTextureRenderer>();
		LaserTopRenderer = CreateComponent<GameEngineTextureRenderer>();

		Renderer->CreateFrameAnimationFolder("DogCopterIdleArms", FrameAnimation_DESC("DogCopterIdleArms", 0.1f)); // Idle Arms
		WristRenderer->CreateFrameAnimationFolder("DogCopterIdleWrist", FrameAnimation_DESC("DogCopterIdleWrist", 0.1f)); // Idle Wrist

		LeftLowPadRenderer->CreateFrameAnimationFolder("LowPadOpen", FrameAnimation_DESC("LowPad", 0.1f, false));
		LeftMidPadRenderer->CreateFrameAnimationFolder("MidPadOPen", FrameAnimation_DESC("MidPad", 0.1f, false));
		LeftTopPadRenderer->CreateFrameAnimationFolder("TopPadOpen", FrameAnimation_DESC("TopPad", 0.1f, false));
		RightLowPadRenderer->CreateFrameAnimationFolder("LowPadOpen", FrameAnimation_DESC("LowPad", 0.1f, false));
		RightMidPadRenderer->CreateFrameAnimationFolder("MidPadOPen", FrameAnimation_DESC("MidPad", 0.1f, false));
		RightTopPadRenderer->CreateFrameAnimationFolder("TopPadOpen", FrameAnimation_DESC("TopPad", 0.1f, false));
		LeftHandRenderer->CreateFrameAnimationFolder("PawMerge", FrameAnimation_DESC("PawMerge", 0.1f, false));
		RightHandRenderer->CreateFrameAnimationFolder("PawMerge", FrameAnimation_DESC("PawMerge", 0.1f, false));
		LaserTopRenderer->CreateFrameAnimationFolder("LaserTop", FrameAnimation_DESC("LaserTop", 0.1f, false));

		Renderer->ChangeFrameAnimation("DogCopterIdleArms");
		WristRenderer->ChangeFrameAnimation("DogCopterIdleWrist");
		LeftLowPadRenderer->ChangeFrameAnimation("LowPad");
		LeftMidPadRenderer->ChangeFrameAnimation("MidPad");
		LeftTopPadRenderer->ChangeFrameAnimation("TopPad");
		RightLowPadRenderer->ChangeFrameAnimation("LowPad");
		RightMidPadRenderer->ChangeFrameAnimation("MidPad");
		RightTopPadRenderer->ChangeFrameAnimation("TopPad");
		LeftHandRenderer->ChangeFrameAnimation("PawMerge");
		RightHandRenderer->ChangeFrameAnimation("PawMerge");
		LaserTopRenderer->ChangeFrameAnimation("LaserTop");

		Renderer->GetTransform().SetLocalPosition({ 650, -360, (int)ZOrder::NPC });
		WristRenderer->GetTransform().SetLocalPosition({ 650, -360, (int)ZOrder::NPC - 1 });

		LeftTopPadRenderer->GetTransform().SetLocalPosition({ 195, -145, (int)ZOrder::NPC - 3 });
		LeftMidPadRenderer->GetTransform().SetLocalPosition({ 125, -350, (int)ZOrder::NPC - 3 });
		LeftLowPadRenderer->GetTransform().SetLocalPosition({ 176, -559, (int)ZOrder::NPC - 3 });

		RightTopPadRenderer->GetTransform().SetLocalPosition({ 1110, -129, (int)ZOrder::NPC - 4 });
		RightMidPadRenderer->GetTransform().SetLocalPosition({ 1180, -338, (int)ZOrder::NPC - 4 });
		RightLowPadRenderer->GetTransform().SetLocalPosition({ 1125, -540, (int)ZOrder::NPC - 4 });
		
		LeftHandRenderer->GetTransform().SetLocalPosition({ 125, -360, (int)ZOrder::NPC - 2 });
		RightHandRenderer->GetTransform().SetLocalPosition({ 1180, -340, (int)ZOrder::NPC - 2 });

		LaserTopRenderer->GetTransform().SetLocalPosition({ 195, -145, (int)ZOrder::NPC - 3 });

		Renderer->SetScaleModeImage();
		WristRenderer->SetScaleModeImage();
		LeftLowPadRenderer->SetScaleModeImage();
		LeftMidPadRenderer->SetScaleModeImage();
		LeftTopPadRenderer->SetScaleModeImage();
		RightLowPadRenderer->SetScaleModeImage();
		RightMidPadRenderer->SetScaleModeImage();
		RightTopPadRenderer->SetScaleModeImage();
		LeftHandRenderer->SetScaleModeImage();
		RightHandRenderer->SetScaleModeImage();
		LaserTopRenderer->SetScaleModeImage();

		RightLowPadRenderer->GetTransform().PixLocalNegativeX();
		RightMidPadRenderer->GetTransform().PixLocalNegativeX();
		RightTopPadRenderer->GetTransform().PixLocalNegativeX();
		RightHandRenderer->GetTransform().PixLocalNegativeX();

		SetRenderer(Renderer);
	}


	// 컴포넌트 생성
	{
		Animation = CreateComponent<InGameMonsterAnimationControllerComponent>();
		Animation->SetMonsterName("DogCopterArms");
	}

	srand(static_cast<unsigned int>(time(NULL)));
	SetHP(5);
	//SetState(InGameMonsterState::Idle);
	//SetAttackState(InGameMonsterAttackState::None);
}

void DogCopterArms::Update(float _DeltaTime)
{
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
