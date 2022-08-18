#include "PreCompile.h"
#include "DogCopter.h"
#include "DogCopterArms.h"
#include "InGameMonsterAnimationControllerComponent.h"

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
		Renderer->CreateFrameAnimationFolder("DogCopterRotateCamera", FrameAnimation_DESC("DogCopterRotateCamera", 0.1f));
		Renderer->CreateFrameAnimationFolder("DogCopterRotatedIdle", FrameAnimation_DESC("DogCopterRotatedIdle", 0.1f));
		Renderer->CreateFrameAnimationFolder("DogCopterRotateCameraOut", FrameAnimation_DESC("DogCopterRotateCameraOut", 0.1f));

		// Test
		Renderer->AnimationBindEnd("DogCopterIntro", std::bind(&DogCopter::OnIntroAnimationFrameFinished, this, std::placeholders::_1));

		Renderer->ChangeFrameAnimation("DogCopterIntro");
		Renderer->SetScaleModeImage();
		Renderer->GetTransform().SetLocalPosition({ 640, -360, (int)ZOrder::NPC - 1 });

		SetState(InGameMonsterState::Prepare);
		SetRenderer(Renderer);
	}

	Animation = CreateComponent<InGameMonsterAnimationControllerComponent>();
	Animation->SetMonsterName("DogCopter");
}

void DogCopter::Update(float _DeltaTime)
{
	//if (false == MoveDirection.CompareInt2D(float4::ZERO))
	//{
	//	if (false == IsEndPosArrived())
	//	{
	//		GetTransform().SetWorldMove(MoveDirection * MoveSpeed * GameEngineTime::GetDeltaTime());
	//	}
	//}
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
	if (CopterArms == nullptr && GetDogCopterState() == InGameDogCopterState::Idle)
	{
		CopterArms = GetLevel()->CreateActor<DogCopterArms>();
	}

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

void DogCopter::OnIntroAnimationFrameFinished(const FrameAnimation_DESC& _Info)
{
	Idle();
}
