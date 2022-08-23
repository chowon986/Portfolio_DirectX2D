#include "PreCompile.h"
#include "BackgroundHills.h"

BackgroundHills::BackgroundHills()
{
}

BackgroundHills::~BackgroundHills()
{
}

void BackgroundHills::Start()
{
	Renderer = CreateComponent<GameEngineTextureRenderer>();
	Renderer->CreateFrameAnimationFolder("BackgroundHills", FrameAnimation_DESC("Hills", 0.07f, true));
	Renderer->ChangeFrameAnimation("BackgroundHills");
	Renderer->ScaleToTexture();
	Renderer->SetPivot(PIVOTMODE::LEFTTOP);
	Renderer->ChangeCamera(CAMERAORDER::BACKGROUND);
}

void BackgroundHills::Update(float _DeltaTime)
{
}

void BackgroundHills::End()
{
}
