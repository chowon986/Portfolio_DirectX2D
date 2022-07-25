#include "PreCompile.h"
#include "HourglassLevel.h"
#include <GameEngineCore/GameEngineTextureRenderer.h>
#include "Background.h"
#include <GameEngineCore/GEngine.h>
#include <GameEngineContents/Enums.h>
#include <GameEngineCore/GameEngineCameraActor.h>
#include <functional>

HourglassLevel::HourglassLevel()
{
}

HourglassLevel::~HourglassLevel()
{
}

void HourglassLevel::Start()
{
	GameEngineCameraActor* CameraActor = CreateActor<GameEngineCameraActor>();
	CameraActor->GetCameraComponent()->SetProjectionMode(CAMERAPROJECTIONMODE::Orthographic);
	CameraActor->GetTransform().SetLocalPosition({ 0.0f, 0.0f, -500.0f });

	Background* Hourglass = CreateActor<Background>(GameObjectGroup::UI);
	GameEngineTextureRenderer* Renderer = Hourglass->CreateComponent<GameEngineTextureRenderer>();
	Renderer->CreateFrameAnimationFolder("Hourglass", FrameAnimation_DESC("13HourglassLevel", 0.1f));
	Renderer->AnimationBindEnd("Hourglass", &HourglassLevel::EndAnimation, this);
	Renderer->ChangeFrameAnimation("Hourglass");
	Renderer->GetTransform().SetLocalScale({ 191,326,100 });
	Renderer->GetTransform().SetLocalPosition({ 500,-180,100 });
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
