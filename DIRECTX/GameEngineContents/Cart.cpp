#include "PreCompile.h"
#include "Cart.h"

Cart::Cart()
{
}

Cart::~Cart()
{
}

void Cart::Start()
{
	Renderer = CreateComponent<GameEngineTextureRenderer>();
	Renderer->GetTransform().SetLocalScale({ 176,179,1 });
	Renderer->CreateFrameAnimationFolder("Cart", FrameAnimation_DESC("Cart", 0.1f));
	Renderer->ChangeFrameAnimation("Cart");
	Renderer->SetPivot(PIVOTMODE::CENTER);
}

void Cart::Update(float _DeltaTime)
{
}

void Cart::End()
{
}
