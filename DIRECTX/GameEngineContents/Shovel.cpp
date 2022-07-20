#include "PreCompile.h"
#include "Shovel.h"

Shovel::Shovel()
{
}

Shovel::~Shovel()
{
}

void Shovel::Start()
{
	Renderer = CreateComponent<GameEngineTextureRenderer>();
	Renderer->CreateFrameAnimationFolder("Shovel", FrameAnimation_DESC("Shovel", 0.1f));
	Renderer->ChangeFrameAnimation("Shovel");
	Renderer->GetTransform().SetLocalScale({ 94, 94, 100 });
}

void Shovel::Update(float _DeltaTime)
{
}

void Shovel::Talk()
{
}

void Shovel::Idle()
{
}
