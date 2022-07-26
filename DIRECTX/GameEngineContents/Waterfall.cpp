#include "PreCompile.h"
#include "Waterfall.h"

Waterfall::Waterfall()
{
}

Waterfall::~Waterfall()
{
}

void Waterfall::Start()
{
	Renderer = CreateComponent<GameEngineTextureRenderer>();
	Renderer->GetTransform().SetLocalScale({ 190,289,1 });
	Renderer->CreateFrameAnimationFolder("Waterfall", FrameAnimation_DESC("Waterfall", 0.1f, true));
	Renderer->ChangeFrameAnimation("Waterfall");
}

void Waterfall::Update(float _DeltaTime)
{
}

void Waterfall::End()
{
}
