#include "PreCompile.h"
#include "Lantern.h"

Lantern::Lantern()
{
}

Lantern::~Lantern()
{
}

void Lantern::Start()
{
	Renderer = CreateComponent<GameEngineTextureRenderer>();
	Renderer->CreateFrameAnimationFolder("Lantern", FrameAnimation_DESC("Lantern", 0.1f));
	Renderer->ChangeFrameAnimation("Lantern");
	Renderer->GetTransform().SetLocalScale({ 66,111,100 });
}

void Lantern::Update(float _DeltaTime)
{
}

void Lantern::Talk()
{
}

void Lantern::Idle()
{
}
