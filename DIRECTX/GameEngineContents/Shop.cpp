#include "PreCompile.h"
#include "Shop.h"

Shop::Shop()
{
}

Shop::~Shop()
{
}

void Shop::Start()
{
	Renderer = CreateComponent<GameEngineTextureRenderer>();
	Renderer->CreateFrameAnimationFolder("Shop", FrameAnimation_DESC("Shop", 0.1f));
	Renderer->ChangeFrameAnimation("Shop");
	Renderer->GetTransform().SetLocalScale({ 222,259,100 });
}

void Shop::Update(float _DeltaTime)
{
}

void Shop::End()
{
}
