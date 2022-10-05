#include "PreCompile.h"
#include "Dogfight.h"
#include "WorldMapLevel.h"

Dogfight::Dogfight()
	: DogFightEntryBubbleOn(false)
{
}

Dogfight::~Dogfight()
{
}

void Dogfight::Start()
{
	PortalBase::Start();

	Renderer->CreateFrameAnimationFolder("Dogfight", FrameAnimation_DESC("Dogfight", 0.1f));
	Renderer->ChangeFrameAnimation("Dogfight");
	Renderer->GetTransform().SetLocalScale({ 189,163,1 });
	Renderer->SetPivot(PIVOTMODE::CENTER);

	Collision->GetTransform().SetLocalScale({ 100.0f, 150.0f, 1.0f });

}

void Dogfight::Update(float _DeltaTime)
{
	PortalBase::Update(_DeltaTime);

	if (true == DogFightEntryBubbleOn)
	{
		if (GameEngineInput::GetInst()->IsDown("Select"))
		{
			GEngine::ChangeLevel("DogFight");
			DogFightEntryBubbleOn = false;
		}
	}
}

void Dogfight::End()
{
}

CollisionReturn Dogfight::OnPortalCollision(GameEngineCollision* _This, GameEngineCollision* _Other)
{
	if (true == GameEngineInput::GetInst()->IsDown("EnterMap"))
	{
		if (WorldMapLevel* Level = dynamic_cast<WorldMapLevel*>(GetLevel()))
		{
			if (nullptr != Level->DogFightEntryBubbleRenderer)
			{
				Level->DogFightEntryBubbleRenderer->On();
				DogFightEntryBubbleOn = true;
			}
		}
	}
	return CollisionReturn::ContinueCheck;
}