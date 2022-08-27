#include "PreCompile.h"
#include "Background.h"
#include "TutorialLevel.h"
#include "WorldMapCuphead.h"
#include "InGameCuphead.h"
#include "TutorialBackground.h"

TutorialLevel::TutorialLevel()
	: BackgroundRenderer(nullptr)
	, ColMapRenderer(nullptr)
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

	//{
	//	WorldMapCuphead* Cuphead = CreateActor<WorldMapCuphead>(GameObjectGroup::Player);
	//	Cuphead->GetTransform().SetLocalPosition({ 100, 300, -100 });
	//	Cuphead->SetColMapImage(ColMapRenderer);
	//}

	{
		InGameCuphead* Cuphead = CreateActor<InGameCuphead>(GameObjectGroup::Player);
		Cuphead->GetTransform().SetLocalPosition({ 100, 300, -100 });
		Cuphead->SetColMapImage(ColMapRenderer);
	}
}

void TutorialLevel::Update(float _DeltaTime)
{
	if (true == GameEngineInput::GetInst()->IsDown("ColMapOnOffSwitch"))
	{
		ColMapRenderer->OnOffSwitch();
	}
}


void TutorialLevel::End()
{
}