#include "PreCompile.h"
#include "OldFilm.h"

OldFilm::OldFilm()
{
}

OldFilm::~OldFilm()
{
}

void OldFilm::Start()
{	
	
	{
		GameEngineTextureRenderer* PostEffectRenderer = CreateComponent<GameEngineTextureRenderer>();
		PostEffectRenderer->CreateFrameAnimationFolder("03ScreenFX", FrameAnimation_DESC("03ScreenFX", 0.1f));
		PostEffectRenderer->ChangeFrameAnimation("03ScreenFX");
		PostEffectRenderer->GetTransform().SetLocalScale({ 1280, 720, 1.0 });
		PostEffectRenderer->Option.ColorInversion = 1;
		PostEffectRenderer->GetPipeLine()->SetOutputMergerBlend("OldFilm");
		//PostEffectRenderer->GetColorData().PlusColor.a = -0.9;
	}

	//{
	//	GameEngineTextureRenderer* PostEffectRenderer = CreateComponent<GameEngineTextureRenderer>();
	//	PostEffectRenderer->CreateFrameAnimationFolder("03ScreenFX", FrameAnimation_DESC("03ScreenFX", 0.2f));
	//	PostEffectRenderer->ChangeFrameAnimation("03ScreenFX");
	//	PostEffectRenderer->GetTransform().SetLocalScale({ 1920, 1080, 1.0f });
	//}

}

void OldFilm::Update(float _DeltaTime)
{
}

void OldFilm::End()
{
}