#include "PreCompile.h"
#include "WaterfallBase.h"

WaterfallBase::WaterfallBase()
{
}

WaterfallBase::~WaterfallBase()
{
}

void WaterfallBase::Start()
{
	Renderer = CreateComponent<GameEngineTextureRenderer>();
	Renderer->CreateFrameAnimationFolder("WaterfallBase", FrameAnimation_DESC("WaterfallBase", 0.1f, true));
	Renderer->ChangeFrameAnimation("WaterfallBase");
	Renderer->GetTransform().SetLocalScale({ 160,100,1 });
}

void WaterfallBase::Update(float _DeltaTime)
{
}

void WaterfallBase::End()
{
}
