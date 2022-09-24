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
#include "Tornado.h"

SaltBakerLevel::SaltBakerLevel()
	:BeforePhase(Phase::Ready)
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
	{
		Background* Kitchen = CreateActor<Background>(GameObjectGroup::UI);
		KitchenRenderer = Kitchen->CreateComponent<GameEngineTextureRenderer>();
		KitchenRenderer->CreateFrameAnimationFolder("Kitchen", FrameAnimation_DESC("Kitchen", 0.1f, true));
		KitchenRenderer->ChangeFrameAnimation("Kitchen");
		KitchenRenderer->SetScaleModeImage();
		KitchenRenderer->GetTransform().SetLocalPosition({ 640.0f, -360.0f, (int)ZOrder::Background });
	}

	//SaltBaker* Boss = CreateActor<SaltBaker>();
	//Boss->GetTransform().SetWorldPosition({ 640.0f,-360.0f });
	//Boss->SetBackgroundRenderer(KitchenRenderer);

	//InGameCuphead* Cuphead = CreateActor<InGameCuphead>();
	//Cuphead->GetTransform().SetWorldPosition({ 640.0f,-360.0f });


	//Chicken* ComMonster = CreateActor<Chicken>();
	//Monster->GetTransform().SetWorldPosition({ 640.0f, -360.0f });

	GetMainCamera()->SetProjectionSize({ 1280.0f, 720.0f });
	GetRotateCamera()->SetProjectionSize({ 1536.0f, 864.0f });
	GetIrisCamera()->SetProjectionSize({ 1280.0f, 720.0f });

	GetMainCameraActorTransform().SetLocalPosition({ 640, -360 });
	GetRotateCameraActorTransform().SetLocalPosition({ 640, -360 });
	GetIrisCameraActorTransform().SetLocalPosition({ 640.0f, -360.0f });

	SetPhase(Phase::Phase1);
}

void SaltBakerLevel::Update(float _DeltaTime)
{
	if (true == GameEngineInput::GetInst()->IsDown("LevelChange"))
	{
		GEngine::ChangeLevel("WorldMap");
	}

	if (CurrentPhase != BeforePhase)
	{
		BeforePhase = CurrentPhase;

		if (CurrentPhase == Phase::Phase1)
		{
			SaltBaker* Ph1Boss = CreateActor<SaltBaker>();
			Ph1Boss->GetTransform().SetWorldPosition({ 640.0f,-360.0f });

			Chicken* Ph1Monster = CreateActor<Chicken>();
			Ph1Monster->GetTransform().SetWorldPosition({ 640.0f, -360.0f });
		}

		else if (CurrentPhase == Phase::Phase3)
		{
			ColMapRenderer->SetTexture("SBPh3ColMap.png");
			CogWheel* Ph3Monster1 = CreateActor<CogWheel>();
			Ph3Monster1->GetTransform().SetWorldPosition({ 300.0f,-650.0f });
		}

		else if (CurrentPhase == Phase::Phase4)
		{
			//ColMapRenderer->SetTexture(".png");
			{
				Tornado* Ph4Tornado = CreateActor<Tornado>();
				Ph4Tornado->GetTransform().SetWorldPosition({ 200.0f, 720.0f });
				Ph4Tornado->GetCollision()->ChangeOrder(ObjectOrder::TRACKING1);

			}

			{
				Tornado* Ph4Tornado = CreateActor<Tornado>();
				Ph4Tornado->GetTransform().SetWorldPosition({ 1080.0f, 720.0f });
				Ph4Tornado->GetCollision()->ChangeOrder(ObjectOrder::TRACKING2);
			}
		}
	}
}

void SaltBakerLevel::End()
{
}

void SaltBakerLevel::EndAnimation(const FrameAnimation_DESC& _Info)
{
	GEngine::ChangeLevel("WorldMap");
}
