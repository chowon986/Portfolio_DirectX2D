#include "PreCompile.h"
#include "OldFilm.h"
#include <GameEngineCore/GameEngineBlur.h>
#include "ContentsOldFilm.h"

OldFilm::OldFilm()
{
}

OldFilm::~OldFilm()
{
}

void OldFilm::Start()
{	
	{
		GameEngineTextureRenderer* Test = CreateComponent<GameEngineTextureRenderer>();
		//Test->
		//PostEffectRenderer->GetTransform().SetLocalScale({ 1280, 720, 1.0 });
		////PostEffectRenderer->GetPixelData().PlusColor.a = 1.0;
		//GetLevel()->GetMainCamera()->GetCameraRenderTarget()->AddEffect<GameEngineBlur>();
		////GetLevel()->GetMainCamera()->GetCameraRenderTarget()->AddEffect<ContentsOldFilm>();
		//PostEffectRenderer->GetPipeLine()->SetOutputMergerBlend("OldFilm3");
		////PostEffectRenderer->Option.ColorInversion = 1;
	}

	{
		GameEngineTextureRenderer* PostEffectRenderer = CreateComponent<GameEngineTextureRenderer>();
		PostEffectRenderer->CreateFrameAnimationFolder("03ScreenFX", FrameAnimation_DESC("03ScreenFX", 0.1f));
		PostEffectRenderer->ChangeFrameAnimation("03ScreenFX");
		PostEffectRenderer->GetTransform().SetLocalScale({ 2560, 1440, 1.0 });
		GetLevel()->GetMainCamera()->GetCameraRenderTarget()->AddEffect<GameEngineBlur>();
		PostEffectRenderer->GetPipeLine()->SetOutputMergerBlend("OldFilm2");
		//PostEffectRenderer->Option.ColorInversion = 1;
	}

	//{
	//	GameEngineTextureRenderer* PostEffectRenderer = CreateComponent<GameEngineTextureRenderer>();
	//	PostEffectRenderer->CreateFrameAnimationFolder("03ScreenFX", FrameAnimation_DESC("03ScreenFX", 0.1f));
	//	PostEffectRenderer->ChangeFrameAnimation("03ScreenFX");
	//	PostEffectRenderer->GetTransform().SetLocalScale({ 1280, 720, 1.0 });
	//	//PostEffectRenderer->GetPixelData().PlusColor.a = 1.0;
	//	GetLevel()->GetMainCamera()->GetCameraRenderTarget()->AddEffect<GameEngineBlur>();
	//	//GetLevel()->GetMainCamera()->GetCameraRenderTarget()->AddEffect<ContentsOldFilm>();
	//	PostEffectRenderer->GetPipeLine()->SetOutputMergerBlend("OldFilm3");
	//	PostEffectRenderer->Option.ColorInversion = 1;
	//}

}

void OldFilm::Update(float _DeltaTime)
{
}

void OldFilm::End()
{
}