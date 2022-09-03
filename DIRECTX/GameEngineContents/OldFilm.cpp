#include "PreCompile.h"
#include "OldFilm.h"
#include <GameEngineCore/GameEngineBlur.h>

OldFilm::OldFilm()
{
}

OldFilm::~OldFilm()
{
}

void OldFilm::Test(const FrameAnimation_DESC& _Info)
{
	int a = 0;
}

void OldFilm::Start()
{	
	{
		GameEngineTextureRenderer* PostEffectRenderer = CreateComponent<GameEngineTextureRenderer>();
		PostEffectRenderer->CreateFrameAnimationFolder("03ScreenFX", FrameAnimation_DESC("03ScreenFX", 0.08f));
		PostEffectRenderer->ChangeFrameAnimation("03ScreenFX");
		//PostEffectRenderer->GetTransform().SetLocalScale({ 1280, 720, 1.0 });
		PostEffectRenderer->GetTransform().SetLocalScale({ 1920, 1080, 1.0 });
		GetLevel()->PushRendererToUICamera(PostEffectRenderer);
	}

	{
		GameEngineTextureRenderer* PostEffectRenderer = CreateComponent<GameEngineTextureRenderer>();
		PostEffectRenderer->CreateFrameAnimationFolder("04RevScreenFX", FrameAnimation_DESC("04RevScreenFX", 0.08f));
		PostEffectRenderer->ChangeFrameAnimation("04RevScreenFX");
		//PostEffectRenderer->GetTransform().SetLocalScale({ 1280, 720, 1.0 });
		PostEffectRenderer->GetTransform().SetLocalScale({ 1920, 1080, 1.0 });
		GetLevel()->PushRendererToUICamera(PostEffectRenderer);
		PostEffectRenderer->GetPipeLine()->SetOutputMergerBlend("OldFilm");
		PostEffectRenderer->Option.ColorInversion = 1;
		PostEffectRenderer->AnimationBindFrame("04RevScreenFX", std::bind(&OldFilm::Test, this, std::placeholders::_1));
		//GetLevel()->GetUICamera()->GetCameraRenderTarget()->AddEffect<ContentsOldFilm>();
	}
}

void OldFilm::Update(float _DeltaTime)
{
}

void OldFilm::End()
{
}