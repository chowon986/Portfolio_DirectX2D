#include "PreCompile.h"
#include "TutorialLevel.h"
#include "Background.h"
#include "Enums.h"
#include <GameEngineCore/GEngine.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineCore/GameEngineTextureRenderer.h>
#include "InGameCuphead.h"
#include "TutorialBackground.h"

TutorialLevel::TutorialLevel()
	: BackgroundRenderer(nullptr)
	, Cuphead(nullptr)
{
}

TutorialLevel::~TutorialLevel()
{
}

void TutorialLevel::Start()
{
	{
		TutorialBackground* Background = CreateActor<TutorialBackground>(GameObjectGroup::UI);
		Background->GetTransform().SetLocalPosition({ -150, 166 });
	}

	{
		Background* ColMapImage = CreateActor<Background>(GameObjectGroup::UI);
		ColMapRenderer = ColMapImage->CreateComponent<GameEngineTextureRenderer>();
		ColMapRenderer->SetTexture("TestColMap.png");
		ColMapRenderer->ScaleToTexture();
		ColMapRenderer->SetPivot(PIVOTMODE::LEFTTOP);
	}

	{
		Cuphead = CreateActor<InGameCuphead>(GameObjectGroup::Player);
		Cuphead->GetTransform().SetLocalPosition({ 640, -300, -100 });
		Cuphead->SetColMapImage(ColMapRenderer);
	}

}

void TutorialLevel::Update(float _DeltaTime)
{
	if (true == GameEngineInput::GetInst()->IsDown("ColMapOnOffSwitch"))
	{
		ColMapRenderer->OnOffSwitch();
	}

	if (GameEngineInput::GetInst()->IsDown("FreeCameaOnOff"))
	{
		GetMainCameraActor()->FreeCameraModeOnOff();
	}
}


void TutorialLevel::End()
{
	int a = 0;
}