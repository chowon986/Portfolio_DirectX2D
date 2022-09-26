#include "PreCompile.h"
#include "SaltBakerHand.h"
#include "SaltBaker.h"

SaltBakerHand::SaltBakerHand()
{
}

SaltBakerHand::~SaltBakerHand()
{
}

void SaltBakerHand::Start()
{
	Renderer = CreateComponent<GameEngineTextureRenderer>();
	Renderer->CreateFrameAnimationFolder("SaltBakerHandDeath", FrameAnimation_DESC("SaltBakerHandDeath", 0.07f));
	Renderer->CreateFrameAnimationFolder("SaltBakerHandIdle", FrameAnimation_DESC("SaltBakerHandIdle", 0.07f));
	Renderer->CreateFrameAnimationFolder("SaltBakerHandTakeDamage", FrameAnimation_DESC("SaltBakerHandTakeDamage", 0.07f));
	Renderer->SetScaleModeImage();
	Renderer->ChangeFrameAnimation("SaltBakerHandIdle");

	Renderer->GetTransform().SetLocalPosition({ 0.0f, -380.0f });
	Renderer->ChangeCamera(CAMERAORDER::ROTATECAMERA);

	TopperRenderer = CreateComponent<GameEngineTextureRenderer>();
	TopperRenderer->CreateFrameAnimationFolder("SaltBakerHandDeathTopper", FrameAnimation_DESC("SaltBakerHandDeathTopper", 0.07f));
	TopperRenderer->CreateFrameAnimationFolder("SaltBakerHandIdleTopper", FrameAnimation_DESC("SaltBakerHandIdleTopper", 0.07f));
	TopperRenderer->CreateFrameAnimationFolder("SaltBakerHandTakeDamageTopper", FrameAnimation_DESC("SaltBakerHandTakeDamageTopper", 0.07f));
	TopperRenderer->SetScaleModeImage();
	TopperRenderer->ChangeFrameAnimation("SaltBakerHandIdleTopper");

	TopperRenderer->GetTransform().SetLocalPosition({ -380.0f, -450.0f});

	TopperRenderer->ChangeCamera(CAMERAORDER::ROTATECAMERA);

	Renderer->AnimationBindFrame("SaltBakerHandDeath", std::bind(&SaltBakerHand::OnSaltBakerHandDeathAnimationFrameChanged, this, std::placeholders::_1));

}

void SaltBakerHand::Update(float _DeltaTime)
{
	if (SaltBaker* Boss = dynamic_cast<SaltBaker*>(GetParent()))
	{
		if (Boss->GetState() == InGameMonsterState::TakeDamage)
		{
			Renderer->ChangeFrameAnimation("SaltBakerHandTakeDamage");
			TopperRenderer->ChangeFrameAnimation("SaltBakerHandTakeDamageTopper");
		}

		else if (Boss->GetState() == InGameMonsterState::Idle)
		{
			Renderer->ChangeFrameAnimation("SaltBakerHandIdle");
			TopperRenderer->ChangeFrameAnimation("SaltBakerHandIdleTopper");
		}

		else if (Boss->GetState() == InGameMonsterState::Die)
		{
			Renderer->ChangeFrameAnimation("SaltBakerHandDeath");
			TopperRenderer->ChangeFrameAnimation("SaltBakerHandIdleTopper");
		}
	}
}

void SaltBakerHand::TakeDamage()
{
}

void SaltBakerHand::Prepare()
{
}

void SaltBakerHand::Idle()
{
}

void SaltBakerHand::Shoot()
{
}

void SaltBakerHand::Die()
{
}

void SaltBakerHand::OnSaltBakerHandDeathAnimationFrameChanged(const FrameAnimation_DESC& _Info)
{
	if (_Info.CurFrame == 39)
	{
		TopperRenderer->ChangeFrameAnimation("SaltBakerHandDeathTopper");
	}

	if (_Info.CurFrame == 45)
	{
		Renderer->CurAnimationPauseOn();
		TopperRenderer->CurAnimationPauseOn();
	}
}
