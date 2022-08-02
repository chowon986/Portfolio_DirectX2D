#include "PreCompile.h"
#include "Snow.h"

Snow::Snow()
{
}

Snow::~Snow()
{
}

void Snow::Start()
{
	PortalBase::Start();

	Renderer->GetTransform().SetLocalScale({ 346,335,1 });
	Renderer->CreateFrameAnimationFolder("Snow", FrameAnimation_DESC("Snow", 0.1f, true));
	Renderer->ChangeFrameAnimation("Snow");
	Renderer->SetPivot(PIVOTMODE::CENTER);

	Collision->GetTransform().SetLocalScale({ 100.0f, 100.0f, 1.0f });

}

void Snow::Update(float _DeltaTime)
{
	PortalBase::Update(_DeltaTime);

}

void Snow::End()
{
}
