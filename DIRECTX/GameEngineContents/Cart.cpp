#include "PreCompile.h"
#include "Cart.h"
#include "WorldMapLevel.h"

Cart::Cart()
	: TutorialEntryBubbleOn(false)
{
}

Cart::~Cart()
{
}

void Cart::Start()
{
	PortalBase::Start();

	Renderer->GetTransform().SetLocalScale({ 176,179,1 });
	Renderer->CreateFrameAnimationFolder("Cart", FrameAnimation_DESC("Cart", 0.1f));
	Renderer->ChangeFrameAnimation("Cart");
	Renderer->SetPivot(PIVOTMODE::CENTER);

	Collision->GetTransform().SetLocalScale({ 100.0f, 200.0f, 1.0f });
}

void Cart::Update(float _DeltaTime)
{
	PortalBase::Update(_DeltaTime);

	if (true == TutorialEntryBubbleOn)
	{
		if (GameEngineInput::GetInst()->IsDown("Select"))
		{
			GameEngineSound::SoundPlayOneShot("sfx_WorldMap_LevelSelect_DiffucultySettings_Appear.wav");
			GameEngineSound::SoundPlayOneShot("sfx_worldmap_level_menu_up.wav");
			GEngine::ChangeLevel("Tutorial");
			TutorialEntryBubbleOn = false;
		}
	}
}

void Cart::End()
{
}

CollisionReturn Cart::OnPortalCollision(GameEngineCollision* _This, GameEngineCollision* _Other)
{
	if (true == GameEngineInput::GetInst()->IsDown("EnterMap"))
	{
		if (true == GameEngineInput::GetInst()->IsDown("EnterMap"))
		{
			if (WorldMapLevel* Level = dynamic_cast<WorldMapLevel*>(GetLevel()))
			{
				if (nullptr != Level->TutorialEntryBubbleRenderer)
				{
					Level->TutorialEntryBubbleRenderer->On();
					TutorialEntryBubbleOn = true;
				}
			}
		}
	}
	return CollisionReturn::ContinueCheck;
}