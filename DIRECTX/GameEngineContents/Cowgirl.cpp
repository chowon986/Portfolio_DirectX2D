#include "PreCompile.h"
#include "Cowgirl.h"

Cowgirl::Cowgirl()
	:Renderer(nullptr)
{
}

Cowgirl::~Cowgirl()
{
}

void Cowgirl::Start()
{
	Renderer = CreateComponent<GameEngineTextureRenderer>();
	Renderer->GetTransform().SetLocalScale({ 169,224,1 });
	Renderer->CreateFrameAnimationFolder("Cowgirl", FrameAnimation_DESC("Cowgirl", 0.1f, true));
	Renderer->ChangeFrameAnimation("Cowgirl");
	Renderer->SetPivot(PIVOTMODE::CENTER);
}

void Cowgirl::Update(float _DeltaTime)
{
}

void Cowgirl::End()
{
}
