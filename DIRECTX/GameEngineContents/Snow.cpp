#include "PreCompile.h"
#include "Snow.h"

Snow::Snow()
{
}

Snow::~Snow()
{
}

void Snow::Start()
{
	Renderer = CreateComponent<GameEngineTextureRenderer>();
	Renderer->GetTransform().SetLocalScale({ 346,335,1 });
	Renderer->CreateFrameAnimationFolder("Snow", FrameAnimation_DESC("Snow", 0.1f, true));
	Renderer->ChangeFrameAnimation("Snow");
	Renderer->SetPivot(PIVOTMODE::CENTER);
}

void Snow::Update(float _DeltaTime)
{
}

void Snow::End()
{
}
