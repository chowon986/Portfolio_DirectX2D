#include "PreCompile.h"
#include "Bakery.h"

Bakery::Bakery()
{
}

Bakery::~Bakery()
{
}

void Bakery::Start()
{
	Renderer = CreateComponent<GameEngineTextureRenderer>();
	Renderer->CreateFrameAnimationFolder("Bakery", FrameAnimation_DESC("Bakery", 0.1f));
	Renderer->ChangeFrameAnimation("Bakery");
	Renderer->GetTransform().SetLocalScale({ 286,398,100 });
}

void Bakery::Update(float _DeltaTime)
{
}

void Bakery::End()
{
}
