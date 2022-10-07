#include "PreCompile.h"
#include "InGameCharacterExShotEffect.h"

InGameCharacterExShotEffect::InGameCharacterExShotEffect()
{
}

InGameCharacterExShotEffect::~InGameCharacterExShotEffect()
{
}

void InGameCharacterExShotEffect::OnDustAnimationFrameFinished(const FrameAnimation_DESC& _Info)
{
	Death();
}

void InGameCharacterExShotEffect::Start()
{
	Renderer = CreateComponent<GameEngineTextureRenderer>();
	Renderer->CreateFrameAnimationFolder("PlayerExShotEffect", FrameAnimation_DESC("PlayerExShotEffect", 0.03f, true));
	Renderer->AnimationBindEnd("PlayerExShotEffect", std::bind(&InGameCharacterExShotEffect::OnDustAnimationFrameFinished, this, std::placeholders::_1));
	Renderer->SetScaleModeImage();
	Renderer->ChangeCamera(CAMERAORDER::ROTATECAMERA2);
	Renderer->SetPivot(PIVOTMODE::LEFT);
}

void InGameCharacterExShotEffect::Update(float _DeltaTime)
{
}

void InGameCharacterExShotEffect::End()
{
}
