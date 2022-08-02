#include "PreCompile.h"
#include "Ladder.h"

Ladder::Ladder()
{
}

Ladder::~Ladder()
{
}

void Ladder::Start()
{
	PortalBase::Start();

	Renderer->CreateFrameAnimationFolder("Ladder", FrameAnimation_DESC("Ladder", 0.1f));
	Renderer->ChangeFrameAnimation("Ladder");
	Renderer->SetPivot(PIVOTMODE::CENTER);
	Renderer->ScaleToTexture();	

	Collision->GetTransform().SetLocalScale({ 100.0f, 100.0f, 1.0f });

}

void Ladder::Update(float _DeltaTime)
{
	PortalBase::Update(_DeltaTime);

}

void Ladder::End()
{
}
