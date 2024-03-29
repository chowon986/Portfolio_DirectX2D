#include "PreCompile.h"
#include "BulldogPlane.h"
#include "Bulldog.h"
#include "Ph1Dog.h"
#include <vector>
#include "BulldogPlanePuff.h"

BulldogPlane::BulldogPlane()
	: Player(nullptr)
	, BossBulldog(nullptr)
	, CanMoveLeftRight(false)
	, OnDeath(false)
	, ColMapImage(nullptr)
	, ColMapTexture(nullptr)
	, DogFightPh1Dog(nullptr)
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
		Renderer->CreateFrameAnimationFolder("Nothing", FrameAnimation_DESC("Nothing", 0.1f, false));
		Renderer->ChangeFrameAnimation("BulldogPlaneFront");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().SetLocalPosition({ 640, 65, (int)ZOrder::NPC - 1 });
		AllBulldogPlaneRenderer.push_back(Renderer);
	}
	{
		GameEngineTextureRenderer* Renderer = CreateComponent<GameEngineTextureRenderer>();
		Renderer->CreateFrameAnimationFolder("BulldogPlaneWingLeft", FrameAnimation_DESC("BulldogPlaneWingLeft", 0.1f, true));
		Renderer->CreateFrameAnimationFolder("Nothing", FrameAnimation_DESC("Nothing", 0.1f, false));
		Renderer->ChangeFrameAnimation("BulldogPlaneWingLeft");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().SetLocalPosition({ 275, 200, (int)ZOrder::NPC + 3 });
		AllBulldogPlaneRenderer.push_back(Renderer);
		WingRenderers.push_back(Renderer);
	}

	{
		GameEngineTextureRenderer* Renderer = CreateComponent<GameEngineTextureRenderer>();

		Renderer->CreateFrameAnimationFolder("BulldogPlaneWingRight", FrameAnimation_DESC("BulldogPlaneWingRight", 0.1f, true));
		Renderer->CreateFrameAnimationFolder("Nothing", FrameAnimation_DESC("Nothing", 0.1f, false));
		Renderer->ChangeFrameAnimation("BulldogPlaneWingRight");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().SetLocalPosition({ 1010, 200, (int)ZOrder::NPC + 3 });
		AllBulldogPlaneRenderer.push_back(Renderer);
		WingRenderers.push_back(Renderer);
	}

	{
		GameEngineTextureRenderer* Renderer = CreateComponent<GameEngineTextureRenderer>();

		Renderer->CreateFrameAnimationFolder("BulldogPlaneBack", FrameAnimation_DESC("BulldogPlaneBack", 0.1f, true));
		Renderer->CreateFrameAnimationFolder("Nothing", FrameAnimation_DESC("Nothing", 0.1f, false));
		Renderer->ChangeFrameAnimation("BulldogPlaneBack");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().SetLocalPosition({ 640, 200, (int)ZOrder::NPC + 2 });
		AllBulldogPlaneRenderer.push_back(Renderer);
	}

	{
		GameEngineTextureRenderer* Renderer = CreateComponent<GameEngineTextureRenderer>();

		Renderer->CreateFrameAnimationFolder("BulldogPlaneTail", FrameAnimation_DESC("BulldogPlaneTail", 0.1f, true));
		Renderer->CreateFrameAnimationFolder("Nothing", FrameAnimation_DESC("Nothing", 0.1f, false));
		Renderer->ChangeFrameAnimation("BulldogPlaneTail");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().SetLocalPosition({ 640, 300, (int)ZOrder::NPC + 4 });
		AllBulldogPlaneRenderer.push_back(Renderer);
	}

	{
		GameEngineTextureRenderer* Renderer = CreateComponent<GameEngineTextureRenderer>();

		Renderer->CreateFrameAnimationFolder("BulldogPropellorRingCenter", FrameAnimation_DESC("BulldogPropellorRingCenter", 0.1f, true));
		Renderer->CreateFrameAnimationFolder("Nothing", FrameAnimation_DESC("Nothing", 0.1f, false));
		Renderer->ChangeFrameAnimation("BulldogPropellorRingCenter");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().SetLocalPosition({ 640, 20, (int)ZOrder::NPC - 4 });
		AllBulldogPlaneRenderer.push_back(Renderer);
	}

	{
		GameEngineTextureRenderer* Renderer = CreateComponent<GameEngineTextureRenderer>();

		Renderer->CreateFrameAnimationFolder("BulldogPropellorTipCenter", FrameAnimation_DESC("BulldogPropellorTipCenter", 0.1f, true));
		Renderer->CreateFrameAnimationFolder("Nothing", FrameAnimation_DESC("Nothing", 0.1f, false));
		Renderer->ChangeFrameAnimation("BulldogPropellorTipCenter");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().SetLocalPosition({ 640, 20, (int)ZOrder::NPC - 6 });
		AllBulldogPlaneRenderer.push_back(Renderer);
	}

	{
		GameEngineTextureRenderer* Renderer = CreateComponent<GameEngineTextureRenderer>();

		Renderer->CreateFrameAnimationFolder("BulldogPropellorSpinCenter", FrameAnimation_DESC("BulldogPropellorSpinCenter", 0.05f, true));
		Renderer->CreateFrameAnimationFolder("Nothing", FrameAnimation_DESC("Nothing", 0.1f, false));
		Renderer->ChangeFrameAnimation("BulldogPropellorSpinCenter");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().SetLocalPosition({ 638, 25, (int)ZOrder::NPC - 5 });
		AllBulldogPlaneRenderer.push_back(Renderer);
	}


	{
		GameEngineTextureRenderer* Renderer = CreateComponent<GameEngineTextureRenderer>();

		Renderer->CreateFrameAnimationFolder("BulldogPropelloRingLeft", FrameAnimation_DESC("BulldogPropelloRingLeft", 0.1f, true));
		Renderer->CreateFrameAnimationFolder("Nothing", FrameAnimation_DESC("Nothing", 0.1f, false));
		Renderer->ChangeFrameAnimation("BulldogPropelloRingLeft");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().SetLocalPosition({ 240, 100, (int)ZOrder::NPC + 1 });
		AllBulldogPlaneRenderer.push_back(Renderer);
	}

	{
		GameEngineTextureRenderer* Renderer = CreateComponent<GameEngineTextureRenderer>();

		Renderer->CreateFrameAnimationFolder("BulldogPropellorTipLeft", FrameAnimation_DESC("BulldogPropellorTipLeft", 0.1f, true));
		Renderer->CreateFrameAnimationFolder("Nothing", FrameAnimation_DESC("Nothing", 0.1f, false));
		Renderer->ChangeFrameAnimation("BulldogPropellorTipLeft");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().SetLocalPosition({ 240, 100, (int)ZOrder::NPC - 1 });
		AllBulldogPlaneRenderer.push_back(Renderer);
	}

	{
		GameEngineTextureRenderer* Renderer = CreateComponent<GameEngineTextureRenderer>();

		Renderer->CreateFrameAnimationFolder("BulldogPropellorSpinLeft", FrameAnimation_DESC("BulldogPropellorSpinLeft", 0.05f, true));
		Renderer->CreateFrameAnimationFolder("Nothing", FrameAnimation_DESC("Nothing", 0.1f, false));
		Renderer->ChangeFrameAnimation("BulldogPropellorSpinLeft");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().SetLocalPosition({ 240, 100, (int)ZOrder::NPC });
		AllBulldogPlaneRenderer.push_back(Renderer);
	}

	{
		GameEngineTextureRenderer* Renderer = CreateComponent<GameEngineTextureRenderer>();

		Renderer->CreateFrameAnimationFolder("BulldogPropellorTipRight", FrameAnimation_DESC("BulldogPropellorTipRight", 0.1f, true));
		Renderer->CreateFrameAnimationFolder("Nothing", FrameAnimation_DESC("Nothing", 0.1f, false));
		Renderer->ChangeFrameAnimation("BulldogPropellorTipRight");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().SetLocalPosition({ 1040, 100, (int)ZOrder::NPC - 1 });
		AllBulldogPlaneRenderer.push_back(Renderer);
	}

	{
		GameEngineTextureRenderer* Renderer = CreateComponent<GameEngineTextureRenderer>();

		Renderer->CreateFrameAnimationFolder("BulldogPropelloRingLeft", FrameAnimation_DESC("BulldogPropelloRingLeft", 0.1f, true));
		Renderer->CreateFrameAnimationFolder("Nothing", FrameAnimation_DESC("Nothing", 0.1f, false));
		Renderer->ChangeFrameAnimation("BulldogPropelloRingLeft");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().PixLocalNegativeX();
		Renderer->GetTransform().SetLocalPosition({ 1040, 100, (int)ZOrder::NPC + 1 });
		AllBulldogPlaneRenderer.push_back(Renderer);
	}

	{
		GameEngineTextureRenderer* Renderer = CreateComponent<GameEngineTextureRenderer>();

		Renderer->CreateFrameAnimationFolder("BulldogPropellorSpinRight", FrameAnimation_DESC("BulldogPropellorSpinRight", 0.05f, true));
		Renderer->CreateFrameAnimationFolder("Nothing", FrameAnimation_DESC("Nothing", 0.1f, false));
		Renderer->ChangeFrameAnimation("BulldogPropellorSpinRight");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().SetLocalPosition({ 1045, 105, (int)ZOrder::NPC });
		AllBulldogPlaneRenderer.push_back(Renderer);
	}

	{
		GameEngineTextureRenderer* Renderer = CreateComponent<GameEngineTextureRenderer>();

		Renderer->CreateFrameAnimationFolder("BulldogPlaneFlapLeftA", FrameAnimation_DESC("BulldogPlaneFlapLeftA", 0.1f, true));
		Renderer->CreateFrameAnimationFolder("Nothing", FrameAnimation_DESC("Nothing", 0.1f, false));
		Renderer->ChangeFrameAnimation("BulldogPlaneFlapLeftA");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().SetLocalPosition({ 430, 170, (int)ZOrder::NPC + 2 });
		AllBulldogPlaneRenderer.push_back(Renderer);
	}

	{
		GameEngineTextureRenderer* Renderer = CreateComponent<GameEngineTextureRenderer>();

		Renderer->CreateFrameAnimationFolder("BulldogPlaneFlapLeftB", FrameAnimation_DESC("BulldogPlaneFlapLeftB", 0.1f, true));
		Renderer->CreateFrameAnimationFolder("Nothing", FrameAnimation_DESC("Nothing", 0.1f, false));
		Renderer->ChangeFrameAnimation("BulldogPlaneFlapLeftB");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().SetLocalPosition({ 120, 190, (int)ZOrder::NPC + 2 });
		AllBulldogPlaneRenderer.push_back(Renderer);
	}

	{
		GameEngineTextureRenderer* Renderer = CreateComponent<GameEngineTextureRenderer>();

		Renderer->CreateFrameAnimationFolder("BulldogPlaneFlapRightA", FrameAnimation_DESC("BulldogPlaneFlapRightA", 0.1f, true));
		Renderer->CreateFrameAnimationFolder("Nothing", FrameAnimation_DESC("Nothing", 0.1f, false));
		Renderer->ChangeFrameAnimation("BulldogPlaneFlapRightA");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().SetLocalPosition({ 860, 170, (int)ZOrder::NPC + 2 });
		AllBulldogPlaneRenderer.push_back(Renderer);
	}

	{
		GameEngineTextureRenderer* Renderer = CreateComponent<GameEngineTextureRenderer>();
		Renderer->CreateFrameAnimationFolder("BulldogPlaneFlapRightB", FrameAnimation_DESC("BulldogPlaneFlapRightB", 0.1f, true));
		Renderer->CreateFrameAnimationFolder("Nothing", FrameAnimation_DESC("Nothing", 0.1f, false));
		Renderer->ChangeFrameAnimation("BulldogPlaneFlapRightB");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().SetLocalPosition({ 1160, 190, (int)ZOrder::NPC + 2 });
		AllBulldogPlaneRenderer.push_back(Renderer);
	}

	{
		DogFightPh1Dog = GetLevel()->CreateActor<Ph1Dog>();
		DogFightPh1Dog->SetParent(this);
		DogFightPh1Dog->GetTransform().SetLocalPosition({ 640, 0, (int)ZOrder::NPC - 2 });

		BossBulldog = GetLevel()->CreateActor<Bulldog>();
		BossBulldog->SetParent(this);
		BossBulldog->GetTransform().SetLocalPosition({ 640, 0, (int)ZOrder::NPC - 2 });
		BossBulldog->SetPh1Dog(DogFightPh1Dog);
	}

	Direction = float4::LEFT;
}

void BulldogPlane::Update(float _DeltaTime)
{
	PuffDeltaTime += _DeltaTime;
	if (PuffDeltaTime > 1.5 && false == OnDeath)
	{
		float4 MyPos = GetTransform().GetWorldPosition();
		BulldogPlanePuff* PuffLeft = GetLevel()->CreateActor<BulldogPlanePuff>();
		PuffLeft->GetTransform().SetLocalPosition({ MyPos.x + 360.0f, -50.0f });
		PuffLeft->GetRenderer()->ChangeFrameAnimation("BulldogPlanePuffA");
		PuffLeft->SetDirection({ float4::RIGHT * 2 + float4::UP });
	
		BulldogPlanePuff* PuffRight = GetLevel()->CreateActor<BulldogPlanePuff>();
		PuffRight->GetTransform().SetLocalPosition({MyPos.x + 920, -50.0f });
		PuffRight->GetRenderer()->ChangeFrameAnimation("BulldogPlanePuffB");
		PuffRight->SetDirection({ float4::LEFT * 2 + float4::UP });
		PuffDeltaTime = 0.0f;
	}

	if (BossBulldog->GetState() == InGameMonsterState::Die)
	{
		for (int i = 0; i< AllBulldogPlaneRenderer.size(); i++)
		{
			AllBulldogPlaneRenderer[i]->ChangeFrameAnimation("Nothing");
		}

		if (DogFightPh1Dog != nullptr)
		{
			DogFightPh1Dog->Death();
			OnDeath = true;
			DogFightPh1Dog = nullptr;
		}
	}

	if (ColMapImage == nullptr)
	{
		ColMapImage = GetLevel()->GetMainColMapImage();
		ColMapImage->SetPivot(PIVOTMODE::LEFTTOP);
	}

	if (ColMapTexture == nullptr)
	{
		ColMapTexture = ColMapImage->GetCurTexture();
	}
	//GameEngineDebug::DrawBox(Collision->GetTransform(), { 1.0f, 0.0f,0.0f, 0.5f });

	if (WingRenderers[0] == nullptr || WingRenderers[1] == nullptr)
	{
		return;
	}

	if (true == ColMapTexture->GetPixelToFloat4(WingRenderers[0]->GetTransform().GetWorldPosition().ix(), -WingRenderers[0]->GetTransform().GetWorldPosition().iy()).CompareInt3D(float4::BLACK) ||
		true == ColMapTexture->GetPixelToFloat4(WingRenderers[1]->GetTransform().GetWorldPosition().ix(), -WingRenderers[1]->GetTransform().GetWorldPosition().iy()).CompareInt3D(float4::BLACK))
	{
		Direction.x *= -1;
	}

	if (BossBulldog->GetState() == InGameMonsterState::Idle && CanMoveLeftRight == true)
	{
		GetTransform().SetLocalMove(Direction * _DeltaTime * 200);
	}
}

void BulldogPlane::End()
{
}
