#include "PreCompile.h"
#include "Shop.h"
#include "GameEngineCore/GameEngineCollision.h"
#include "WorldMapCuphead.h"
#include "WorldMapLevel.h"

Shop::Shop()
	: ShopEntryBubbleOn(false)
{
}

Shop::~Shop()
{
}

void Shop::Start()
{
	PortalBase::Start();

	Renderer->CreateFrameAnimationFolder("Shop", FrameAnimation_DESC("Shop", 0.1f));
	Renderer->ChangeFrameAnimation("Shop");
	Renderer->GetTransform().SetLocalScale({ 222,259,100 });
	Renderer->SetPivot(PIVOTMODE::CENTER);

	Collision->GetTransform().SetLocalScale({ 300.0f, 200.0f, 1.0f });
}

void Shop::Update(float _DeltaTime)
{
	PortalBase::Update(_DeltaTime);
	Collision->IsCollision(CollisionType::CT_AABB2D, ObjectOrder::PC, CollisionType::CT_AABB2D, std::bind(&Shop::OnPortalCollision, this, std::placeholders::_1, std::placeholders::_2));
	
	if (true == ShopEntryBubbleOn)
	{
		if (GameEngineInput::GetInst()->IsDown("Select"))
		{
			GameEngineSound::SoundPlayOneShot("sfx_WorldMap_LevelSelect_DiffucultySettings_Appear.wav");
			GameEngineSound::SoundPlayOneShot("sfx_worldmap_level_menu_up.wav");
			GEngine::ChangeLevel("Shop");
			ShopEntryBubbleOn = false;
		}
	}

}

void Shop::End()
{
}

CollisionReturn Shop::OnPortalCollision(GameEngineCollision* _This, GameEngineCollision* _Other)
{

	if (true == GameEngineInput::GetInst()->IsDown("EnterMap"))
	{
		if (WorldMapLevel* Level = dynamic_cast<WorldMapLevel*>(GetLevel()))
		{
			if (nullptr != Level->ShopEntryBubbleRenderer)
			{
				Level->ShopEntryBubbleRenderer->On();
				ShopEntryBubbleOn = true;
			}
		}
	}

	return CollisionReturn::ContinueCheck;
}