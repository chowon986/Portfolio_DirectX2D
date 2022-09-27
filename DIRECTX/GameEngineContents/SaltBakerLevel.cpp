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
#include "CharacterState.h"
#include "Tornado.h"
#include "BreakObject.h"

SaltBakerLevel::SaltBakerLevel()
	:BeforePhase(Phase::Ready)
	, OnceCheck(false)
	, AlphaSettingOn(false)
	, BackgroundMoveOn(false)
	, BackgroundMoveFinished(false)
	, Phase2BreakOn(false)
{
}

SaltBakerLevel::~SaltBakerLevel()
{ 
}

void SaltBakerLevel::LevelStartEvent()
{
	std::list<GameEngineActor*> Actors = GetGroup(GameObjectGroup::CharacterState);
	for (GameEngineActor* Actor : Actors)
	{
		if (CharacterState* _State = dynamic_cast<CharacterState*>(Actor))
		{
			State = _State;
			HPCount = State->MaxHP;
		}
	}
}

void SaltBakerLevel::Start()
{
	GetMainCamera()->GetCameraRenderTarget()->AddEffect<GameEngineBlur>();
	{
		Background* ColMapImage = CreateActor<Background>(GameObjectGroup::UI);
		ColMapRenderer = ColMapImage->CreateComponent<GameEngineTextureRenderer>();
		ColMapRenderer->SetTexture("TestColMap.png");
		ColMapRenderer->ScaleToTexture();
		ColMapRenderer->GetTransform().SetWorldScale({ 1280.0f, 720.0f, 1.0f });
		ColMapRenderer->GetTransform().SetWorldPosition({640.0f, -360.0f, (int)ZOrder::Background + 1 });
		SetMainColMapImage(ColMapRenderer);
	}
	{
		Background* Kitchen = CreateActor<Background>(GameObjectGroup::UI);
		KitchenRenderer = Kitchen->CreateComponent<GameEngineTextureRenderer>();
		KitchenRenderer->SetTexture("MoveKitchen.png");
		KitchenRenderer->ScaleToTexture();
		KitchenRenderer->GetTransform().SetLocalPosition({ 640.0f, 843.0f, (int)ZOrder::Background });
	}
	
	{
		Background* Kitchen = CreateActor<Background>(GameObjectGroup::UI);
		KitchenRendererTopper = Kitchen->CreateComponent<GameEngineTextureRenderer>();
		KitchenRendererTopper->CreateFrameAnimationFolder("Kitchen", FrameAnimation_DESC("Kitchen", 0.1f, true));
		KitchenRendererTopper->ChangeFrameAnimation("Kitchen");
		KitchenRendererTopper->SetScaleModeImage();
		KitchenRendererTopper->ScaleToTexture();
		KitchenRendererTopper->GetTransform().SetLocalPosition({ 640.0f, -360.0f, (int)ZOrder::Background - 1});
	}

	//{
	//	Background* Ph3Sky = CreateActor<Background>(GameObjectGroup::UI);
	//	GameEngineTextureRenderer* Ph3SkyRenderer = Ph3Sky->CreateComponent<GameEngineTextureRenderer>();
	//	Ph3SkyRenderer->CreateFrameAnimationFolder("Kitchen", FrameAnimation_DESC("Kitchen", 0.1f, true));
	//	Ph3SkyRenderer->SetTexture("MoveKitchen.png");
	//	Ph3SkyRenderer->ChangeFrameAnimation("Kitchen");
	//	Ph3SkyRenderer->SetScaleModeImage();
	//	Ph3SkyRenderer->GetTransform().SetLocalPosition({ 640.0f, -360.0f, (int)ZOrder::Background });
	//}

	//{
	//	Background* Ph3Background = CreateActor<Background>(GameObjectGroup::UI);
	//	GameEngineTextureRenderer* Ph3BackgroundRenderer = Ph3Background->CreateComponent<GameEngineTextureRenderer>();
	//	Ph3BackgroundRenderer->SetTexture("Ph3Background1.png");
	//	Ph3BackgroundRenderer->ScaleToTexture();
	//	Ph3BackgroundRenderer->GetTransform().SetLocalPosition({ 675.0f, -260.0f, (int)ZOrder::Background });
	//}

	//{
	//	Background* Ph3Background = CreateActor<Background>(GameObjectGroup::UI);
	//	GameEngineTextureRenderer* Ph3BackgroundRenderer = Ph3Background->CreateComponent<GameEngineTextureRenderer>();
	//	Ph3BackgroundRenderer->SetTexture("Ph3Background2.png");
	//	Ph3BackgroundRenderer->ScaleToTexture();
	//	Ph3BackgroundRenderer->GetTransform().SetLocalPosition({ 630.0f, -320.0f, (int)ZOrder::Background - 1});
	//}

	//{
	//	Background* Ph3Background = CreateActor<Background>(GameObjectGroup::UI);
	//	GameEngineTextureRenderer* Ph3BackgroundRenderer = Ph3Background->CreateComponent<GameEngineTextureRenderer>();
	//	Ph3BackgroundRenderer->SetTexture("Ph3Background3.png");
	//	Ph3BackgroundRenderer->ScaleToTexture();
	//	Ph3BackgroundRenderer->GetTransform().SetLocalPosition({ 655.0f, -610.0f, (int)ZOrder::Background - 2 });
	//}

	//{
	//	Background* Ph3Background = CreateActor<Background>(GameObjectGroup::UI);
	//	GameEngineTextureRenderer* Ph3BackgroundRenderer = Ph3Background->CreateComponent<GameEngineTextureRenderer>();
	//	Ph3BackgroundRenderer->SetTexture("Ph3Background4.png");
	//	Ph3BackgroundRenderer->ScaleToTexture();
	//	Ph3BackgroundRenderer->GetTransform().SetLocalPosition({ 450.0f, -220.0f, (int)ZOrder::Background - 0.5});
	//}

	//{
	//	Background* Ph3Background = CreateActor<Background>(GameObjectGroup::UI);
	//	GameEngineTextureRenderer* Ph3BackgroundRenderer = Ph3Background->CreateComponent<GameEngineTextureRenderer>();
	//	Ph3BackgroundRenderer->SetTexture("Ph3Background5.png");
	//	Ph3BackgroundRenderer->ScaleToTexture();
	//	Ph3BackgroundRenderer->GetTransform().SetLocalPosition({ 610.0f, -400.0f, (int)ZOrder::Background - 3 });
	//}

	// Ph2Break
	{
		BreakObject* Object = CreateActor<BreakObject>(GameObjectGroup::UI);
		Object->SetStartPos({ 1100.0f, 50.0f, (int)ZOrder::UI });
		Object-> GetTransform().SetWorldPosition(Object->GetStartPos());
		Object->GetRenderer()->ChangeFrameAnimation("Ph2DeribsA");
		Object->SetAnimationName("Ph2DeribsA");
	}

	{
		BreakObject* Object = CreateActor<BreakObject>(GameObjectGroup::UI);
		Object->SetStartPos({ 870.0f, 50.0f, (int)ZOrder::UI });
		Object->GetTransform().SetWorldPosition(Object->GetStartPos());
		Object->GetRenderer()->ChangeFrameAnimation("Ph2DeribsB");
		Object->SetAnimationName("Ph2DeribsB");
	}

	{
		BreakObject* Object = CreateActor<BreakObject>(GameObjectGroup::UI);
		Object->SetStartPos({ 450.0f, 50.0f, (int)ZOrder::UI });
		Object->GetTransform().SetWorldPosition(Object->GetStartPos());
		Object->GetRenderer()->ChangeFrameAnimation("Ph2DeribsB");
		Object->SetAnimationName("Ph2DeribsB");
	}

	{
		BreakObject* Object = CreateActor<BreakObject>(GameObjectGroup::UI);
		Object->SetStartPos({ 640, 50.0f, (int)ZOrder::UI });
		Object->GetTransform().SetWorldPosition(Object->GetStartPos());
		Object->GetRenderer()->ChangeFrameAnimation("Ph2DeribsC");
		Object->SetAnimationName("Ph2DeribsC");
	}

	{
		BreakObject* Object = CreateActor<BreakObject>(GameObjectGroup::UI);
		Object->SetStartPos({ 1000, 50.0f, (int)ZOrder::UI });
		Object->GetTransform().SetWorldPosition(Object->GetStartPos());
		Object->GetRenderer()->ChangeFrameAnimation("Ph2DeribsD");
		Object->SetAnimationName("Ph2DeribsD");
	}

	{
		BreakObject* Object = CreateActor<BreakObject>(GameObjectGroup::UI);
		Object->SetStartPos({ 640, 30.0f, (int)ZOrder::UI });
		Object->GetTransform().SetWorldPosition(Object->GetStartPos());
		Object->GetRenderer()->ChangeFrameAnimation("Ph2BreakMidLeftFall");
		Object->SetAnimationName("Ph2BreakMidLeftFall");
	}

	{
		BreakObject* Object = CreateActor<BreakObject>(GameObjectGroup::UI);
		Object->SetStartPos({ 1150, 30.0f, (int)ZOrder::UI });
		Object->GetTransform().SetWorldPosition(Object->GetStartPos());
		Object->GetRenderer()->ChangeFrameAnimation("Ph2BreakMidRightFall");
		Object->SetAnimationName("Ph2BreakMidRightFall");
	}

	{
		BreakObject* Object = CreateActor<BreakObject>(GameObjectGroup::UI);
		Object->SetStartPos({ 300, 30.0f, (int)ZOrder::UI });
		Object->GetTransform().SetWorldPosition(Object->GetStartPos());
		Object->GetRenderer()->ChangeFrameAnimation("Ph2BreakLeft");
		Object->SetAnimationName("Ph2BreakLeft");
	}

	{
		BreakObject* Object = CreateActor<BreakObject>(GameObjectGroup::UI);
		Object->SetStartPos({ 150, 30.0f, (int)ZOrder::UI });
		Object->GetTransform().SetWorldPosition(Object->GetStartPos());
		Object->GetRenderer()->ChangeFrameAnimation("Ph2BreakRight");
		Object->SetAnimationName("Ph2BreakRight");
	}

	{
		BreakObject* Object = CreateActor<BreakObject>(GameObjectGroup::UI);
		Object->SetStartPos({ 150, 30.0f, (int)ZOrder::UI });
		Object->GetTransform().SetWorldPosition(Object->GetStartPos());
		Object->GetRenderer()->GetTransform().PixLocalNegativeX();
		Object->GetRenderer()->ChangeFrameAnimation("Ph2DeribsD");
		Object->SetAnimationName("Ph2DeribsD");
	}

	{
		BreakObject* Object = CreateActor<BreakObject>(GameObjectGroup::UI);
		Object->SetStartPos({ 800, 30.0f, (int)ZOrder::UI });
		Object->GetTransform().SetWorldPosition(Object->GetStartPos());
		Object->GetRenderer()->GetTransform().PixLocalNegativeX();
		Object->GetRenderer()->ChangeFrameAnimation("Ph2BreakFrontFallLeft");
		Object->SetAnimationName("Ph2BreakFrontFallLeft");
	}

	{
		Background* OldFilm = CreateActor<Background>(GameObjectGroup::UI);
		OldFilmRenderer = OldFilm->CreateComponent<GameEngineTextureRenderer>();
		OldFilmRenderer->CreateFrameAnimationFolder("03ScreenFX", FrameAnimation_DESC("03ScreenFX", 0.1f, true));
		OldFilmRenderer->ChangeFrameAnimation("03ScreenFX");
		OldFilmRenderer->GetTransform().SetLocalScale({ 1280.0f, 720.0f, 1.0f });
		OldFilmRenderer->GetTransform().SetLocalPosition({ 640.0f, -360.0f, (int)ZOrder::UI });
		OldFilmRenderer->GetPixelData().PlusColor.a -= 1;
		OldFilmRenderer->Off();
	}

	Background* Iris = CreateActor<Background>(GameObjectGroup::UI);
	IrisRenderer = Iris->CreateComponent<GameEngineTextureRenderer>();
	IrisRenderer->GetTransform().SetLocalScale({ 1280.0f, 720.0f, 1.0f });
	IrisRenderer->GetTransform().SetWorldPosition({ 640.0f, -360.0f });
	IrisRenderer->CreateFrameAnimationFolder("IrisAStart", FrameAnimation_DESC("IrisA", 0.07f, false));
	IrisRenderer->CreateFrameAnimationFolder("IrisA", FrameAnimation_DESC("IrisA", 0, 0, 0.07f, true));
	IrisRenderer->CreateFrameAnimationFolder("IrisBStart", FrameAnimation_DESC("IrisB", 0.07f, true));
	IrisRenderer->AnimationBindEnd("IrisAStart", std::bind(&SaltBakerLevel::OnIrisAnimationFrameEnd, this, std::placeholders::_1));
	IrisRenderer->ChangeFrameAnimation("IrisA");
	IrisRenderer->ChangeCamera(CAMERAORDER::IRISCAMERA);

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
	ElapsedTime += _DeltaTime;

	if (true == Phase2BreakOn)
	{

	}

	if (true == BackgroundMoveOn)
	{
		if (false == BackgroundMoveFinished)
		{
			if (KitchenRenderer->GetTransform().GetWorldPosition().y > -1550)
			{
				KitchenRenderer->GetTransform().SetWorldMove(float4::DOWN * _DeltaTime * 1000);
			}
			else
			{
				BackgroundMoveFinished = true;
			}
		}
	}

	if (ElapsedTime > 1.0f && OnceCheck == false)
	{
		IrisRenderer->ChangeFrameAnimation("IrisAStart");
		OnceCheck = true;
	}

	if (true == GameEngineInput::GetInst()->IsDown("LevelChange"))
	{
		GEngine::ChangeLevel("WorldMap");
	}

	if (CurrentPhase != BeforePhase)
	{
		BeforePhase = CurrentPhase;

		if (CurrentPhase == Phase::Phase1)
		{
			Ph1Boss = CreateActor<SaltBaker>();
			Ph1Boss->GetTransform().SetWorldPosition({ 640.0f,-360.0f, (int)ZOrder::Player + 2});
			Ph1Boss->SetBackgroundRenderer(KitchenRendererTopper);

			Ph1Monster = CreateActor<Chicken>();
			Ph1Monster->GetTransform().SetWorldPosition({ 640.0f, -50.0f, (int)ZOrder::Player+1 });

			InGameCuphead* Cuphead = CreateActor<InGameCuphead>(GameObjectGroup::Player);
			Cuphead->GetTransform().SetWorldPosition({ 640.0f,-360.0f, (int)ZOrder::Player });
			Cuphead->SetColMapImage(ColMapRenderer);
			Cuphead->GetRenderer()->ChangeCamera(CAMERAORDER::ROTATECAMERA);

			if (nullptr != State)
			{
				Cuphead->SetHP(State->MaxHP);
				Cuphead->SetOnDashInvisible(State->OnDashInvisible);
			}
			Player = Cuphead;
		}

		else if (CurrentPhase == Phase::Phase3)
		{
			ColMapRenderer->SetTexture("SBPh3ColMap.png");
			CogWheel* Ph3Monster1 = CreateActor<CogWheel>();
			Ph3Monster1->GetTransform().SetWorldPosition({ 300.0f, -650.0f });
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

void SaltBakerLevel::OnIrisAnimationFrameEnd(const FrameAnimation_DESC& _Info)
{
	IrisRenderer->Off();
	SetPhase(Phase::Phase1);
}
