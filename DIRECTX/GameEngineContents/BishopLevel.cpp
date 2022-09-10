#include "PreCompile.h"
#include "BishopLevel.h"
#include <GameEngineCore/GameEngineTextureRenderer.h>
#include "Background.h"
#include "InGameCuphead.h"
#include "Pawn.h"
#include <GameEngineCore/GEngine.h>
#include <GameEngineContents/Enums.h>
#include <functional>
#include <GameEngineCore/GameEngineBlur.h>

BishopLevel::BishopLevel()
	: BackgroundRenderer(nullptr)
	, ColMapRenderer(nullptr)
	, BossPawnActors(8)
{
}

BishopLevel::~BishopLevel()
{
}

void BishopLevel::Start()
{
	GetMainCamera()->GetCameraRenderTarget()->AddEffect<GameEngineBlur>();

	{
		Background* BishopBackground = CreateActor<Background>(GameObjectGroup::UI);
		BackgroundRenderer = BishopBackground->CreateComponent<GameEngineTextureRenderer>();
		BackgroundRenderer->SetTexture("bg_main.png");
		BackgroundRenderer->GetTransform().SetLocalPosition({ 640.0f, -360.0f, (int)ZOrder::Background });
		BackgroundRenderer->ScaleToTexture();
	}

	{
		//Background* BishopBackgroundTopper = CreateActor<Background>(GameObjectGroup::UI);
		//GameEngineTextureRenderer* Renderer = BishopBackgroundTopper->CreateComponent<GameEngineTextureRenderer>();
		//Renderer->SetTexture("bg_main_topper.png");
		//Renderer->ScaleToTexture();
		//Renderer->GetTransform().SetLocalPosition({ 500,-180,-100 });
	}

	{
		Background* ColMapImage = CreateActor<Background>(GameObjectGroup::UI);
		ColMapRenderer = ColMapImage->CreateComponent<GameEngineTextureRenderer>();
		ColMapRenderer->SetTexture("BishopColMap.png");
		ColMapRenderer->ScaleToTexture();
		ColMapRenderer->GetTransform().SetLocalPosition({ 640.0f, -360.0f, (int)ZOrder::Background + 1 });
	}

	{
		Background* ColMapImage = CreateActor<Background>(GameObjectGroup::UI);
		GameEngineTextureRenderer* PawnColMapRenderer = ColMapImage->CreateComponent<GameEngineTextureRenderer>();
		PawnColMapRenderer->SetTexture("PawnColMap.png");
		PawnColMapRenderer->ScaleToTexture();
		PawnColMapRenderer->GetTransform().SetLocalPosition({ 640.0f, -360.0f, (int)ZOrder::Background + 1 });
		SetMainColMapImage(PawnColMapRenderer);
	}
	{
		InGameCuphead* Cuphead = CreateActor<InGameCuphead>(GameObjectGroup::Player);
		Cuphead->GetTransform().SetLocalPosition({ 640.0f, -360.0f, (int)ZOrder::Player });
		Cuphead->SetColMapImage(ColMapRenderer);
		PushToRotateCamera(Cuphead);
	}

	{
		PawnPosX = { 150.0f, 290.0f, 430.0f, 570.0f, 710.0f, 850.0f, 990.0f, 1130.0f };

		for (int i = 0; i < 8; i++)
		{
			Pawn* BossPawn = CreateActor<Pawn>(GameObjectGroup::Monster);
			BossPawn->SetPlayer(Cuphead);
			BossPawn->GetTransform().SetLocalPosition({ PawnPosX[i], 0.0f, (int)ZOrder::Player - 1 });
			if (i % 2 == 0)
			{
				BossPawn->SetIntroName("AStart");
			}
			else if (i % 2 == 1)
			{
				BossPawn->SetIntroName("BStart");
			}
			PushToRotateCamera(BossPawn);
			BossPawnActors.push_back(BossPawn);
		}
	}

	GetMainCamera()->SetProjectionSize({ 1280.0f, 720.0f });
	GetRotateCamera()->SetProjectionSize({ 1536.0f, 864.0f });
	GetIrisCamera()->SetProjectionSize({ 1280.0f, 720.0f });

	GetMainCameraActorTransform().SetLocalPosition({ 640, -360 });
	GetRotateCameraActorTransform().SetLocalPosition({ 640, -360 });
	GetIrisCameraActorTransform().SetLocalPosition({ 640.0f, -360.0f });
}

void BishopLevel::Update(float _DeltaTime)
{
	ColMapOnOffSwitch();

	if (true == GameEngineInput::GetInst()->IsDown("LevelChange"))
	{
		GEngine::ChangeLevel("WorldMap");
	}
}

void BishopLevel::ColMapOnOffSwitch()
{
	if (true == GameEngineInput::GetInst()->IsDown("ColMapOnOffSwitch"))
	{
		BackgroundRenderer->OnOffSwitch();
	}
}

void BishopLevel::End()
{
}
