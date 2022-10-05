#include "PreCompile.h"
#include "InGameCharacterJumpDust.h"

InGameCharacterJumpDust::InGameCharacterJumpDust()
{
}

InGameCharacterJumpDust::~InGameCharacterJumpDust()
{
}

void InGameCharacterJumpDust::OnDustAnimationFrameFinished(const FrameAnimation_DESC& _Info)
{
	Death();
}

void InGameCharacterJumpDust::Start()
{
	Renderer = CreateComponent<GameEngineTextureRenderer>();
	Renderer->CreateFrameAnimationFolder("IngameCupheadJump", FrameAnimation_DESC("PlayerJumpDust", 0.03f, true));
	Renderer->AnimationBindEnd("IngameCupheadJump", std::bind(&InGameCharacterJumpDust::OnDustAnimationFrameFinished, this, std::placeholders::_1));
	Renderer->SetScaleModeImage();
	Renderer->ChangeCamera(CAMERAORDER::ROTATECAMERA2);
}

void InGameCharacterJumpDust::Update(float _DeltaTime)
{
}

void InGameCharacterJumpDust::End()
{
}
