#include "PreCompile.h"
#include "Omm.h"

Omm::Omm()
{
}

Omm::~Omm()
{
}

void Omm::Start()
{
	Renderer = CreateComponent<GameEngineTextureRenderer>();
	Renderer->GetTransform().SetLocalScale({ 361,301,1 });
	Renderer->CreateFrameAnimationFolder("Omm", FrameAnimation_DESC("Omm", 0.1f, true));
	Renderer->ChangeFrameAnimation("Omm");
	Renderer->SetPivot(PIVOTMODE::CENTER);
}

void Omm::Update(float _DeltaTime)
{
}

void Omm::End()
{
}
