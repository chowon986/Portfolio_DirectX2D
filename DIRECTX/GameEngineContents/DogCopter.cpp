#include "PreCompile.h"
#include "DogCopter.h"
#include "DogCopterArms.h"
#include "InGameMonsterAnimationControllerComponent.h"

DogCopter::DogCopter()
	:Renderer(nullptr)
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
		Renderer->CreateFrameAnimationFolder("DogCopterIntro", FrameAnimation_DESC("DogCopterIntro", 0.1f, false));
		Renderer->CreateFrameAnimationFolder("DogCopterIdle", FrameAnimation_DESC("DogCopterIdle", 0.1f));

		// Test
		Renderer->AnimationBindEnd("DogCopterIntro", std::bind(&DogCopter::OnTestAnimationFrameEnd, this, std::placeholders::_1));
		Renderer->AnimationBindFrame("DogCopterIdle", std::bind(&DogCopter::OnTestAnimationFrameChanged, this, std::placeholders::_1));

		Renderer->ChangeFrameAnimation("DogCopterIntro");
		Renderer->GetTransform().SetLocalPosition({ 640, -360, (int)ZOrder::NPC - 1 });
		Renderer->SetScaleModeImage();

		SetState(InGameMonsterState::Prepare);
		SetRenderer(Renderer);
	}

	Animation = CreateComponent<InGameMonsterAnimationControllerComponent>();
	Animation->SetMonsterName("DogCopter");
}

void DogCopter::Update(float _DeltaTime)
{
	if (CopterArms == nullptr)
	{
		CopterArms = GetLevel()->CreateActor<DogCopterArms>();
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

void DogCopter::OnTestAnimationFrameChanged(const FrameAnimation_DESC& _Info)
{
	// Test
	if (_Info.CurFrame == 4)
	{

	}
}

void DogCopter::OnTestAnimationFrameEnd(const FrameAnimation_DESC& _Info)
{
	//Renderer->GetTransform().SetLocalPosition({ Renderer->GetTransform().GetLocalPosition().x, Renderer->GetTransform().GetLocalPosition().y + 100 });
	//Idle();
}
