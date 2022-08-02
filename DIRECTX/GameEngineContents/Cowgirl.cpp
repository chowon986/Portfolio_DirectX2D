#include "PreCompile.h"
#include "Cowgirl.h"

Cowgirl::Cowgirl()
{
}

Cowgirl::~Cowgirl()
{
}

void Cowgirl::Start()
{
	PortalBase::Start();

	Renderer->GetTransform().SetLocalScale({ 169,224,1 });
	Renderer->CreateFrameAnimationFolder("Cowgirl", FrameAnimation_DESC("Cowgirl", 0.1f, true));
	Renderer->ChangeFrameAnimation("Cowgirl");
	Renderer->SetPivot(PIVOTMODE::CENTER);

	Collision->GetTransform().SetLocalScale({ 100.0f, 100.0f, 1.0f });

}

void Cowgirl::Update(float _DeltaTime)
{
	PortalBase::Update(_DeltaTime);

}

void Cowgirl::End()
{
}
