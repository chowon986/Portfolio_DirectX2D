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
	Renderer->GetTransform().SetLocalScale({ 145,77,1 });
	Renderer->CreateFrameAnimationFolder("WaterfallBase", FrameAnimation_DESC("WaterfallBase", 0.1f, true));
	Renderer->ChangeFrameAnimation("WaterfallBase");
}

void WaterfallBase::Update(float _DeltaTime)
{
}

void WaterfallBase::End()
{
}
