#include "PreCompile.h"
#include "Boatman.h"

Boatman::Boatman()
{
}

Boatman::~Boatman()
{
}

void Boatman::SetState(BoatmanState _State)
{
}

BoatmanState Boatman::GetState()
{
	return BoatmanState();
}

void Boatman::Start()
{
	Renderer = CreateComponent<GameEngineTextureRenderer>();
	Renderer->CreateFrameAnimationFolder("BoatmanIdle", FrameAnimation_DESC("BoatmanIdle", 0.17f));
	Renderer->ChangeFrameAnimation("BoatmanIdle");
	Renderer->GetTransform().SetLocalScale({ -121,160, 1 });
	Renderer->SetPivot(PIVOTMODE::CENTER);
}

void Boatman::Update(float _DeltaTime)
{
}

void Boatman::Talk()
{
}

void Boatman::Idle()
{
}
