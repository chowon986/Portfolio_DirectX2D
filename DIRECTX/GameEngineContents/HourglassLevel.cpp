#include "PreCompile.h"
#include "HourglassLevel.h"
#include <GameEngineCore/GameEngineTextureRenderer.h>
#include "Background.h"
#include <GameEngineCore/GEngine.h>
#include <GameEngineContents/Enums.h>
#include <functional>

HourglassLevel::HourglassLevel()
{
}

HourglassLevel::~HourglassLevel()
{
}

void HourglassLevel::Start()
{

	{
		Background* HourglassBackground = CreateActor<Background>(GameObjectGroup::UI);
		GameEngineTextureRenderer* Renderer = HourglassBackground->CreateComponent<GameEngineTextureRenderer>();
		Renderer->SetTexture("Loading_background.png");
		Renderer->ScaleToTexture();
	}

	{
		Background* Hourglass = CreateActor<Background>(GameObjectGroup::UI);
		GameEngineTextureRenderer* Renderer = Hourglass->CreateComponent<GameEngineTextureRenderer>();
		Renderer->CreateFrameAnimationFolder("Hourglass", FrameAnimation_DESC("13HourglassLevel", 0.05f));
		Renderer->AnimationBindEnd("Hourglass", &HourglassLevel::EndAnimation, this);
		Renderer->ChangeFrameAnimation("Hourglass");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().SetLocalPosition({ 500,-180,-100 });
	}
}

void HourglassLevel::Update(float _DeltaTime)
{
	if (true == GameEngineInput::GetInst()->IsDown("LevelChange"))
	{
		GEngine::ChangeLevel("WorldMap");
	}
}

void HourglassLevel::End()
{
}

void HourglassLevel::EndAnimation(const FrameAnimation_DESC& _Info)
{
	GEngine::ChangeLevel("WorldMap");
}
