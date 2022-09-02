#include "PreCompile.h"
#include "DogCopter.h"
#include "InGameDogCopterAnimationControllerComponent.h"
#include "DogCopterShooter.h"
#include "DogBowlShooter.h"

DogCopter::DogCopter()
	: Renderer(nullptr)
	, Leader(nullptr)
{
}

DogCopter::~DogCopter()
{
}

void DogCopter::Start()
{
	IInGameMonsterBase::Start();
	{
		Renderer = CreateComponent<GameEngineTextureRenderer>();
		Renderer->CreateFrameAnimationFolder("DogCopterIntro", FrameAnimation_DESC("DogCopterIntro",0, 44, 0.1f, false));
		Renderer->CreateFrameAnimationFolder("DogCopterIdle", FrameAnimation_DESC("DogCopterIdle", 0.1f));
		Renderer->CreateFrameAnimationFolder("DogCopterAttack1", FrameAnimation_DESC("DogCopterIdle", 0.1f));
		Renderer->CreateFrameAnimationFolder("DogCopterRotateCamera", FrameAnimation_DESC("DogCopterRotateCamera", 0.1f));
		Renderer->CreateFrameAnimationFolder("DogCopterRotatedIdle", FrameAnimation_DESC("DogCopterRotatedIdle", 0.1f));
		Renderer->CreateFrameAnimationFolder("DogCopterAttack2", FrameAnimation_DESC("DogCopterRotatedIdle", 0.1f));
		Renderer->CreateFrameAnimationFolder("DogCopterRotateCameraOut", FrameAnimation_DESC("DogCopterRotateCameraOut", 0.1f));

		Renderer->AnimationBindEnd("DogCopterIntro", std::bind(&DogCopter::OnIntroAnimationFrameFinished, this, std::placeholders::_1));
		Renderer->AnimationBindFrame("DogCopterIntro", std::bind(&DogCopter::Test, this, std::placeholders::_1));
		Renderer->AnimationBindFrame("DogCopterIntro", std::bind(&DogCopter::Test, this, std::placeholders::_1));
		Renderer->AnimationBindEnd("DogCopterRotateCamera", std::bind(&DogCopter::OnRotateCameraAnimationFrameFinished, this, std::placeholders::_1));
		Renderer->AnimationBindEnd("DogCopterRotatedIdle", std::bind(&DogCopter::OnRotatedIdleAnimationFrameFinished, this, std::placeholders::_1));
		Renderer->AnimationBindFrame("DogCopterRotatedIdle", std::bind(&DogCopter::Test, this, std::placeholders::_1));
		//Renderer->AnimationBindFrame("DogCopterRotateCamera", std::bind(&DogCopter::Test, this, std::placeholders::_1));
		Renderer->AnimationBindEnd("DogCopterRotateCameraOut", std::bind(&DogCopter::OnRotateCameraOutAnimationFrameFinished, this, std::placeholders::_1));
	
		Renderer->AnimationBindFrame("DogCopterIdle", std::bind(&DogCopter::OnIdleAnimationFrameChanged, this, std::placeholders::_1));
		Renderer->AnimationBindFrame("DogCopterRotateCameraOut", std::bind(&DogCopter::OnRotateCameraOutAnimationFrameChanged, this, std::placeholders::_1));
		Renderer->AnimationBindFrame("DogCopterRotateCamera", std::bind(&DogCopter::OnRotateCameraAnimationFrameChanged, this, std::placeholders::_1));

		Renderer->ChangeFrameAnimation("DogCopterIntro");
		Renderer->SetScaleModeImage();
		Renderer->GetTransform().SetLocalPosition({ 640, -360, (int)ZOrder::NPC - 1 });

		SetState(InGameMonsterState::Prepare);
		SetRenderer(Renderer);
	}

	{
		ArmsRenderer = CreateComponent<GameEngineTextureRenderer>();
		ArmsRenderer->CreateFrameAnimationFolder("DogCopterIdleArms", FrameAnimation_DESC("DogCopterIdleArms", 0.1f));
		ArmsRenderer->CreateFrameAnimationFolder("Nothing", FrameAnimation_DESC("Nothing", 0.1f));
		ArmsRenderer->ChangeFrameAnimation("DogCopterIdleArms");
		ArmsRenderer->SetScaleModeImage();
		ArmsRenderer->GetTransform().SetLocalPosition({ 650, -410, (int)ZOrder::NPC });
		ArmsRenderer->Off();
	}

	{
		WristRenderer = CreateComponent<GameEngineTextureRenderer>();
		WristRenderer->CreateFrameAnimationFolder("DogCopterIdleWrist", FrameAnimation_DESC("DogCopterIdleWrist", 0.1f)); // Idle Wrist
		WristRenderer->CreateFrameAnimationFolder("Nothing", FrameAnimation_DESC("Nothing", 0.1f)); // Idle Wrist
		WristRenderer->ChangeFrameAnimation("DogCopterIdleWrist");
		WristRenderer->SetScaleModeImage();
		WristRenderer->GetTransform().SetLocalPosition({ 650, -360, (int)ZOrder::NPC - 1 });
		WristRenderer->Off();
	}

	{
		LeftHandRenderer = CreateComponent<GameEngineTextureRenderer>();
		LeftHandRenderer->CreateFrameAnimationFolder("PawMerge", FrameAnimation_DESC("PawMerge", 0.1f));
		LeftHandRenderer->CreateFrameAnimationFolder("Nothing", FrameAnimation_DESC("Nothing", 0.1f));
		LeftHandRenderer->ChangeFrameAnimation("PawMerge");
		LeftHandRenderer->SetScaleModeImage();
		LeftHandRenderer->GetTransform().SetLocalPosition({ 125, -360, (int)ZOrder::NPC - 2 });
		LeftHandRenderer->Off();

		RightHandRenderer = CreateComponent<GameEngineTextureRenderer>();
		RightHandRenderer->CreateFrameAnimationFolder("PawMerge", FrameAnimation_DESC("PawMerge", 0.1f));
		RightHandRenderer->CreateFrameAnimationFolder("Nothing", FrameAnimation_DESC("Nothing", 0.1f));
		RightHandRenderer->ChangeFrameAnimation("PawMerge");
		RightHandRenderer->SetScaleModeImage();
		RightHandRenderer->GetTransform().SetLocalPosition({ 1180, -340, (int)ZOrder::NPC - 2 });
		RightHandRenderer->GetTransform().PixLocalNegativeX();
		RightHandRenderer->Off();

		GetLevel()->PushRendererToRotateCamera2(LeftHandRenderer);
		GetLevel()->PushRendererToRotateCamera2(RightHandRenderer);
	}

	{
		InGameDogCopterAnimationControllerComponent* Animation = CreateComponent<InGameDogCopterAnimationControllerComponent>();
		Animation->SetMonsterName("DogCopter");

		DogCopterShooter* LaserShooter = GetLevel()->CreateActor<DogCopterShooter>();
		LaserShooter->SetParent(this);

		DogBowlShooter* BowlShooter = GetLevel()->CreateActor<DogBowlShooter>();
		BowlShooter->SetParent(this);
	}

	srand(time(NULL));
	
	Collision = CreateComponent<GameEngineCollision>();
	Collision->GetTransform().SetWorldScale({ 300.0f,300.0f,1.0f });
	Collision->GetTransform().SetWorldPosition({ 640.0f, -360.0f });
	SetHP(1);
}

void DogCopter::Update(float _DeltaTime)
{
	if (GetState() != InGameMonsterState::Prepare)
	{
		if (Collision->IsCollision(CollisionType::CT_AABB2D, ObjectOrder::PC_BULLET, CollisionType::CT_AABB2D, std::bind(&DogCopter::OnTakeDamage, this, std::placeholders::_1, std::placeholders::_2)))
		{
			SetHP(GetHP() - 1);
			if (GetHP() <= 0)
			{
				//Death();
				GEngine::ChangeLevel("WorldMap");
			}
		}
	}

	if (GetState() == InGameMonsterState::BeforeRotateCameraIn)
	{
		ArmsRenderer->ChangeFrameAnimation("Nothing");
		ArmsRenderer->Off();

		WristRenderer->ChangeFrameAnimation("Nothing");
		WristRenderer->Off();

		RotateCameraIn();
	}
}

void DogCopter::End()
{
}

void DogCopter::Prepare()
{
	int a = 0;
}

void DogCopter::Idle()
{
	SetState(InGameMonsterState::Idle);
}

void DogCopter::TakeDamage()
{
}

void DogCopter::Shoot()
{
}

void DogCopter::Die()
{
}

void DogCopter::Attack1()
{
	SetState(InGameMonsterState::Attack1);
}


void DogCopter::Attack2()
{
	SetState(InGameMonsterState::Attack2);
}

void DogCopter::RotateCameraIn()
{
	SetState(InGameMonsterState::RotateCameraIn);
}

void DogCopter::RotateCameraOut()
{
	SetState(InGameMonsterState::RotateCameraOut);
}

void DogCopter::RotateCameraIdle()
{
	SetState(InGameMonsterState::RotateCameraIdle);
}

void DogCopter::BeforeRoateCameraIn()
{
	SetState(InGameMonsterState::BeforeRotateCameraIn);
}

bool DogCopter::OnTakeDamage(GameEngineCollision* _This, GameEngineCollision* _Other)
{
	return true;
}


void DogCopter::OnIntroAnimationFrameFinished(const FrameAnimation_DESC& _Info)
{
	ArmsRenderer->ChangeFrameAnimation("DogCopterIdleArms");
	ArmsRenderer->On();
	WristRenderer->ChangeFrameAnimation("DogCopterIdleWrist");
	WristRenderer->On();
	LeftHandRenderer->ChangeFrameAnimation("PawMerge");
	LeftHandRenderer->On();
	RightHandRenderer->ChangeFrameAnimation("PawMerge");
	RightHandRenderer->On();

	Idle();
}

void DogCopter::OnIdleAnimationFrameChanged(const FrameAnimation_DESC& _Info)
{
	if (_Info.CurFrame == 6)
	{
		Attack1();
	}
}


void DogCopter::OnRotateCameraAnimationFrameFinished(const FrameAnimation_DESC& _Info)
{
	RotateCameraIdle();
}

void DogCopter::OnRotatedIdleAnimationFrameFinished(const FrameAnimation_DESC& _Info)
{
	RotateCameraOut();
	//Attack2();
}

void DogCopter::OnRotateCameraOutAnimationFrameFinished(const FrameAnimation_DESC& _Info)
{
	Renderer->GetTransform().SetLocalRotate({ 0,0,180 });
	ArmsRenderer->ChangeFrameAnimation("DogCopterIdleArms");
	ArmsRenderer->On();
	WristRenderer->ChangeFrameAnimation("DogCopterIdleWrist");
	WristRenderer->On();
	Idle();
}

void DogCopter::OnRotateCameraAnimationFrameChanged(const FrameAnimation_DESC& _Info)
{
	if (_Info.CurFrame == 11)
	{
		LeftHandRenderer->ChangeFrameAnimation("Nothing");
		LeftHandRenderer->Off();
		RightHandRenderer->ChangeFrameAnimation("Nothing");
		RightHandRenderer->Off();
	}
}

void DogCopter::OnRotateCameraOutAnimationFrameChanged(const FrameAnimation_DESC& _Info)
{
	int a = 0;
	if (_Info.CurFrame == 14)
	{
		LeftHandRenderer->ChangeFrameAnimation("PawMerge");
		LeftHandRenderer->On();
		RightHandRenderer->ChangeFrameAnimation("PawMerge");
		RightHandRenderer->On();
	}
}

void DogCopter::Test(const FrameAnimation_DESC& _Info)
{
	int a = 0;
}
