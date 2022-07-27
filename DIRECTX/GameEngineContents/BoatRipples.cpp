#include "PreCompile.h"
#include "BoatRipples.h"
#include "Enums.h"

BoatRipples::BoatRipples()
{
}

BoatRipples::~BoatRipples()
{
}

void BoatRipples::Start()
{
	Renderer = CreateComponent<GameEngineTextureRenderer>();
	Renderer->GetTransform().SetLocalScale({ -238,66,1 });
	Renderer->CreateFrameAnimationFolder("BoatRipples", FrameAnimation_DESC("BoatmanRipples", 0.1f));
	Renderer->ChangeFrameAnimation("BoatRipples");
	Renderer->SetPivot(PIVOTMODE::CENTER);
}

void BoatRipples::Update(float _DeltaTime)
{
}

void BoatRipples::End()
{
}
