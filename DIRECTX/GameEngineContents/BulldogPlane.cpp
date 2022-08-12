#include "PreCompile.h"
#include "BulldogPlane.h"

BulldogPlane::BulldogPlane()
{
}

BulldogPlane::~BulldogPlane()
{
}

void BulldogPlane::Start()
{
	{
		GameEngineTextureRenderer* Renderer = CreateComponent<GameEngineTextureRenderer>();
		Renderer->CreateFrameAnimationFolder("BulldogPlaneFront", FrameAnimation_DESC("BulldogPlaneFront", 0.1f, true));
		Renderer->ChangeFrameAnimation("BulldogPlaneFront");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().SetLocalPosition({ 40, -5, (int)ZOrder::UI-1}); // -600 -300
	}

	{
		GameEngineTextureRenderer* Renderer = CreateComponent<GameEngineTextureRenderer>();
		Renderer->CreateFrameAnimationFolder("BulldogPlaneWingLeft", FrameAnimation_DESC("BulldogPlaneWingLeft", 0.1f, true));
		Renderer->ChangeFrameAnimation("BulldogPlaneWingLeft");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().SetLocalPosition({ -300, -0, (int)ZOrder::UI});
	}
}

void BulldogPlane::Update(float _DeltaTime)
{
	int a = 0;
}

void BulldogPlane::End()
{
}
