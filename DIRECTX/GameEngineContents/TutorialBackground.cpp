#include "PreCompile.h"
#include "TutorialBackground.h"

TutorialBackground::TutorialBackground()
{
}

TutorialBackground::~TutorialBackground()
{
}

void TutorialBackground::Start()
{
	Renderer = CreateComponent<GameEngineTextureRenderer>();
	Renderer->CreateFrameAnimationFolder("TutorialStartBackground", FrameAnimation_DESC("TutorialStartBackground", 0.05f, false));
	Renderer->CreateFrameAnimationFolder("TutorialBackground", FrameAnimation_DESC("TutorialBackground", 0.1f, false));
	Renderer->AnimationBindEnd("TutorialStartBackground", &TutorialBackground::EndTutorialStartAnimation, this);
	Renderer->ChangeFrameAnimation("TutorialStartBackground");
	Renderer->ScaleToTexture();
	Renderer->SetPivot(PIVOTMODE::LEFTTOP);
}

void TutorialBackground::Update(float _DeltaTime)
{
}

void TutorialBackground::End()
{
}

void TutorialBackground::EndTutorialStartAnimation(const FrameAnimation_DESC& _Info)
{
	Renderer->ChangeFrameAnimation("TutorialBackground");
}
