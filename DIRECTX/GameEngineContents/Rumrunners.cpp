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
	PortalBase::Start();

	Renderer->GetTransform().SetLocalScale({ 179,178,1 });
	Renderer->CreateFrameAnimationFolder("Rumrunners", FrameAnimation_DESC("Rumrunners", 0.1f, true));
	Renderer->ChangeFrameAnimation("Rumrunners");
	Renderer->SetPivot(PIVOTMODE::CENTER);

	Collision->GetTransform().SetLocalScale({ 100.0f, 100.0f, 1.0f });

}

void Rumrunners::Update(float _DeltaTime)
{
	PortalBase::Update(_DeltaTime);

}

void Rumrunners::End()
{
}
