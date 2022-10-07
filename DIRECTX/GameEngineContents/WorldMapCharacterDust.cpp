#include "PreCompile.h"
#include "WorldMapCharacterDust.h"
#include "WorldMapCuphead.h"

WorldMapCharacterDust::WorldMapCharacterDust()
{
}

WorldMapCharacterDust::~WorldMapCharacterDust()
{
}

void WorldMapCharacterDust::OnDustAnimationFrameFinished(const FrameAnimation_DESC& _Info)
{
	Death();
}

void WorldMapCharacterDust::Start()
{
	Renderer = CreateComponent<GameEngineTextureRenderer>();
	Renderer->CreateFrameAnimationCutTexture("PlayerWorldMapDust", FrameAnimation_DESC("PlayerWorldMapDust.png", 0, 20, 0.03f, true));
	Renderer->AnimationBindEnd("PlayerWorldMapDust", std::bind(&WorldMapCharacterDust::OnDustAnimationFrameFinished, this, std::placeholders::_1));
	Renderer->GetTransform().SetWorldScale({ 70,70,1 });
	//Renderer->ChangeCamera(CAMERAORDER::ROTATECAMERA2);
}

void WorldMapCharacterDust::Update(float _DeltaTime)
{
}

void WorldMapCharacterDust::End()
{
}
