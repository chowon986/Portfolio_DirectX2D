#include "PreCompile.h"
#include "WorldMapLevel.h"
#include "Background.h"
#include "WorldMapCuphead.h"
#include "Enums.h"
#include <GameEngineCore/GEngine.h>
#include <GameEngineCore/GameEngineCameraActor.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineCore/GameEngineTextureRenderer.h>

WorldMapLevel::WorldMapLevel()
{
}

WorldMapLevel::~WorldMapLevel()
{
}

void WorldMapLevel::Start()
{


	GameEngineCameraActor* CameraActor = CreateActor<GameEngineCameraActor>();
	CameraActor->GetCameraComponent()->SetProjectionMode(CAMERAPROJECTIONMODE::Orthographic);
	CameraActor->GetTransform().SetLocalPosition({ -1468.0f, -326.0f, -500.0f });


	{
		Background* OutsideOfMainLand = CreateActor<Background>(GameObjectGroup::UI);
		GameEngineTextureRenderer* Renderer = OutsideOfMainLand->CreateComponent<GameEngineTextureRenderer>();
		Renderer->SetTexture("dlc_water_multiply.png");
		Renderer->ScaleToTexture();
	}

	{
		Background* MainLand = CreateActor<Background>(GameObjectGroup::UI);
		GameEngineTextureRenderer* Renderer = MainLand->CreateComponent<GameEngineTextureRenderer>();
		Renderer->SetTexture("dlc_main_land.png");
		Renderer->ScaleToTexture();
	}

	{
		WorldMapCuphead* Cuphead = CreateActor<WorldMapCuphead>(GameObjectGroup::Player);
		Cuphead->GetTransform().SetLocalPosition({ -1473.0f, -296.0f, 100.0f, 0.0f });
	}
}

void WorldMapLevel::Update(float _DeltaTime)
{
	if (true == GameEngineInput::GetInst()->IsDown("LevelChange"))
	{
		//GEngine::ChangeLevel("Title");
	}

}


void WorldMapLevel::End()
{
	int a = 0;
}