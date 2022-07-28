#include "PreCompile.h"
#include "TutorialLevel.h"
#include "Background.h"
#include "Enums.h"
#include <GameEngineCore/GEngine.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineCore/GameEngineTextureRenderer.h>
#include "InGameCuphead.h"

TutorialLevel::TutorialLevel()
{
}

TutorialLevel::~TutorialLevel()
{
}

void TutorialLevel::Start()
{
	//{
	//	Background* TutorialBackground = CreateActor<Background>(GameObjectGroup::UI);
	//	GameEngineTextureRenderer* Renderer = TutorialBackground->CreateComponent<GameEngineTextureRenderer>();
	//	Renderer->CreateFrameAnimationFolder("TutorialBackgroundStart", FrameAnimation_DESC("TutorialBackgroundStart", 0.1f, false));
	//	Renderer->ChangeFrameAnimation("TutorialBackgroundStart");
	//}

	{
		InGameCuphead* Cuphead = CreateActor<InGameCuphead>(GameObjectGroup::Player);
	}
}

void TutorialLevel::Update(float _DeltaTime)
{

}


void TutorialLevel::End()
{
	int a = 0;
}