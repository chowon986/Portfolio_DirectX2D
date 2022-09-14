#include "PreCompile.h"
#include "ScoreLevel.h"
#include "CharacterState.h"
#include <GameEngineCore/GameEngineBlur.h>
#include <GameEngineCore/GameEngineFontRenderer.h>

ScoreLevel::ScoreLevel()
	: BackgroundRenderer(nullptr)
	, IrisRenderer(nullptr)
	, State(nullptr)
{
}

ScoreLevel::~ScoreLevel()
{
}

void ScoreLevel::LevelStartEvent()
{
	std::list<GameEngineActor*> Actors = GetGroup(GameObjectGroup::CharacterState);
	for (GameEngineActor* Actor : Actors)
	{
		if (CharacterState* _State = dynamic_cast<CharacterState*>(Actor))
		{
			State = _State;
		}
	}

}

void ScoreLevel::Start()
{
	GetMainCamera()->GetCameraRenderTarget()->AddEffect<GameEngineBlur>();
	{
		GameEngineActor* Iris = CreateActor<GameEngineActor>();
		IrisRenderer = Iris->CreateComponent<GameEngineTextureRenderer>();
		IrisRenderer->CreateFrameAnimationFolder("LightOn", FrameAnimation_DESC("IrisA", 0,0,0.05f, true));
		IrisRenderer->ChangeFrameAnimation("LightOn");
		IrisRenderer->GetTransform().SetLocalScale(float4{ 1280.0f,720.0f,1.0f });
		IrisRenderer->GetTransform().SetLocalPosition(float4{ 640.0f,-360.0f,(int)ZOrder::UI });
	}
	{
		GameEngineActor* Background = CreateActor<GameEngineActor>();
		BackgroundRenderer = Background->CreateComponent<GameEngineTextureRenderer>();
		BackgroundRenderer->SetTexture("WinScreen.png");
		BackgroundRenderer->ScaleToTexture();
		BackgroundRenderer->GetTransform().SetLocalPosition(float4{ 640.0f,-360.0f,(int)ZOrder::Background });
	}
	{
		GameEngineActor* ResultTitle = CreateActor<GameEngineActor>();
		GameEngineTextureRenderer* TitleRenderer = ResultTitle->CreateComponent<GameEngineTextureRenderer>();
		TitleRenderer->CreateFrameAnimationFolder("ResultTitle", FrameAnimation_DESC("ResultTitle", 0.05f, true));
		TitleRenderer->ChangeFrameAnimation("ResultTitle");
		TitleRenderer->SetScaleModeImage();
		TitleRenderer->GetTransform().SetLocalPosition(float4{ 640.0f, -100.0f,(int)ZOrder::Foreground });
	}
	{
		GameEngineActor* Board = CreateActor<GameEngineActor>();
		GameEngineTextureRenderer* BoardRenderer = Board->CreateComponent<GameEngineTextureRenderer>();
		BoardRenderer->CreateFrameAnimationFolder("Board", FrameAnimation_DESC("Board", 0.05f, false));
		BoardRenderer->ChangeFrameAnimation("Board");
		BoardRenderer->SetScaleModeImage();
		BoardRenderer->GetTransform().SetLocalPosition(float4{ 750.0f, -425.0f,(int)ZOrder::Foreground });
	}

	{
		GameEngineActor* Font = CreateActor<GameEngineActor>();
		GameEngineFontRenderer* FontRenderer = Font->CreateComponent<GameEngineFontRenderer>();
		FontRenderer->ChangeCamera(CAMERAORDER::UICAMERA);
		FontRenderer->SetText("시간 ", "Yoon-Backjae");
		FontRenderer->SetColor({ 1.0f, 1.0f, 1.0f, 1.0 });
		FontRenderer->SetSize(35);
		FontRenderer->SetScreenPostion(float4{ 550.0f, 250.0f,(int)ZOrder::Foreground - 1 });
		FontRenderer->SetRenderingOrder(10000);
	}

	{
		GameEngineActor* Font = CreateActor<GameEngineActor>();
		GameEngineFontRenderer* FontRenderer = Font->CreateComponent<GameEngineFontRenderer>();
		FontRenderer->ChangeCamera(CAMERAORDER::UICAMERA);
		FontRenderer->SetText("HP보너스 ", "Yoon-Backjae");
		FontRenderer->SetColor({ 1.0f, 1.0f, 1.0f, 1.0 });
		FontRenderer->SetSize(35);
		FontRenderer->SetScreenPostion(float4{ 550.0f, 300.0f,(int)ZOrder::Foreground - 1});
		FontRenderer->SetRenderingOrder(10000);
	}
	{
		GameEngineActor* Font = CreateActor<GameEngineActor>();
		GameEngineFontRenderer* FontRenderer = Font->CreateComponent<GameEngineFontRenderer>();
		FontRenderer->ChangeCamera(CAMERAORDER::UICAMERA);
		FontRenderer->SetText("회피 ", "Yoon-Backjae");
		FontRenderer->SetColor({ 1.0f, 1.0f, 1.0f, 1.0 });
		FontRenderer->SetSize(35);
		FontRenderer->SetScreenPostion(float4{ 550.0f, 350.0f,(int)ZOrder::Foreground - 1 });
		FontRenderer->SetRenderingOrder(10000);
	}
	{
		GameEngineActor* Font = CreateActor<GameEngineActor>();
		GameEngineFontRenderer* FontRenderer = Font->CreateComponent<GameEngineFontRenderer>();
		FontRenderer->ChangeCamera(CAMERAORDER::UICAMERA);
		FontRenderer->SetText("슈퍼 미터 ", "Yoon-Backjae");
		FontRenderer->SetColor({ 1.0f, 1.0f, 1.0f, 1.0 });
		FontRenderer->SetSize(35);
		FontRenderer->SetScreenPostion(float4{ 550.0f, 400.0f,(int)ZOrder::Foreground - 1 });
		FontRenderer->SetRenderingOrder(10000);
	}
	{
		GameEngineActor* Font = CreateActor<GameEngineActor>();
		GameEngineFontRenderer* FontRenderer = Font->CreateComponent<GameEngineFontRenderer>();
		FontRenderer->ChangeCamera(CAMERAORDER::UICAMERA);
		FontRenderer->SetText("스킬 레벨 ", "Yoon-Backjae");
		FontRenderer->SetColor({ 1.0f, 1.0f, 1.0f, 1.0 });
		FontRenderer->SetSize(35);
		FontRenderer->SetScreenPostion(float4{ 550.0f, 350.0f,(int)ZOrder::Foreground - 1 });
		FontRenderer->SetRenderingOrder(10000);
	}
	{
		GameEngineActor* Font = CreateActor<GameEngineActor>();
		GameEngineFontRenderer* FontRenderer = Font->CreateComponent<GameEngineFontRenderer>();
		FontRenderer->ChangeCamera(CAMERAORDER::UICAMERA);
		FontRenderer->SetText("득점 ", "Yoon-Backjae");
		FontRenderer->SetColor({ 1.0f, 1.0f, 1.0f, 1.0 });
		FontRenderer->SetSize(50);
		FontRenderer->SetScreenPostion(float4{ 600.0f, 600.0f,(int)ZOrder::Foreground - 1 });
		FontRenderer->SetRenderingOrder(10000);
	}

	if (State == nullptr)
	{
		GameEngineActor* Player = CreateActor<GameEngineActor>();
		GameEngineTextureRenderer* PlayerRenderer = Player->CreateComponent<GameEngineTextureRenderer>();
		PlayerRenderer->CreateFrameAnimationFolder("WinCuphead", FrameAnimation_DESC("WinCuphead", 0.05f, true));
		PlayerRenderer->ChangeFrameAnimation("WinCuphead");
		PlayerRenderer->SetScaleModeImage();
		PlayerRenderer->GetTransform().SetLocalPosition(float4{ 320, -400.0f,(int)ZOrder::Foreground });

		GameEngineActor* PlayerName = CreateActor<GameEngineActor>();
		GameEngineTextureRenderer* PlayerNameRenderer = PlayerName->CreateComponent<GameEngineTextureRenderer>();
		PlayerNameRenderer->CreateFrameAnimationFolder("CupheadName", FrameAnimation_DESC("CupheadName", 0.1f, false));
		PlayerNameRenderer->ChangeFrameAnimation("CupheadName");
		PlayerNameRenderer->SetScaleModeImage();
		PlayerNameRenderer->GetTransform().SetLocalPosition(float4{ 320.0, -660.0f,(int)ZOrder::Foreground - 1 });
	}
	else
	{
		if (State->Type == CharacterType::Cuphead)
		{
			GameEngineActor* Player = CreateActor<GameEngineActor>();
			GameEngineTextureRenderer* PlayerRenderer = Player->CreateComponent<GameEngineTextureRenderer>();
			PlayerRenderer->CreateFrameAnimationFolder("WinCuphead", FrameAnimation_DESC("WinCuphead", 0.05f, true));
			PlayerRenderer->ChangeFrameAnimation("WinCuphead");
			PlayerRenderer->SetScaleModeImage();
			PlayerRenderer->GetTransform().SetLocalPosition(float4{ 320, -400.0f,(int)ZOrder::Foreground });

			GameEngineActor* PlayerName = CreateActor<GameEngineActor>();
			GameEngineTextureRenderer* PlayerNameRenderer = PlayerName->CreateComponent<GameEngineTextureRenderer>();
			PlayerNameRenderer->CreateFrameAnimationFolder("CupheadName", FrameAnimation_DESC("CupheadName",0.1f,false));
			PlayerNameRenderer->ChangeFrameAnimation("CupheadName");
			PlayerNameRenderer->SetScaleModeImage();
			PlayerNameRenderer->GetTransform().SetLocalPosition(float4{ 320.0, -660.0f,(int)ZOrder::Foreground - 1 });
		}
		else if (State->Type == CharacterType::Chalice)
		{
			GameEngineActor* Player = CreateActor<GameEngineActor>();
			GameEngineTextureRenderer* PlayerRenderer = Player->CreateComponent<GameEngineTextureRenderer>();
			PlayerRenderer->CreateFrameAnimationFolder("WinCuphead", FrameAnimation_DESC("WinCuphead", 0.05f, true)); // Need to chk : 챌리스 이미지 적용하기
			PlayerRenderer->ChangeFrameAnimation("WinCuphead"); // Need to chk : 상동
			PlayerRenderer->SetScaleModeImage();
			PlayerRenderer->GetTransform().SetLocalPosition(float4{ 320, -400.0f,(int)ZOrder::Foreground });

			GameEngineActor* PlayerName = CreateActor<GameEngineActor>();
			GameEngineTextureRenderer* PlayerNameRenderer = PlayerName->CreateComponent<GameEngineTextureRenderer>();
			PlayerNameRenderer->CreateFrameAnimationFolder("CupheadName", FrameAnimation_DESC("CupheadName", 0.1f, false)); // Need to chk : 상동
			PlayerNameRenderer->ChangeFrameAnimation("CupheadName");
			PlayerNameRenderer->SetScaleModeImage();
			PlayerNameRenderer->GetTransform().SetLocalPosition(float4{ 320.0, -660.0f,(int)ZOrder::Foreground - 1 });
		}
	}

	GetMainCameraActorTransform().SetLocalPosition({ 640, -360 });

}

void ScoreLevel::Update(float _DeltaTime)
{
	if (IrisRenderer->GetPixelData().PlusColor.a > -1.0f)
	{
		IrisRenderer->GetPixelData().PlusColor.a -= _DeltaTime * 0.3;
	}
	BackgroundRenderer->GetTransform().SetLocalRotate({0.0f, 0.0f, 10 * _DeltaTime});
}

void ScoreLevel::End()
{
}
