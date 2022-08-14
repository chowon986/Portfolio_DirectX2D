#include "PreCompile.h"
#include "DogCopter.h"
#include "Bulldog.h"
#include "Ph1Dog.h"

DogCopter::DogCopter()
	:Player(nullptr)
{
}

DogCopter::~DogCopter()
{
}

void DogCopter::Start()
{
	{
		GameEngineTextureRenderer* Renderer = CreateComponent<GameEngineTextureRenderer>();
		Renderer->CreateFrameAnimationFolder("DogCopterFront", FrameAnimation_DESC("DogCopterFront", 0.1f, true));
		Renderer->ChangeFrameAnimation("DogCopterFront");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().SetLocalPosition({ 640, 65, (int)ZOrder::NPC - 1 });
	}
	{
		GameEngineTextureRenderer* Renderer = CreateComponent<GameEngineTextureRenderer>();
		Renderer->CreateFrameAnimationFolder("DogCopterWingLeft", FrameAnimation_DESC("DogCopterWingLeft", 0.1f, true));
		Renderer->ChangeFrameAnimation("DogCopterWingLeft");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().SetLocalPosition({ 275, 200, (int)ZOrder::NPC + 3 });
	}

	{
		GameEngineTextureRenderer* Renderer = CreateComponent<GameEngineTextureRenderer>();

		Renderer->CreateFrameAnimationFolder("DogCopterWingRight", FrameAnimation_DESC("DogCopterWingRight", 0.1f, true));
		Renderer->ChangeFrameAnimation("DogCopterWingRight");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().SetLocalPosition({ 1010, 200, (int)ZOrder::NPC + 3 });
	}

	{
		GameEngineTextureRenderer* Renderer = CreateComponent<GameEngineTextureRenderer>();

		Renderer->CreateFrameAnimationFolder("DogCopterBack", FrameAnimation_DESC("DogCopterBack", 0.1f, true));
		Renderer->ChangeFrameAnimation("DogCopterBack");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().SetLocalPosition({ 640, 200, (int)ZOrder::NPC + 2 });
	}

	{
		GameEngineTextureRenderer* Renderer = CreateComponent<GameEngineTextureRenderer>();

		Renderer->CreateFrameAnimationFolder("DogCopterTail", FrameAnimation_DESC("DogCopterTail", 0.1f, true));
		Renderer->ChangeFrameAnimation("DogCopterTail");
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
		Renderer->GetTransform().SetLocalPosition({ 240, 100, (int)ZOrder::NPC + 1 });
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
		Renderer->GetTransform().SetLocalPosition({ 1040, 100, (int)ZOrder::NPC + 1 });
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

		Renderer->CreateFrameAnimationFolder("DogCopterFlapLeftA", FrameAnimation_DESC("DogCopterFlapLeftA", 0.1f, true));
		Renderer->ChangeFrameAnimation("DogCopterFlapLeftA");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().SetLocalPosition({ 430, 170, (int)ZOrder::NPC + 2 });
	}

	{
		GameEngineTextureRenderer* Renderer = CreateComponent<GameEngineTextureRenderer>();

		Renderer->CreateFrameAnimationFolder("DogCopterFlapLeftB", FrameAnimation_DESC("DogCopterFlapLeftB", 0.1f, true));
		Renderer->ChangeFrameAnimation("DogCopterFlapLeftB");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().SetLocalPosition({ 120, 190, (int)ZOrder::NPC + 2 });
	}

	{
		GameEngineTextureRenderer* Renderer = CreateComponent<GameEngineTextureRenderer>();

		Renderer->CreateFrameAnimationFolder("DogCopterFlapRightA", FrameAnimation_DESC("DogCopterFlapRightA", 0.1f, true));
		Renderer->ChangeFrameAnimation("DogCopterFlapRightA");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().SetLocalPosition({ 860, 170, (int)ZOrder::NPC + 2 });
	}

	{
		GameEngineTextureRenderer* Renderer = CreateComponent<GameEngineTextureRenderer>();

		Renderer->CreateFrameAnimationFolder("DogCopterFlapRightB", FrameAnimation_DESC("DogCopterFlapRightB", 0.1f, true));
		Renderer->ChangeFrameAnimation("DogCopterFlapRightB");
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

void DogCopter::Update(float _DeltaTime)
{
}

void DogCopter::End()
{
}
