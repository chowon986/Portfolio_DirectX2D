#include "PreCompile.h"
#include "TutorialLevel.h"
#include "Background.h"
#include "Enums.h"
#include <GameEngineCore/GEngine.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineCore/GameEngineTextureRenderer.h>
#include "InGameCuphead.h"

TutorialLevel::TutorialLevel()
{
}

TutorialLevel::~TutorialLevel()
{
}

void TutorialLevel::EndTutorialStartAnimation(const FrameAnimation_DESC& _Info)
{
	BackgroundRenderer->ChangeFrameAnimation("TutorialBackground");
}

void TutorialLevel::Start()
{
	{
		Background* TutorialBackground = CreateActor<Background>(GameObjectGroup::UI);
		BackgroundRenderer = TutorialBackground->CreateComponent<GameEngineTextureRenderer>();
		BackgroundRenderer->CreateFrameAnimationFolder("TutorialStartBackground", FrameAnimation_DESC("TutorialStartBackground", 0.05f, false));
		BackgroundRenderer->CreateFrameAnimationFolder("TutorialBackground", FrameAnimation_DESC("TutorialBackground", 0.1f, false));
		BackgroundRenderer->AnimationBindEnd("TutorialStartBackground", &TutorialLevel::EndTutorialStartAnimation, this);
		BackgroundRenderer->ChangeFrameAnimation("TutorialStartBackground");
		BackgroundRenderer->ScaleToTexture();
	}

	{
		Cuphead = CreateActor<InGameCuphead>(GameObjectGroup::Player);
		Cuphead->GetTransform().SetLocalPosition({ -300, -200, -100 });
	}
}

void TutorialLevel::Update(float _DeltaTime)
{
}


void TutorialLevel::End()
{
	int a = 0;
}