#include "PreCompile.h"
#include "PlayerCard.h"
#include "IInGameCharacterBase.h"
#include "InGameCuphead.h"

PlayerCard::PlayerCard()
{
}

PlayerCard::~PlayerCard()
{
}

void PlayerCard::Start()
{
	Renderer = CreateComponent<GameEngineTextureRenderer>();
	Renderer->CreateFrameAnimationFolder("CardBack", FrameAnimation_DESC("CardBack", 0.1f, false));
	Renderer->CreateFrameAnimationFolder("CardOpen", FrameAnimation_DESC("CardOpen", 0.1f, false));
	Renderer->ChangeFrameAnimation("CardBack");
	Renderer->ChangeCamera(CAMERAORDER::DARKNESSCAMERA);
	Renderer->SetPivot(PIVOTMODE::BOT);
}

void PlayerCard::Update(float _DeltaTime)
{
	if (Player->GetGauge() != 0 && Renderer->GetTransform().GetWorldScale().y > 0)
	{
		Renderer->On();
	}

	if (static_cast<int>(Player->GetGauge()) == 0 && Renderer->GetTransform().GetWorldScale().y <= 0)
	{
		Renderer->Off();
	}
}

void PlayerCard::End()
{
}
