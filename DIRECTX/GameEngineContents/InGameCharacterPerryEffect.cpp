#include "PreCompile.h"
#include "InGameCharacterPerryEffect.h"

void InGameCharacterPerryEffect::OnEffectAnimationFrameFinished(const FrameAnimation_DESC& _Info)
{
	Death();
}

void InGameCharacterPerryEffect::Start()
{
	Renderer = CreateComponent<GameEngineTextureRenderer>();
	Renderer->CreateFrameAnimationFolder("PlayerParryEffect", FrameAnimation_DESC("PlayerParryEffect", 0.03f, true));
	Renderer->AnimationBindEnd("PlayerParryEffect", std::bind(&InGameCharacterPerryEffect::OnEffectAnimationFrameFinished, this, std::placeholders::_1));
	Renderer->SetScaleModeImage();
	Renderer->ChangeCamera(CAMERAORDER::ROTATECAMERA2);
}

void InGameCharacterPerryEffect::Update(float _DeltaTime)
{
}

void InGameCharacterPerryEffect::End()
{
}

InGameCharacterPerryEffect::InGameCharacterPerryEffect()
{
}

InGameCharacterPerryEffect::~InGameCharacterPerryEffect()
{
}
