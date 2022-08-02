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
	PortalBase::Start();

	Renderer->GetTransform().SetLocalScale({ 361,301,1 });
	Renderer->CreateFrameAnimationFolder("Omm", FrameAnimation_DESC("Omm", 0.1f, true));
	Renderer->ChangeFrameAnimation("Omm");
	Renderer->SetPivot(PIVOTMODE::CENTER);

	Collision->GetTransform().SetLocalScale({ 100.0f, 100.0f, 1.0f });

}

void Omm::Update(float _DeltaTime)
{
	PortalBase::Update(_DeltaTime);

}

void Omm::End()
{
}
