#include "PreCompile.h"
#include "Dogfight.h"

Dogfight::Dogfight()
{
}

Dogfight::~Dogfight()
{
}

void Dogfight::Start()
{
	Renderer = CreateComponent<GameEngineTextureRenderer>();
	Renderer->CreateFrameAnimationFolder("Dogfight", FrameAnimation_DESC("Dogfight", 0.1f));
	Renderer->ChangeFrameAnimation("Dogfight");
	Renderer->GetTransform().SetLocalScale({ 189,163,100 });
}

void Dogfight::Update(float _DeltaTime)
{
}

void Dogfight::End()
{
}
