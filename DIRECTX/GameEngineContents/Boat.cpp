#include "PreCompile.h"
#include "Boat.h"
#include "Enums.h"

Boat::Boat()
{
}

Boat::~Boat()
{
}

void Boat::Start()
{
	Renderer = CreateComponent<GameEngineTextureRenderer>();
	Renderer->CreateFrameAnimationFolder("Boat", FrameAnimation_DESC("Boat", 0.1f));
	Renderer->ChangeFrameAnimation("Boat");
	Renderer->GetTransform().SetLocalScale({ -233,148,1 });
	Renderer->SetPivot(PIVOTMODE::CENTER);
}

void Boat::Update(float _DeltaTime)
{
}

void Boat::End()
{
}
