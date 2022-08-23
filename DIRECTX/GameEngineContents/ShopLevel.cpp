#include "PreCompile.h"
#include "ShopLevel.h"
#include "Background.h"
#include "Enums.h"
#include "Pig.h"
#include <functional>
#include <GameEngineCore/GameEngineTextureRenderer.h>


ShopLevel::ShopLevel()
	: IrisRenderer(nullptr)
	, IsLeftDrawerOpen(false)
	, IsLeftDrawerOpened(false)
	, OnceCheck(false)
{
}

ShopLevel::~ShopLevel()
{
}

void ShopLevel::Start()
{

	{
		Background* ShopBackground = CreateActor<Background>(GameObjectGroup::UI);
		GameEngineTextureRenderer* Renderer = ShopBackground->CreateComponent<GameEngineTextureRenderer>();
		Renderer->SetTexture("dlc_shop_bg.png");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().SetLocalPosition({ 0, 200, (int)ZOrder::Background });
	}

	{
		Background* TableChalkboard = CreateActor<Background>(GameObjectGroup::UI);
		GameEngineTextureRenderer* Renderer = TableChalkboard->CreateComponent<GameEngineTextureRenderer>();
		Renderer->SetTexture("shop_table_chalkboard.png");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().SetLocalPosition({ 0, -210, (int)ZOrder::Background - 2 });
	}

	{
		Background* LeftDrawer = CreateActor<Background>(GameObjectGroup::UI);
		LeftDrawerRenderer = LeftDrawer->CreateComponent<GameEngineTextureRenderer>();
		LeftDrawerRenderer->SetTexture("dlc_shop_drawer_left.png");
		LeftDrawerRenderer->ScaleToTexture();
		LeftDrawerRenderer->GetTransform().SetLocalPosition({ -320, -210, (int)ZOrder::Background - 2 });
	}

	{
		Background* RightDrawer = CreateActor<Background>(GameObjectGroup::UI);
		GameEngineTextureRenderer* Renderer = RightDrawer->CreateComponent<GameEngineTextureRenderer>();
		Renderer->SetTexture("dlc_shop_drawer_Right.png");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().SetLocalPosition({ 320, -210, (int)ZOrder::Background - 2 });
	}

	{
		Background* ShopTable = CreateActor<Background>(GameObjectGroup::UI);
		GameEngineTextureRenderer* Renderer = ShopTable->CreateComponent<GameEngineTextureRenderer>();
		Renderer->SetTexture("shop_table.png");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().SetLocalPosition({ 0, -195, (int)ZOrder::Background - 5 });
	}

	{
		ShopPig = CreateActor<Pig>(GameObjectGroup::UI);
	}

	{
		Background* Iris = CreateActor<Background>(GameObjectGroup::UI);
		IrisRenderer = Iris->CreateComponent<GameEngineTextureRenderer>();
		IrisRenderer->GetTransform().SetLocalScale({ 1280,720,1 });
		IrisRenderer->GetTransform().SetLocalPosition({ 0,0,(int)ZOrder::UI });
		IrisRenderer->CreateFrameAnimationFolder("IrisAStart", FrameAnimation_DESC("IrisA", 0.1f, false));
		IrisRenderer->AnimationBindEnd("IrisAStart", std::bind(&ShopLevel::EndIrisAnimation, this, std::placeholders::_1));
		IrisRenderer->ChangeFrameAnimation("IrisAStart");
	}
	StartLerpValueX = { -320.0f, -850.0f };
	EndLerpValueX = { -850.0f, -780.0f };
	Phase = ShopPhase::None;


}

void ShopLevel::Update(float _DeltaTime)
{
	if (OnceCheck == true)
	{
		ElapsedTime += _DeltaTime;
		ElapsedTime = ElapsedTime / 1.0f;
		float LeftDrawerPosX = LeftDrawerRenderer->GetTransform().GetLocalPosition().x;

		if (IsLeftDrawerOpened == false)
		{
			if (StartLerpValueX.y == LeftDrawerPosX)
			{
				IsLeftDrawerOpened = true;
				ElapsedTime = 0.0f;
			}

			EndPosition = float4::LerpLimit(StartLerpValueX.x, StartLerpValueX.y, ElapsedTime);
		}
		else
		{
			if (EndLerpValueX.y == LeftDrawerPosX)
			{
				OnceCheck = false;
				Phase = ShopPhase::Open;
			}
			EndPosition = float4::LerpLimit(EndLerpValueX.x, EndLerpValueX.y, ElapsedTime);
		}

		LeftDrawerRenderer->GetTransform().SetLocalPosition({ EndPosition.x, -210, (int)ZOrder::Background - 2 });
	}

	if (Phase == ShopPhase::Open)
	{

	}
}

void ShopLevel::End()
{
}

void ShopLevel::EndIrisAnimation(const FrameAnimation_DESC& _Info)
{
	ShopPig->GetRenderer()->ChangeFrameAnimation("Welcome");
	OnceCheck = true;
}
