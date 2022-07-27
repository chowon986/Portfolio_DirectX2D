#include "PreCompile.h"
#include "Rumrunners.h"

Rumrunners::Rumrunners()
{
}

Rumrunners::~Rumrunners()
{
}

void Rumrunners::Start()
{
	Renderer = CreateComponent<GameEngineTextureRenderer>();
	Renderer->GetTransform().SetLocalScale({ 179,178,1 });
	Renderer->CreateFrameAnimationFolder("Rumrunners", FrameAnimation_DESC("Rumrunners", 0.1f, true));
	Renderer->ChangeFrameAnimation("Rumrunners");
	Renderer->SetPivot(PIVOTMODE::CENTER);
}

void Rumrunners::Update(float _DeltaTime)
{
}

void Rumrunners::End()
{
}
