#include "PreCompile.h"
#include "DogCopter.h"
#include "DogCopterArms.h"
#include "LaserShooter.h"
#include "InGameDogCopterAnimationControllerComponent.h"

DogCopter::DogCopter()
	:Renderer(nullptr)
	, CopterArms(nullptr)
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
		Renderer->CreateFrameAnimationFolder("DogCopterIntro", FrameAnimation_DESC("DogCopterIntro",0,29, 0.1f, false));
		Renderer->CreateFrameAnimationFolder("DogCopterIdle", FrameAnimation_DESC("DogCopterIdle", 0.1f));
		Renderer->CreateFrameAnimationFolder("DogCopterAttack1", FrameAnimation_DESC("DogCopterIdle", 0.1f));
		Renderer->CreateFrameAnimationFolder("DogCopterRotateCamera", FrameAnimation_DESC("DogCopterRotateCamera", 0.1f));
		Renderer->CreateFrameAnimationFolder("DogCopterRotatedIdle", FrameAnimation_DESC("DogCopterRotatedIdle", 0.1f));
		Renderer->CreateFrameAnimationFolder("DogCopterAttack2", FrameAnimation_DESC("DogCopterRotatedIdle", 0.1f));
		Renderer->CreateFrameAnimationFolder("DogCopterRotateCameraOut", FrameAnimation_DESC("DogCopterRotateCameraOut", 0.1f));

		// Test
		Renderer->AnimationBindEnd("DogCopterIntro", std::bind(&DogCopter::OnIntroAnimationFrameFinished, this, std::placeholders::_1));
		Renderer->AnimationBindEnd("DogCopterIdle", std::bind(&DogCopter::OnIdleAnimationFrameFinished, this, std::placeholders::_1));
		Renderer->AnimationBindEnd("DogCopterAttack1", std::bind(&DogCopter::OnAttack1AnimationFrameFinished, this, std::placeholders::_1));
		Renderer->AnimationBindEnd("DogCopterRotateCamera", std::bind(&DogCopter::OnRotateCameraAnimationFrameFinished, this, std::placeholders::_1));
		Renderer->AnimationBindEnd("DogCopterRotatedIdle", std::bind(&DogCopter::OnRotatedIdleAnimationFrameFinished, this, std::placeholders::_1));
		Renderer->AnimationBindEnd("DogCopterAttack2", std::bind(&DogCopter::OnAttack2AnimationFrameFinished, this, std::placeholders::_1));
		Renderer->AnimationBindEnd("DogCopterRotateCameraOut", std::bind(&DogCopter::OnRotateCameraOutAnimationFrameFinished, this, std::placeholders::_1));

		Renderer->AnimationBindFrame("DogCopterAttack1", std::bind(&DogCopter::OnAttack1AnimationFrameChanged, this, std::placeholders::_1));

		Renderer->ChangeFrameAnimation("DogCopterIntro");
		Renderer->SetScaleModeImage();
		Renderer->GetTransform().SetLocalPosition({ 640, -360, (int)ZOrder::NPC - 1 });

		SetState(InGameMonsterState::Prepare);
		SetRenderer(Renderer);
	}

	Animation = CreateComponent<InGameDogCopterAnimationControllerComponent>();
	Animation->SetMonsterName("DogCopter");

	LaserShooter* Laser = GetLevel()->CreateActor<LaserShooter>();
	Laser->SetParent(this);

	srand(time(NULL));

}

void DogCopter::Update(float _DeltaTime)
{

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
	SetDogCopterState(InGameDogCopterState::Idle);
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
	SetDogCopterState(InGameDogCopterState::Attack1);
}

void DogCopter::Attack2()
{
	SetDogCopterState(InGameDogCopterState::Attack2);
}

void DogCopter::RotateCameraIn()
{
	SetDogCopterState(InGameDogCopterState::RotateCameraIn);
}

void DogCopter::RotateCameraOut()
{
	SetDogCopterState(InGameDogCopterState::RotateCameraOut);
}

void DogCopter::RotateCameraIdle()
{
	SetDogCopterState(InGameDogCopterState::RotateCameraIdle);
}


void DogCopter::OnIntroAnimationFrameFinished(const FrameAnimation_DESC& _Info)
{
	if (CopterArms == nullptr)
	{
		CopterArms = GetLevel()->CreateActor<DogCopterArms>();
	}
	Idle();
}

void DogCopter::OnIdleAnimationFrameFinished(const FrameAnimation_DESC& _Info)
{
	Attack1();
}

void DogCopter::OnAttack1AnimationFrameFinished(const FrameAnimation_DESC& _Info)
{
	/*if (CopterArms != nullptr)
	{
		CopterArms->Death();
		CopterArms = nullptr;
	}*/
	// 손에서 공격이 끝나면 RotateCameraIn();
}

void DogCopter::OnRotateCameraAnimationFrameFinished(const FrameAnimation_DESC& _Info)
{
	RotateCameraIdle();
}

void DogCopter::OnRotatedIdleAnimationFrameFinished(const FrameAnimation_DESC& _Info)
{
	Attack2();
}

void DogCopter::OnAttack2AnimationFrameFinished(const FrameAnimation_DESC& _Info)
{
	RotateCameraOut();
}

void DogCopter::OnRotateCameraOutAnimationFrameFinished(const FrameAnimation_DESC& _Info)
{
	Renderer->GetTransform().SetLocalRotate({ 0,0,180 });
	Idle();
}

void DogCopter::OnAttack1AnimationFrameChanged(const FrameAnimation_DESC& _Info)
{
	if (_Info.CurFrame == 6)
	{
		SetAttackState(InGameMonsterAttackState::LaserPattern1);
			//int RandomAttack = rand() % 3;
		// if(RandomAttack == 1)
		//{

		//}

	}
}
