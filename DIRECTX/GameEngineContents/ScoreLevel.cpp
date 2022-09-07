#include "PreCompile.h"
#include "ScoreLevel.h"
#include "CharacterState.h"
#include <GameEngineCore/GameEngineBlur.h>

ScoreLevel::ScoreLevel()
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
	GetMainCameraActorTransform().SetLocalPosition({ 640, -360 });

	{
		GameEngineActor* Background = CreateActor<GameEngineActor>();
		BackgroundRenderer = Background->CreateComponent<GameEngineTextureRenderer>();
		BackgroundRenderer->SetTexture("WinScreen.png");
		BackgroundRenderer->ScaleToTexture();
		BackgroundRenderer->GetTransform().SetLocalPosition(float4{ 640.0f,-360.0f,(int)ZOrder::Background });
	}

	if (State == nullptr)
	{
		GameEngineActor* Player = CreateActor<GameEngineActor>();
		GameEngineTextureRenderer* PlayerRenderer = Player->CreateComponent<GameEngineTextureRenderer>();
		PlayerRenderer->CreateFrameAnimationFolder("WinCuphead", FrameAnimation_DESC("WinCuphead", 0.05f, true));
		PlayerRenderer->ChangeFrameAnimation("WinCuphead");
		PlayerRenderer->SetScaleModeImage();
		PlayerRenderer->GetTransform().SetLocalPosition(float4{ 500.0f,-360.0f,(int)ZOrder::Foreground });
		PlayerRenderer->ChangeCamera(CAMERAORDER::BACKGROUND);
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
			PlayerRenderer->GetTransform().SetLocalPosition(float4{ -320,-0.0f,(int)ZOrder::Foreground });
			PlayerRenderer->ChangeCamera(CAMERAORDER::BACKGROUND);
		}
		else if (State->Type == CharacterType::Chalice)
		{
			GameEngineActor* Player = CreateActor<GameEngineActor>();
			GameEngineTextureRenderer* PlayerRenderer = Player->CreateComponent<GameEngineTextureRenderer>();
			PlayerRenderer->CreateFrameAnimationFolder("WinCuphead", FrameAnimation_DESC("WinCuphead", 0.05f, true)); // Need to chk
			PlayerRenderer->ChangeFrameAnimation("WinCuphead"); // Need to chk
			PlayerRenderer->SetScaleModeImage();
			PlayerRenderer->GetTransform().SetLocalPosition(float4{ -320,0.0f,(int)ZOrder::Foreground });
			PlayerRenderer->ChangeCamera(CAMERAORDER::BACKGROUND);
		}
	}

}

void ScoreLevel::Update(float _DeltaTime)
{
	BackgroundRenderer->GetTransform().SetLocalRotate({0.0f, 0.0f, 10 * _DeltaTime});

}

void ScoreLevel::End()
{
}
