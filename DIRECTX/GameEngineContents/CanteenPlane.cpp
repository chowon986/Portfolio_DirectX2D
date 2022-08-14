#include "PreCompile.h"
#include "CanteenPlane.h"
#include "Canteen.h"
#include "Ph1Dog.h"

CanteenPlane::CanteenPlane()
	: Player(nullptr)
	, CaptainCanteen(nullptr)
{
}

CanteenPlane::~CanteenPlane()
{
}

void CanteenPlane::Start()
{
	{
		GameEngineTextureRenderer* Renderer = CreateComponent<GameEngineTextureRenderer>();
		Renderer->CreateFrameAnimationFolder("CanteenPlaneBody", FrameAnimation_DESC("CanteenPlaneBody", 0.1f, true));
		Renderer->ChangeFrameAnimation("CanteenPlaneBody");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().SetLocalPosition({ 640, -360, (int)ZOrder::NPC });
	}
	{
		GameEngineTextureRenderer* Renderer = CreateComponent<GameEngineTextureRenderer>();
		Renderer->CreateFrameAnimationFolder("CanteenPlanePropeller", FrameAnimation_DESC("CanteenPlanePropeller", 0.1f, true));
		Renderer->ChangeFrameAnimation("CanteenPlanePropeller");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().SetLocalPosition({ 640, -400, (int)ZOrder::Player - 1 });
	}

	{
		GameEngineTextureRenderer* Renderer = CreateComponent<GameEngineTextureRenderer>();

		Renderer->CreateFrameAnimationFolder("CanteenPlaneTail", FrameAnimation_DESC("CanteenPlaneTail", 0.1f, true));
		Renderer->ChangeFrameAnimation("CanteenPlaneTail");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().SetLocalPosition({ 640, -310, (int)ZOrder::NPC + 3 });
	}

	{
		GameEngineTextureRenderer* Renderer = CreateComponent<GameEngineTextureRenderer>();

		Renderer->CreateFrameAnimationFolder("CanteenPlaneTopWing", FrameAnimation_DESC("CanteenPlaneTopWing", 0.1f, true));
		Renderer->ChangeFrameAnimation("CanteenPlaneTopWing");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().SetLocalPosition({ 640, -320, (int)ZOrder::NPC - 1 });
	}

	{
		GameEngineTextureRenderer* Renderer = CreateComponent<GameEngineTextureRenderer>();

		Renderer->CreateFrameAnimationFolder("CanteenPlaneWheels", FrameAnimation_DESC("CanteenPlaneWheels", 0.1f, true));
		Renderer->ChangeFrameAnimation("CanteenPlaneWheels");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().SetLocalPosition({ 640, -430, (int)ZOrder::NPC + 2 });
	}

	{
		GameEngineTextureRenderer* Renderer = CreateComponent<GameEngineTextureRenderer>();

		Renderer->CreateFrameAnimationFolder("CanteenPlaneWing", FrameAnimation_DESC("CanteenPlaneWing", 0.1f, true));
		Renderer->ChangeFrameAnimation("CanteenPlaneWing");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().SetLocalPosition({ 640, -360, (int)ZOrder::NPC + 2 });
	}

	{
		CaptainCanteen = GetLevel()->CreateActor<Canteen>();
		CaptainCanteen->SetParent(this);
		CaptainCanteen->GetTransform().SetLocalPosition({ 640, 0, (int)ZOrder::NPC - 2 });
	}
}

void CanteenPlane::Update(float _DeltaTime)
{
}

void CanteenPlane::End()
{
}
