#include "PreCompile.h"
#include "WaterLine.h"

WaterLine::WaterLine()
{
}

WaterLine::~WaterLine()
{
}

void WaterLine::Start()
{
	Renderer = CreateComponent<GameEngineTextureRenderer>();
	Renderer->CreateFrameAnimationFolder("WaterLine", FrameAnimation_DESC("WaterLine", 0.1f));
	Renderer->ChangeFrameAnimation("WaterLine");
	Renderer->GetTransform().SetLocalScale({ 3710,1772,1 });
}

void WaterLine::Update(float _DeltaTime)
{
}

void WaterLine::End()
{
}
