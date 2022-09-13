#include "PreCompile.h"
#include "SaltBakerLevel.h"
#include "Background.h"
#include <GameEngineCore/GameEngineTextureRenderer.h>
#include <GameEngineCore/GEngine.h>
#include <GameEngineCore/GameEngineBlur.h>
#include "SaltBaker.h"
#include "Chicken.h"
#include "Pepper.h"
#include "InGameCuphead.h"
#include "CogWheel.h"
#include "ShellWeDance.h"
#include "SaltBakerHeart.h"

SaltBakerLevel::SaltBakerLevel()
{
}

SaltBakerLevel::~SaltBakerLevel()
{
}

void SaltBakerLevel::Start()
{
	GetMainCamera()->GetCameraRenderTarget()->AddEffect<GameEngineBlur>();
	{
		Background* ColMapImage = CreateActor<Background>(GameObjectGroup::UI);
		ColMapRenderer = ColMapImage->CreateComponent<GameEngineTextureRenderer>();
		ColMapRenderer->SetTexture("TestColMap.png");
		ColMapRenderer->ScaleToTexture();
		ColMapRenderer->GetTransform().SetWorldScale({ 1280.0f,720.0f,1.0f });
		ColMapRenderer->GetTransform().SetLocalPosition({640.0f, -360.0f, (int)ZOrder::Background + 1 });
		SetMainColMapImage(ColMapRenderer);
	}
	//InGameCuphead* Cuphead = CreateActor<InGameCuphead>();
	//Cuphead->GetTransform().SetWorldPosition({ 640.0f,-360.0f });

	//SaltBaker* Boss = CreateActor<SaltBaker>();
	//Boss->GetTransform().SetWorldPosition({ 640.0f,-360.0f });

	//Pepper* Ph2Monster1 = CreateActor<Pepper>();
	//Ph2Monster1->GetTransform().SetWorldPosition({ 100.0f,100.0f,(int)ZOrder::NPC });
	//Ph2Monster1->SetPlayer(Cuphead);
	//Ph2Monster1->SetMonster(Boss);

	//CogWheel* Ph3Monster1 = CreateActor<CogWheel>();
	//Ph3Monster1->GetTransform().SetWorldPosition({ 640.0f,-600.0f });

	//ShellWeDance* Ph3Monster2 = CreateActor<ShellWeDance>();
	//Ph3Monster2->GetTransform().SetWorldPosition({ 640.0f,-600.0f });

	SaltBakerHeart* Ph4Boss = CreateActor<SaltBakerHeart>();
	Ph4Boss->GetTransform().SetWorldPosition({ 640.0f,-400.0f });


	//Chicken* ComMonster = CreateActor<Chicken>();
	//Monster->GetTransform().SetWorldPosition({ 640.0f, -360.0f });

	GetMainCamera()->SetProjectionSize({ 1280.0f, 720.0f });
	GetRotateCamera()->SetProjectionSize({ 1536.0f, 864.0f });
	GetIrisCamera()->SetProjectionSize({ 1280.0f, 720.0f });

	GetMainCameraActorTransform().SetLocalPosition({ 640, -360 });
	GetRotateCameraActorTransform().SetLocalPosition({ 640, -360 });
	GetIrisCameraActorTransform().SetLocalPosition({ 640.0f, -360.0f });
}

void SaltBakerLevel::Update(float _DeltaTime)
{
	if (true == GameEngineInput::GetInst()->IsDown("LevelChange"))
	{
		GEngine::ChangeLevel("WorldMap");
	}
}

void SaltBakerLevel::End()
{
}

void SaltBakerLevel::EndAnimation(const FrameAnimation_DESC& _Info)
{
	GEngine::ChangeLevel("WorldMap");
}
