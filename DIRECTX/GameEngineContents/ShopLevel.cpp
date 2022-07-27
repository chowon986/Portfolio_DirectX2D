#include "PreCompile.h"
#include "ShopLevel.h"
#include "Background.h"
#include "Enums.h"
#include "Pig.h"
#include <functional>
#include <GameEngineCore/GameEngineTextureRenderer.h>


ShopLevel::ShopLevel()
	: IrisRenderer(nullptr)
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
		Pig* ShopPig = CreateActor<Pig>(GameObjectGroup::UI);
	}

	{
		Background* Iris = CreateActor<Background>(GameObjectGroup::UI);
		IrisRenderer = Iris->CreateComponent<GameEngineTextureRenderer>();
		IrisRenderer->GetTransform().SetLocalScale({ 1280,720,1 });
		IrisRenderer->GetTransform().SetLocalPosition({ 0,0,(int)ZOrder::UI });
		IrisRenderer->CreateFrameAnimationFolder("IrisAStart", FrameAnimation_DESC("IrisA", 0.1f, false));
		IrisRenderer->ChangeFrameAnimation("IrisAStart");
	}


}

void ShopLevel::Update(float _DeltaTime)
{
	Time += _DeltaTime;

	if (Time < 2.5)
	{
	LeftDrawerRenderer->GetTransform().SetWorldMove(LeftDrawerRenderer->GetTransform().GetLeftVector() * 200 * GameEngineTime::GetDeltaTime());
	}
}

void ShopLevel::End()
{
}
