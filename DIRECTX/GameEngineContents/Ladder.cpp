#include "PreCompile.h"
#include "Ladder.h"

Ladder::Ladder()
{
}

Ladder::~Ladder()
{
}

void Ladder::Start()
{
	Renderer = CreateComponent<GameEngineTextureRenderer>();
	Renderer->CreateFrameAnimationFolder("Ladder", FrameAnimation_DESC("Ladder", 0.1f));
	Renderer->ChangeFrameAnimation("Ladder");
}

void Ladder::Update(float _DeltaTime)
{
	Renderer->ScaleToTexture();
}

void Ladder::End()
{
}
