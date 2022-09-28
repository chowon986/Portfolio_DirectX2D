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
	, RendererNum(0)
	, OldFilmOnceCheck(false)
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
		ColMapRenderer->GetTransform().SetWorldPosition({640.0f, -360.0f, (int)ZOrder::Background + 5 });
		SetMainColMapImage(ColMapRenderer);
	}

	{
		Kitchen = CreateActor<Background>(GameObjectGroup::UI);
		KitchenRenderer = Kitchen->CreateComponent<GameEngineTextureRenderer>();
		KitchenRenderer->SetTexture("MoveKitchen.png");
		KitchenRenderer->ScaleToTexture();
		KitchenRenderer->GetTransform().SetLocalPosition({ 640.0f, 843.0f, (int)ZOrder::Background });
	}
	
	{
		KitchenTopper = CreateActor<Background>(GameObjectGroup::UI);
		KitchenRendererTopper = KitchenTopper->CreateComponent<GameEngineTextureRenderer>();
		KitchenRendererTopper->CreateFrameAnimationFolder("Kitchen", FrameAnimation_DESC("Kitchen", 0.1f, true));
		KitchenRendererTopper->ChangeFrameAnimation("Kitchen");
		KitchenRendererTopper->SetScaleModeImage();
		KitchenRendererTopper->GetTransform().SetLocalPosition({ 640.0f, -360.0f, (int)ZOrder::Background - 1});
	}

	{
		Background* BackgroundA = CreateActor<Background>(GameObjectGroup::UI);
		GameEngineTextureRenderer* RendererA = BackgroundA->CreateComponent<GameEngineTextureRenderer>();
		RendererA->SetTexture("Sky.png");
		RendererA->ScaleToTexture();
		RendererA->GetTransform().SetLocalPosition({ 640.0f, 0.0f, (int)ZOrder::Background + 1 });
		BackgroundA->Off();

		Background* BackgroundB = CreateActor<Background>(GameObjectGroup::UI);
		GameEngineTextureRenderer* RendererB = BackgroundB->CreateComponent<GameEngineTextureRenderer>();
		RendererB->CreateFrameAnimationFolder("Ph3Sky", FrameAnimation_DESC("Ph3Sky", 0.1f, true));
		RendererB->ChangeFrameAnimation("Ph3Sky");
		RendererB->ScaleToTexture();
		RendererB->GetTransform().SetLocalPosition({ 640.0f, -160.0f, (int)ZOrder::Background + 1 });
		BackgroundB->Off();

		Background* BackgroundC = CreateActor<Background>(GameObjectGroup::UI);
		GameEngineTextureRenderer* RendererC = BackgroundC->CreateComponent<GameEngineTextureRenderer>();
		RendererC->SetTexture("Ph3Background1.png");
		RendererC->ScaleToTexture();
		RendererC->GetTransform().SetLocalPosition({ 675.0f, -260.0f, (int)ZOrder::Background });
		BackgroundC->Off();

		Background* BackgroundD = CreateActor<Background>(GameObjectGroup::UI);
		GameEngineTextureRenderer* RendererD = BackgroundD->CreateComponent<GameEngineTextureRenderer>();
		RendererD->SetTexture("Ph3Background2.png");
		RendererD->ScaleToTexture();
		RendererD->GetTransform().SetLocalPosition({ 630.0f, -320.0f, (int)ZOrder::Background - 1 });
		BackgroundD->Off();

		Background* BackgroundE = CreateActor<Background>(GameObjectGroup::UI);
		GameEngineTextureRenderer* RendererE = BackgroundE->CreateComponent<GameEngineTextureRenderer>();
		RendererE->SetTexture("Ph3Background3.png");
		RendererE->ScaleToTexture();
		RendererE->GetTransform().SetLocalPosition({ 655.0f, -610.0f, (int)ZOrder::Background - 2 });
		BackgroundE->Off();

		Background* BackgroundF = CreateActor<Background>(GameObjectGroup::UI);
		GameEngineTextureRenderer* RendererF = BackgroundF->CreateComponent<GameEngineTextureRenderer>();
		RendererF->SetTexture("Ph3Background4.png");
		RendererF->ScaleToTexture();
		RendererF->GetTransform().SetLocalPosition({ 450.0f, -220.0f, (int)ZOrder::Background - 0.5 });
		BackgroundF->Off();

		Background* BackgroundG = CreateActor<Background>(GameObjectGroup::UI);
		GameEngineTextureRenderer* RendererG = BackgroundG->CreateComponent<GameEngineTextureRenderer>();
		RendererG->SetTexture("Ph3Background5.png");
		RendererG->ScaleToTexture();
		RendererG->GetTransform().SetLocalPosition({ 610.0f, -400.0f, (int)ZOrder::Background - 3 });
		BackgroundG->Off();

		BackgroundRenderer.insert(std::make_pair(0, BackgroundA));
		BackgroundRenderer.insert(std::make_pair(1, BackgroundB));
		BackgroundRenderer.insert(std::make_pair(2, BackgroundC));
		BackgroundRenderer.insert(std::make_pair(3, BackgroundD));
		BackgroundRenderer.insert(std::make_pair(4, BackgroundE));
		BackgroundRenderer.insert(std::make_pair(5, BackgroundF));
		BackgroundRenderer.insert(std::make_pair(6, BackgroundG));
	}

		// BreakObject
	{
		BreakObject* ObjectA = CreateActor<BreakObject>(GameObjectGroup::UI);
		ObjectA->SetStartPos({ 1100.0f, 50.0f, (int)ZOrder::UI });
		ObjectA-> GetTransform().SetWorldPosition(ObjectA->GetStartPos());
		ObjectA->GetRenderer()->ChangeFrameAnimation("Ph2DeribsA");
		ObjectA->SetAnimationName("Ph2DeribsA");
		ObjectA->Off();

		BreakObject* ObjectB = CreateActor<BreakObject>(GameObjectGroup::UI);
		ObjectB->SetStartPos({ 870.0f, 50.0f, (int)ZOrder::UI });
		ObjectB->GetTransform().SetWorldPosition(ObjectB->GetStartPos());
		ObjectB->GetRenderer()->ChangeFrameAnimation("Ph2DeribsB");
		ObjectB->SetAnimationName("Ph2DeribsB");
		ObjectB->Off();

		BreakObject* ObjectC = CreateActor<BreakObject>(GameObjectGroup::UI);
		ObjectC->SetStartPos({ 450.0f, 50.0f, (int)ZOrder::UI });
		ObjectC->GetTransform().SetWorldPosition(ObjectC->GetStartPos());
		ObjectC->GetRenderer()->ChangeFrameAnimation("Ph2DeribsB");
		ObjectC->SetAnimationName("Ph2DeribsB");
		ObjectC->Off();

		BreakObject* ObjectD = CreateActor<BreakObject>(GameObjectGroup::UI);
		ObjectD->SetStartPos({ 640, 50.0f, (int)ZOrder::UI });
		ObjectD->GetTransform().SetWorldPosition(ObjectD->GetStartPos());
		ObjectD->GetRenderer()->ChangeFrameAnimation("Ph2DeribsC");
		ObjectD->SetAnimationName("Ph2DeribsC");
		ObjectD->Off();

		BreakObject* ObjectE = CreateActor<BreakObject>(GameObjectGroup::UI);
		ObjectE->SetStartPos({ 1000, 50.0f, (int)ZOrder::UI });
		ObjectE->GetTransform().SetWorldPosition(ObjectE->GetStartPos());
		ObjectE->GetRenderer()->ChangeFrameAnimation("Ph2DeribsD");
		ObjectE->SetAnimationName("Ph2DeribsD");
		ObjectE->Off();

		BreakObject* ObjectF = CreateActor<BreakObject>(GameObjectGroup::UI);
		ObjectF->SetStartPos({ 640, 30.0f, (int)ZOrder::UI });
		ObjectF->GetTransform().SetWorldPosition(ObjectF->GetStartPos());
		ObjectF->GetRenderer()->ChangeFrameAnimation("Ph2BreakMidLeftFall");
		ObjectF->SetAnimationName("Ph2BreakMidLeftFall");
		ObjectF->Off();

		BreakObject* ObjectG = CreateActor<BreakObject>(GameObjectGroup::UI);
		ObjectG->SetStartPos({ 1150, 30.0f, (int)ZOrder::UI });
		ObjectG->GetTransform().SetWorldPosition(ObjectG->GetStartPos());
		ObjectG->GetRenderer()->ChangeFrameAnimation("Ph2BreakMidRightFall");
		ObjectG->SetAnimationName("Ph2BreakMidRightFall");
		ObjectG->Off();

		BreakObject* ObjectH = CreateActor<BreakObject>(GameObjectGroup::UI);
		ObjectH->SetStartPos({ 300, 30.0f, (int)ZOrder::UI });
		ObjectH->GetTransform().SetWorldPosition(ObjectH->GetStartPos());
		ObjectH->GetRenderer()->ChangeFrameAnimation("Ph2BreakLeft");
		ObjectH->SetAnimationName("Ph2BreakLeft");
		ObjectH->Off();

		BreakObject* ObjectI = CreateActor<BreakObject>(GameObjectGroup::UI);
		ObjectI->SetStartPos({ 150, 30.0f, (int)ZOrder::UI });
		ObjectI->GetTransform().SetWorldPosition(ObjectI->GetStartPos());
		ObjectI->GetRenderer()->ChangeFrameAnimation("Ph2BreakRight");
		ObjectI->SetAnimationName("Ph2BreakRight");
		ObjectI->Off();

		BreakObject* ObjectJ = CreateActor<BreakObject>(GameObjectGroup::UI);
		ObjectJ->SetStartPos({ 150, 30.0f, (int)ZOrder::UI });
		ObjectJ->GetTransform().SetWorldPosition(ObjectJ->GetStartPos());
		ObjectJ->GetRenderer()->GetTransform().PixLocalNegativeX();
		ObjectJ->GetRenderer()->ChangeFrameAnimation("Ph2DeribsD");
		ObjectJ->SetAnimationName("Ph2DeribsD");
		ObjectJ->Off();

		BreakObject* ObjectK = CreateActor<BreakObject>(GameObjectGroup::UI);
		ObjectK->SetStartPos({ 800, 30.0f, (int)ZOrder::UI });
		ObjectK->GetTransform().SetWorldPosition(ObjectK->GetStartPos());
		ObjectK->GetRenderer()->GetTransform().PixLocalNegativeX();
		ObjectK->GetRenderer()->ChangeFrameAnimation("Ph2BreakFrontFallLeft");
		ObjectK->SetAnimationName("Ph2BreakFrontFallLeft");
		ObjectK->Off();

		BreakObjectActor.insert(std::make_pair(0, ObjectA));
		BreakObjectActor.insert(std::make_pair(2, ObjectB));
		BreakObjectActor.insert(std::make_pair(4, ObjectC));
		BreakObjectActor.insert(std::make_pair(6, ObjectD));
		BreakObjectActor.insert(std::make_pair(8, ObjectE));
		BreakObjectActor.insert(std::make_pair(10, ObjectF));
		BreakObjectActor.insert(std::make_pair(9, ObjectG));
		BreakObjectActor.insert(std::make_pair(7, ObjectH));
		BreakObjectActor.insert(std::make_pair(5, ObjectI));
		BreakObjectActor.insert(std::make_pair(3, ObjectJ));
		BreakObjectActor.insert(std::make_pair(1, ObjectK));

		for (int i = 0; i < 11; i++)
		{
			if (BreakObject* Actor = dynamic_cast<BreakObject*>(BreakObjectActor[i]))
			{
				Actor->GetRenderer()->ChangeCamera(CAMERAORDER::ROTATECAMERA2);
			}
		}
	}

	{
		Background* OldFilm = CreateActor<Background>(GameObjectGroup::UI);
		OldFilmRenderer = OldFilm->CreateComponent<GameEngineTextureRenderer>();
		OldFilmRenderer->CreateFrameAnimationFolder("03ScreenFX", FrameAnimation_DESC("03ScreenFX", 0.1f, true));
		OldFilmRenderer->ChangeFrameAnimation("03ScreenFX");
		OldFilmRenderer->GetTransform().SetLocalScale({ 1280.0f, 720.0f, 1.0f });
		OldFilmRenderer->GetTransform().SetLocalPosition({ 640.0f, -360.0f, (int)ZOrder::UI });
		OldFilmRenderer->Off();
		OldFilmRenderer->ChangeCamera(CAMERAORDER::ROTATECAMERA2);
	}

	{
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
	}

	GetMainCamera()->SetProjectionSize({ 1280.0f, 720.0f });
	GetRotateCamera()->SetProjectionSize({ 1536.0f, 864.0f });
	GetRotateCamera2()->SetProjectionSize({ 1280.0f, 720.0f });
	GetIrisCamera()->SetProjectionSize({ 1280.0f, 720.0f });

	GetMainCameraActorTransform().SetLocalPosition({ 640, -360 });
	GetRotateCameraActorTransform().SetLocalPosition({ 640, -360 });
	GetIrisCameraActorTransform().SetLocalPosition({ 640.0f, -360.0f });
	GetRotateCamera2ActorTransform().SetLocalPosition({ 640.0f, -360.0f });
	SetPhase(Phase::Phase1);
}

void SaltBakerLevel::Update(float _DeltaTime)
{
	ElapsedTime += _DeltaTime;
	BreakTime += _DeltaTime;
	OldFilmElapsedTime += _DeltaTime;

	if (true == Phase2BreakOn)
	{
		if (BreakTime > 0.5)
		{
			if (RendererNum <= 10)
			{
				BreakObjectActor[RendererNum]->On();
				++RendererNum;
				BreakTime = 0.0f;
			}
		}

		if (RendererNum == 11 && OldFilmOnceCheck == false)
		{
			OldFilmRenderer->On();
			for (int i = 0; i < 11; i++)
			{
				if (false == BreakObjectActor[i]->IsDeath())
				{
					BreakObjectActor[i]->Death();
				}
			}
			OldFilmElapsedTime = 0.0f;
			OldFilmOnceCheck = true;
		}

		if (OldFilmOnceCheck == true && OldFilmElapsedTime > 0.5)
		{
			for (int i = 0; i < 7; i++)
			{
				if (true == Kitchen->IsUpdate())
				{
					Kitchen->Death();
					KitchenTopper->Death();
				}

				BackgroundRenderer[i]->On();
			}
			SetPhase(Phase::Phase3);
			OldFilmRenderer->Off();
		}
	}

	if (ElapsedTime > 1.0f && OnceCheck == false)
	{
		IrisRenderer->ChangeFrameAnimation("IrisAStart");
		OnceCheck = true;
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

			Ph1Boss->SetChicken(Ph1Monster);

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
