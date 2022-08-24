#include "PreCompile.h"
#include "Dogfight.h"

Dogfight::Dogfight()
{
}

Dogfight::~Dogfight()
{
}

void Dogfight::Start()
{
	PortalBase::Start();

	Renderer->CreateFrameAnimationFolder("Dogfight", FrameAnimation_DESC("Dogfight", 0.1f));
	Renderer->ChangeFrameAnimation("Dogfight");
	Renderer->GetTransform().SetLocalScale({ 189,163,1 });
	Renderer->SetPivot(PIVOTMODE::CENTER);

	Collision->ChangeOrder(ObjectOrder::DOGFIGHT);
	Collision->GetTransform().SetLocalScale({ 100.0f, 100.0f, 1.0f });

}

void Dogfight::Update(float _DeltaTime)
{
	PortalBase::Update(_DeltaTime);

}

void Dogfight::End()
{
}
