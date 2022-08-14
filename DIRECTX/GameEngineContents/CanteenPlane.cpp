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
		Renderer->CreateFrameAnimationFolder("CanteenPlaneFront", FrameAnimation_DESC("CanteenPlaneFront", 0.1f, true));
		Renderer->ChangeFrameAnimation("CanteenPlaneFront");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().SetLocalPosition({ 640, 65, (int)ZOrder::NPC - 1 });
	}
	{
		GameEngineTextureRenderer* Renderer = CreateComponent<GameEngineTextureRenderer>();
		Renderer->CreateFrameAnimationFolder("CanteenPlaneWingLeft", FrameAnimation_DESC("CanteenPlaneWingLeft", 0.1f, true));
		Renderer->ChangeFrameAnimation("CanteenPlaneWingLeft");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().SetLocalPosition({ 275, 200, (int)ZOrder::NPC + 3 });
	}

	{
		GameEngineTextureRenderer* Renderer = CreateComponent<GameEngineTextureRenderer>();

		Renderer->CreateFrameAnimationFolder("CanteenPlaneWingRight", FrameAnimation_DESC("CanteenPlaneWingRight", 0.1f, true));
		Renderer->ChangeFrameAnimation("CanteenPlaneWingRight");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().SetLocalPosition({ 1010, 200, (int)ZOrder::NPC + 3 });
	}

	{
		GameEngineTextureRenderer* Renderer = CreateComponent<GameEngineTextureRenderer>();

		Renderer->CreateFrameAnimationFolder("CanteenPlaneBack", FrameAnimation_DESC("CanteenPlaneBack", 0.1f, true));
		Renderer->ChangeFrameAnimation("CanteenPlaneBack");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().SetLocalPosition({ 640, 200, (int)ZOrder::NPC + 2 });
	}

	{
		GameEngineTextureRenderer* Renderer = CreateComponent<GameEngineTextureRenderer>();

		Renderer->CreateFrameAnimationFolder("CanteenPlaneTail", FrameAnimation_DESC("CanteenPlaneTail", 0.1f, true));
		Renderer->ChangeFrameAnimation("CanteenPlaneTail");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().SetLocalPosition({ 640, 300, (int)ZOrder::NPC + 4 });
	}

	{
		GameEngineTextureRenderer* Renderer = CreateComponent<GameEngineTextureRenderer>();

		Renderer->CreateFrameAnimationFolder("CanteenPropellorRingCenter", FrameAnimation_DESC("CanteenPropellorRingCenter", 0.1f, true));
		Renderer->ChangeFrameAnimation("CanteenPropellorRingCenter");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().SetLocalPosition({ 640, 20, (int)ZOrder::NPC - 4 });
	}

	{
		GameEngineTextureRenderer* Renderer = CreateComponent<GameEngineTextureRenderer>();

		Renderer->CreateFrameAnimationFolder("CanteenPropellorTipCenter", FrameAnimation_DESC("CanteenPropellorTipCenter", 0.1f, true));
		Renderer->ChangeFrameAnimation("CanteenPropellorTipCenter");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().SetLocalPosition({ 640, 20, (int)ZOrder::NPC - 6 });
	}

	{
		GameEngineTextureRenderer* Renderer = CreateComponent<GameEngineTextureRenderer>();

		Renderer->CreateFrameAnimationFolder("CanteenPropellorSpinCenter", FrameAnimation_DESC("CanteenPropellorSpinCenter", 0.05f, true));
		Renderer->ChangeFrameAnimation("CanteenPropellorSpinCenter");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().SetLocalPosition({ 638, 25, (int)ZOrder::NPC - 5 });
	}


	{
		GameEngineTextureRenderer* Renderer = CreateComponent<GameEngineTextureRenderer>();

		Renderer->CreateFrameAnimationFolder("CanteenPropelloRingLeft", FrameAnimation_DESC("CanteenPropelloRingLeft", 0.1f, true));
		Renderer->ChangeFrameAnimation("CanteenPropelloRingLeft");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().SetLocalPosition({ 240, 100, (int)ZOrder::NPC + 1 });
	}

	{
		GameEngineTextureRenderer* Renderer = CreateComponent<GameEngineTextureRenderer>();

		Renderer->CreateFrameAnimationFolder("CanteenPropellorTipLeft", FrameAnimation_DESC("CanteenPropellorTipLeft", 0.1f, true));
		Renderer->ChangeFrameAnimation("CanteenPropellorTipLeft");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().SetLocalPosition({ 240, 100, (int)ZOrder::NPC - 1 });
	}

	{
		GameEngineTextureRenderer* Renderer = CreateComponent<GameEngineTextureRenderer>();

		Renderer->CreateFrameAnimationFolder("CanteenPropellorSpinLeft", FrameAnimation_DESC("CanteenPropellorSpinLeft", 0.05f, true));
		Renderer->ChangeFrameAnimation("CanteenPropellorSpinLeft");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().SetLocalPosition({ 240, 100, (int)ZOrder::NPC });
	}

	{
		GameEngineTextureRenderer* Renderer = CreateComponent<GameEngineTextureRenderer>();

		Renderer->CreateFrameAnimationFolder("CanteenPropellorTipRight", FrameAnimation_DESC("CanteenPropellorTipRight", 0.1f, true));
		Renderer->ChangeFrameAnimation("CanteenPropellorTipRight");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().SetLocalPosition({ 1040, 100, (int)ZOrder::NPC - 1 });
	}

	{
		GameEngineTextureRenderer* Renderer = CreateComponent<GameEngineTextureRenderer>();

		Renderer->CreateFrameAnimationFolder("CanteenPropelloRingLeft", FrameAnimation_DESC("CanteenPropelloRingLeft", 0.1f, true));
		Renderer->ChangeFrameAnimation("CanteenPropelloRingLeft");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().PixLocalNegativeX();
		Renderer->GetTransform().SetLocalPosition({ 1040, 100, (int)ZOrder::NPC + 1 });
	}
	{
		GameEngineTextureRenderer* Renderer = CreateComponent<GameEngineTextureRenderer>();

		Renderer->CreateFrameAnimationFolder("CanteenPropellorSpinRight", FrameAnimation_DESC("CanteenPropellorSpinRight", 0.05f, true));
		Renderer->ChangeFrameAnimation("CanteenPropellorSpinRight");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().SetLocalPosition({ 1045, 105, (int)ZOrder::NPC });
	}

	{
		GameEngineTextureRenderer* Renderer = CreateComponent<GameEngineTextureRenderer>();

		Renderer->CreateFrameAnimationFolder("CanteenPlaneFlapLeftA", FrameAnimation_DESC("CanteenPlaneFlapLeftA", 0.1f, true));
		Renderer->ChangeFrameAnimation("CanteenPlaneFlapLeftA");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().SetLocalPosition({ 430, 170, (int)ZOrder::NPC + 2 });
	}

	{
		GameEngineTextureRenderer* Renderer = CreateComponent<GameEngineTextureRenderer>();

		Renderer->CreateFrameAnimationFolder("CanteenPlaneFlapLeftB", FrameAnimation_DESC("CanteenPlaneFlapLeftB", 0.1f, true));
		Renderer->ChangeFrameAnimation("CanteenPlaneFlapLeftB");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().SetLocalPosition({ 120, 190, (int)ZOrder::NPC + 2 });
	}

	{
		GameEngineTextureRenderer* Renderer = CreateComponent<GameEngineTextureRenderer>();

		Renderer->CreateFrameAnimationFolder("CanteenPlaneFlapRightA", FrameAnimation_DESC("CanteenPlaneFlapRightA", 0.1f, true));
		Renderer->ChangeFrameAnimation("CanteenPlaneFlapRightA");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().SetLocalPosition({ 860, 170, (int)ZOrder::NPC + 2 });
	}

	{
		GameEngineTextureRenderer* Renderer = CreateComponent<GameEngineTextureRenderer>();

		Renderer->CreateFrameAnimationFolder("CanteenPlaneFlapRightB", FrameAnimation_DESC("CanteenPlaneFlapRightB", 0.1f, true));
		Renderer->ChangeFrameAnimation("CanteenPlaneFlapRightB");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().SetLocalPosition({ 1160, 190, (int)ZOrder::NPC + 2 });
	}

	{
		CaptainCanteen = GetLevel()->CreateActor<Canteen>();
		CaptainCanteen->SetParent(this);
		CaptainCanteen->GetTransform().SetLocalPosition({ 640, 0, (int)ZOrder::NPC - 2 });
	}

	{
		Ph1Dog* DogFightPh1Dog = GetLevel()->CreateActor<Ph1Dog>();
		DogFightPh1Dog->SetParent(this);
		DogFightPh1Dog->GetTransform().SetLocalPosition({ 640, 0, (int)ZOrder::NPC - 2 });
	}
}

void CanteenPlane::Update(float _DeltaTime)
{
}

void CanteenPlane::End()
{
}
