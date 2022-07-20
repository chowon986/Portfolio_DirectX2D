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
	Renderer->GetTransform().SetLocalScale({ 72,120,100 });
	Renderer->CreateFrameAnimationFolder("Cactus", FrameAnimation_DESC("Cactus", 0.1f, true));
	Renderer->ChangeFrameAnimation("Cactus");
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
