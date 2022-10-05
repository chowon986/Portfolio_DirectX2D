#include "PreCompile.h"
#include "InGameCharacterDust.h"
#include "InGameCuphead.h"

InGameCharacterDust::InGameCharacterDust()
{
}

InGameCharacterDust::~InGameCharacterDust()
{
}

void InGameCharacterDust::OnDustAnimationFrameFinished(const FrameAnimation_DESC& _Info)
{
	Death();
}

void InGameCharacterDust::Start()
{
	Renderer = CreateComponent<GameEngineTextureRenderer>();
	Renderer->CreateFrameAnimationCutTexture("IngameCupheadWalk", FrameAnimation_DESC("PlayerWalkDust.png", 0, 20, 0.03f, true));
	Renderer->AnimationBindEnd("IngameCupheadWalk", std::bind(&InGameCharacterDust::OnDustAnimationFrameFinished, this, std::placeholders::_1));
	Renderer->GetTransform().SetWorldScale({ 141,141,1 });
	Renderer->ChangeCamera(CAMERAORDER::ROTATECAMERA2);
}

void InGameCharacterDust::Update(float _DeltaTime)
{
}

void InGameCharacterDust::End()
{
}
