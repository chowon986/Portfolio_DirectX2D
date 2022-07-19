#include "PreCompile.h"
#include "TitleLevel.h"
#include "Background.h"
#include "Enums.h"
#include <GameEngineCore/GEngine.h>
#include <GameEngineCore/GameEngineCameraActor.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineCore/GameEngineTextureRenderer.h>

TitleLevel::TitleLevel() 
{
}

TitleLevel::~TitleLevel() 
{
}

void TitleLevel::Start()
{

	GameEngineCameraActor* CameraActor = CreateActor<GameEngineCameraActor>();
	CameraActor->GetCameraComponent()->SetProjectionMode(CAMERAPROJECTIONMODE::Orthographic);
	CameraActor->GetTransform().SetLocalPosition({ 0.0f, 0.0f, -500.0f });

	{
		// Background
		Background* Title = CreateActor<Background>(GameObjectGroup::UI);
		GameEngineTextureRenderer* Renderer = Title->CreateComponent<GameEngineTextureRenderer>();
		Renderer->GetTransform().SetLocalScale({ 1280,720,100 });
		Renderer->SetTexture("TitleScreenBackground.png");
	}

	{
		Background* Chalice = CreateActor<Background>(GameObjectGroup::UI);
		GameEngineTextureRenderer* Renderer = Chalice->CreateComponent<GameEngineTextureRenderer>();
		Renderer->GetTransform().SetLocalScale({ 300,476,100 });
		Renderer->CreateFrameAnimationFolder("Chalice", FrameAnimation_DESC("Chalice", 0.1f));
		Renderer->ChangeFrameAnimation("Chalice");
		Renderer->GetTransform().SetLocalPosition({ -25,-50,0 });
	}

	{
		Background* Cuphead = CreateActor<Background>(GameObjectGroup::UI);
		GameEngineTextureRenderer* Renderer = Cuphead->CreateComponent<GameEngineTextureRenderer>();
		Renderer->GetTransform().SetLocalScale({ 313,544,100 });
		Renderer->CreateFrameAnimationFolder("Cuphead", FrameAnimation_DESC("Cuphead", 0.1f));
		Renderer->ChangeFrameAnimation("Cuphead");
		Renderer->GetTransform().SetLocalPosition({ -320,-20,0 });
	}

	{
		Background* Mugman = CreateActor<Background>(GameObjectGroup::UI);
		GameEngineTextureRenderer* Renderer = Mugman->CreateComponent<GameEngineTextureRenderer>();
		//Renderer->GetTransform().SetLocalScale({ -315,560,100 });
		//Renderer->CreateFrameAnimationFolder("MugmanB", FrameAnimation_DESC("Mugman", 0.1f));

		Renderer->GetTransform().SetLocalScale({ 315,560,100 });
		Renderer->CreateFrameAnimationFolder("MugmanA", FrameAnimation_DESC("Mugman", 0.1f));
		Renderer->GetTransform().SetLocalPosition({ 305,-24,0 });
		Renderer->ChangeFrameAnimation("MugmanA");

	}

	{

		Background* Bottom = CreateActor<Background>(GameObjectGroup::UI);
		GameEngineTextureRenderer* Renderer = Bottom->CreateComponent<GameEngineTextureRenderer>();
		Renderer->GetTransform().SetLocalScale({ 1328,176,100 });
		Renderer->GetTransform().SetLocalPosition({ 18,-300,0 });
		Renderer->SetTexture("TitleChipsLeft.png");
	}

	{		
		Background* Iris = CreateActor<Background>(GameObjectGroup::UI);
		IrisRenderer = Iris->CreateComponent<GameEngineTextureRenderer>();
		IrisRenderer->GetTransform().SetLocalScale({ 1280,720,100 });
		IrisRenderer->CreateFrameAnimationFolder("IrisBStart", FrameAnimation_DESC("IrisB", 0.1f));
		IrisRenderer->CreateFrameAnimationFolder("IrisB", FrameAnimation_DESC("IrisB",0,0, 0.1f,true));
		IrisRenderer->ChangeFrameAnimation("IrisB");
	}

	{
		Background* Button = CreateActor<Background>(GameObjectGroup::UI);
		GameEngineTextureRenderer* Renderer = Button->CreateComponent<GameEngineTextureRenderer>();
		Renderer->GetTransform().SetLocalScale({363 ,49,100 });
		Renderer->CreateFrameAnimationFolder("Press", FrameAnimation_DESC("PressAnyKey", 0.8f));
		Renderer->ChangeFrameAnimation("Press");
		Renderer->GetTransform().SetLocalPosition({ 0,-293,0 });
	}
}

void ChangeLocalScale(FrameAnimation_DESC _Info)
{
}

void TitleLevel::Update(float _DeltaTime)
{
	if (true == GameEngineInput::GetInst()->IsDown("LevelChange"))
	{
		IrisRenderer->ChangeFrameAnimation("IrisBStart");

		GEngine::ChangeLevel("Select");
	}
}


void TitleLevel::End() 
{
	int a = 0;
}