#include "PreCompile.h"
#include "Catus.h"

Catus::Catus()
{
}

Catus::~Catus()
{
}

void Catus::Start()
{
	Renderer = CreateComponent<GameEngineTextureRenderer>();
	Renderer->CreateFrameAnimationFolder("Cactus", FrameAnimation_DESC("NPCCactus", 0.1f, true));
	Renderer->ChangeFrameAnimation("Cactus");
	Renderer->ScaleToTexture();
}

void Catus::Update(float _DeltaTime)
{
}

void Catus::Talk()
{
}

void Catus::Idle()
{
}
