#include "PreCompile.h"
#include "Bakery.h"

Bakery::Bakery()
{
}

Bakery::~Bakery()
{
}

void Bakery::Start()
{
	PortalBase::Start();

	Renderer = CreateComponent<GameEngineTextureRenderer>();
	Renderer->CreateFrameAnimationFolder("Bakery", FrameAnimation_DESC("Bakery", 0.1f));
	Renderer->ChangeFrameAnimation("Bakery");
	Renderer->ScaleToTexture();
	Renderer->SetPivot(PIVOTMODE::CENTER);

	Collision->GetTransform().SetLocalScale({ 100.0f, 100.0f, 1.0f });
}

void Bakery::Update(float _DeltaTime)
{
	PortalBase::Update(_DeltaTime);

}

void Bakery::End()
{
}
