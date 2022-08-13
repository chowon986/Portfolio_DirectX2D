#include "PreCompile.h"
#include "BulldogPlane.h"
#include "Bulldog.h"
#include "Ph1Dog.h"

BulldogPlane::BulldogPlane()
	:Player(nullptr)
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
		Renderer->GetTransform().SetLocalPosition({ 640, 65, (int)ZOrder::NPC - 1});
	}
	{
		GameEngineTextureRenderer* Renderer = CreateComponent<GameEngineTextureRenderer>();
		Renderer->CreateFrameAnimationFolder("BulldogPlaneWingLeft", FrameAnimation_DESC("BulldogPlaneWingLeft", 0.1f, true));
		Renderer->ChangeFrameAnimation("BulldogPlaneWingLeft");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().SetLocalPosition({ 275, 200, (int)ZOrder::NPC + 3 });
	}

	{
		GameEngineTextureRenderer* Renderer = CreateComponent<GameEngineTextureRenderer>();

		Renderer->CreateFrameAnimationFolder("BulldogPlaneWingRight", FrameAnimation_DESC("BulldogPlaneWingRight", 0.1f, true));
		Renderer->ChangeFrameAnimation("BulldogPlaneWingRight");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().SetLocalPosition({ 1010, 200, (int)ZOrder::NPC + 3 });
	}

	{
		GameEngineTextureRenderer* Renderer = CreateComponent<GameEngineTextureRenderer>();

		Renderer->CreateFrameAnimationFolder("BulldogPlaneBack", FrameAnimation_DESC("BulldogPlaneBack", 0.1f, true));
		Renderer->ChangeFrameAnimation("BulldogPlaneBack");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().SetLocalPosition({ 640, 200, (int)ZOrder::NPC + 2 });
	}

	{
		GameEngineTextureRenderer* Renderer = CreateComponent<GameEngineTextureRenderer>();

		Renderer->CreateFrameAnimationFolder("BulldogPlaneTail", FrameAnimation_DESC("BulldogPlaneTail", 0.1f, true));
		Renderer->ChangeFrameAnimation("BulldogPlaneTail");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().SetLocalPosition({ 640, 300, (int)ZOrder::NPC + 4 });
	}

	{
		GameEngineTextureRenderer* Renderer = CreateComponent<GameEngineTextureRenderer>();

		Renderer->CreateFrameAnimationFolder("BulldogPropellorRingCenter", FrameAnimation_DESC("BulldogPropellorRingCenter", 0.1f, true));
		Renderer->ChangeFrameAnimation("BulldogPropellorRingCenter");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().SetLocalPosition({ 640, 20, (int)ZOrder::NPC - 4 });
	}

	{
		GameEngineTextureRenderer* Renderer = CreateComponent<GameEngineTextureRenderer>();

		Renderer->CreateFrameAnimationFolder("BulldogPropellorTipCenter", FrameAnimation_DESC("BulldogPropellorTipCenter", 0.1f, true));
		Renderer->ChangeFrameAnimation("BulldogPropellorTipCenter");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().SetLocalPosition({ 640, 20, (int)ZOrder::NPC - 6 });
	}

	{
		GameEngineTextureRenderer* Renderer = CreateComponent<GameEngineTextureRenderer>();

		Renderer->CreateFrameAnimationFolder("BulldogPropellorSpinCenter", FrameAnimation_DESC("BulldogPropellorSpinCenter", 0.05f, true));
		Renderer->ChangeFrameAnimation("BulldogPropellorSpinCenter");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().SetLocalPosition({ 638, 25, (int)ZOrder::NPC - 5 });
	}


	{
		GameEngineTextureRenderer* Renderer = CreateComponent<GameEngineTextureRenderer>();

		Renderer->CreateFrameAnimationFolder("BulldogPropelloRingLeft", FrameAnimation_DESC("BulldogPropelloRingLeft", 0.1f, true));
		Renderer->ChangeFrameAnimation("BulldogPropelloRingLeft");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().SetLocalPosition({ 240, 100, (int)ZOrder::NPC + 1});
	}

	{
		GameEngineTextureRenderer* Renderer = CreateComponent<GameEngineTextureRenderer>();

		Renderer->CreateFrameAnimationFolder("BulldogPropellorTipLeft", FrameAnimation_DESC("BulldogPropellorTipLeft", 0.1f, true));
		Renderer->ChangeFrameAnimation("BulldogPropellorTipLeft");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().SetLocalPosition({ 240, 100, (int)ZOrder::NPC - 1 });
	}

	{
		GameEngineTextureRenderer* Renderer = CreateComponent<GameEngineTextureRenderer>();

		Renderer->CreateFrameAnimationFolder("BulldogPropellorSpinLeft", FrameAnimation_DESC("BulldogPropellorSpinLeft", 0.05f, true));
		Renderer->ChangeFrameAnimation("BulldogPropellorSpinLeft");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().SetLocalPosition({ 240, 100, (int)ZOrder::NPC });
	}

	{
		GameEngineTextureRenderer* Renderer = CreateComponent<GameEngineTextureRenderer>();

		Renderer->CreateFrameAnimationFolder("BulldogPropellorTipRight", FrameAnimation_DESC("BulldogPropellorTipRight", 0.1f, true));
		Renderer->ChangeFrameAnimation("BulldogPropellorTipRight");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().SetLocalPosition({ 1040, 100, (int)ZOrder::NPC - 1 });
	}

	{
		GameEngineTextureRenderer* Renderer = CreateComponent<GameEngineTextureRenderer>();

		Renderer->CreateFrameAnimationFolder("BulldogPropelloRingLeft", FrameAnimation_DESC("BulldogPropelloRingLeft", 0.1f, true));
		Renderer->ChangeFrameAnimation("BulldogPropelloRingLeft");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().PixLocalNegativeX();
		Renderer->GetTransform().SetLocalPosition({ 1040, 100, (int)ZOrder::NPC + 1});
	}
	{
		GameEngineTextureRenderer* Renderer = CreateComponent<GameEngineTextureRenderer>();

		Renderer->CreateFrameAnimationFolder("BulldogPropellorSpinRight", FrameAnimation_DESC("BulldogPropellorSpinRight", 0.05f, true));
		Renderer->ChangeFrameAnimation("BulldogPropellorSpinRight");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().SetLocalPosition({ 1045, 105, (int)ZOrder::NPC });
	}

	{
		GameEngineTextureRenderer* Renderer = CreateComponent<GameEngineTextureRenderer>();

		Renderer->CreateFrameAnimationFolder("BulldogPlaneFlapLeftA", FrameAnimation_DESC("BulldogPlaneFlapLeftA", 0.1f, true));
		Renderer->ChangeFrameAnimation("BulldogPlaneFlapLeftA");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().SetLocalPosition({ 430, 170, (int)ZOrder::NPC + 2 });
	}

	{
		GameEngineTextureRenderer* Renderer = CreateComponent<GameEngineTextureRenderer>();

		Renderer->CreateFrameAnimationFolder("BulldogPlaneFlapLeftB", FrameAnimation_DESC("BulldogPlaneFlapLeftB", 0.1f, true));
		Renderer->ChangeFrameAnimation("BulldogPlaneFlapLeftB");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().SetLocalPosition({ 120, 190, (int)ZOrder::NPC + 2 });
	}

	{
		GameEngineTextureRenderer* Renderer = CreateComponent<GameEngineTextureRenderer>();

		Renderer->CreateFrameAnimationFolder("BulldogPlaneFlapRightA", FrameAnimation_DESC("BulldogPlaneFlapRightA", 0.1f, true));
		Renderer->ChangeFrameAnimation("BulldogPlaneFlapRightA");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().SetLocalPosition({ 860, 170, (int)ZOrder::NPC + 2 });
	}

	{
		GameEngineTextureRenderer* Renderer = CreateComponent<GameEngineTextureRenderer>();

		Renderer->CreateFrameAnimationFolder("BulldogPlaneFlapRightB", FrameAnimation_DESC("BulldogPlaneFlapRightB", 0.1f, true));
		Renderer->ChangeFrameAnimation("BulldogPlaneFlapRightB");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().SetLocalPosition({ 1160, 190, (int)ZOrder::NPC + 2 });
	}

	{
		BossBulldog = GetLevel()->CreateActor<Bulldog>();
		BossBulldog->SetParent(this);
		BossBulldog->GetTransform().SetLocalPosition({ 640, 0, (int)ZOrder::NPC - 2 });
	}

	{
		Ph1Dog* DogFightPh1Dog = GetLevel()->CreateActor<Ph1Dog>();
		DogFightPh1Dog->SetParent(this);
		DogFightPh1Dog->GetTransform().SetLocalPosition({ 640, 0, (int)ZOrder::NPC - 2 });
	}
}

void BulldogPlane::Update(float _DeltaTime)
{
}

void BulldogPlane::End()
{
}
