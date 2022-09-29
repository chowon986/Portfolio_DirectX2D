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
#include "CharacterScore.h"
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
	, TornadoCheck(false)
	, ActorNum(0)
	, OldFilmTimeCountOn(true)
{
}

SaltBakerLevel::~SaltBakerLevel()
{
}

void SaltBakerLevel::LevelStartEvent()
{
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

	{
		std::list<GameEngineActor*> Actors = GetGroup(GameObjectGroup::CharacterScore);
		for (GameEngineActor* Actor : Actors)
		{
			if (CharacterScore* _Score = dynamic_cast<CharacterScore*>(Actor))
			{
				Score = _Score;

				Score->PlayTime = 0.0f;
				Score->HP = 0;
				Score->Parry = 0;
				Score->UseCard = 0;
				Score->SkillLevel = 2;
			}
		}
	}
}

void SaltBakerLevel::LevelEndEvent()
{
	if (nullptr != Score)
	{
		Score->PlayTime = PlayElapsedTime;
		Score->HP = Player->GetHP();
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
		RendererB->CreateFrameAnimationFolder("Ph4WarningSKy", FrameAnimation_DESC("Ph4WarningSKy", 0.1f, true));
		RendererB->AnimationBindFrame("Ph4WarningSKy", std::bind(&SaltBakerLevel::OnPh4WarningSkyAnimationFrameChanged, this, std::placeholders::_1));
		RendererB->ChangeFrameAnimation("Ph3Sky");
		RendererB->SetScaleModeImage();
		RendererB->GetTransform().SetLocalPosition({ 640.0f, -160.0f, (int)ZOrder::Background + 1 });
		BackgroundB->SetRenderer(RendererB);
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

		Background* BackgroundH = CreateActor<Background>(GameObjectGroup::UI); // 밖
		GameEngineTextureRenderer* RendererH = BackgroundH->CreateComponent<GameEngineTextureRenderer>();
		RendererH->CreateFrameAnimationFolder("SaltManBust", FrameAnimation_DESC("SaltManBust", 0.05f, true));
		RendererH->ChangeFrameAnimation("SaltManBust");
		RendererH->SetScaleModeImage();
		RendererH->GetTransform().SetWorldPosition({ 850.0f, -250.0f,  (int)ZOrder::Background - 0.5f});
		BackgroundH->Off();

		Background* BackgroundI = CreateActor<Background>(GameObjectGroup::UI); // 밖
		GameEngineTextureRenderer* RendererI = BackgroundI->CreateComponent<GameEngineTextureRenderer>();
		RendererI->CreateFrameAnimationFolder("SaltManBustRightBackIdle", FrameAnimation_DESC("SaltManBustRightBackIdle", 0.05f, true));
		RendererI->ChangeFrameAnimation("SaltManBustRightBackIdle");
		RendererI->SetScaleModeImage();
		RendererI->GetTransform().SetWorldPosition({ 1040.0f, -260.0f,  (int)ZOrder::Background });
		BackgroundI->Off();

		Background* BackgroundJ = CreateActor<Background>(GameObjectGroup::UI); // 밖
		GameEngineTextureRenderer* RendererJ = BackgroundJ->CreateComponent<GameEngineTextureRenderer>();
		RendererJ->CreateFrameAnimationFolder("SaltManBustCrack", FrameAnimation_DESC("SaltManBustCrack", 0.05f, true));
		RendererJ->AnimationBindFrame("SaltManBustCrack", std::bind(&SaltBakerLevel::OnSaltManBustCrackAnimationFrameChanged, this, std::placeholders::_1));
		RendererJ->ChangeFrameAnimation("SaltManBustCrack");
		RendererJ->SetScaleModeImage();
		RendererJ->SetPivot(PIVOTMODE::LEFTBOT);
		RendererJ->GetTransform().SetWorldPosition({ 650, -350.0f, (int)ZOrder::Background - 1 });
		BackgroundJ->Off();

		Background* BackgroundK = CreateActor<Background>(GameObjectGroup::UI); // 밖
		GameEngineTextureRenderer* RendererK = BackgroundK->CreateComponent<GameEngineTextureRenderer>();
		RendererK->CreateFrameAnimationFolder("SaltManBustLeft", FrameAnimation_DESC("SaltManBustLeft", 0.05f, false));
		RendererK->ChangeFrameAnimation("SaltManBustLeft");
		RendererK->SetScaleModeImage();
		RendererK->GetTransform().SetWorldPosition({ 700.0f, -260.0f, (int)ZOrder::Background});
		BackgroundK->Off();

		Background* BackgroundL = CreateActor<Background>(GameObjectGroup::UI); // 밖
		GameEngineTextureRenderer* RendererL = BackgroundL->CreateComponent<GameEngineTextureRenderer>();
		RendererL->CreateFrameAnimationFolder("SaltManBustRight", FrameAnimation_DESC("SaltManBustRight", 0.05f, false));
		RendererL->AnimationBindFrame("SaltManBustRight", std::bind(&SaltBakerLevel::OnSaltManBustRightFrameChanged, this, std::placeholders::_1));
		RendererL->ChangeFrameAnimation("SaltManBustRight");
		RendererL->SetScaleModeImage();
		RendererL->GetTransform().SetWorldPosition({ 850.0f, -260.0f, (int)ZOrder::Background - 0.3 });
		BackgroundL->Off();

		BackgroundActor.insert(std::make_pair(0, BackgroundA));
		BackgroundActor.insert(std::make_pair(1, BackgroundB));
		BackgroundActor.insert(std::make_pair(2, BackgroundC));
		BackgroundActor.insert(std::make_pair(3, BackgroundD));
		BackgroundActor.insert(std::make_pair(4, BackgroundE));
		BackgroundActor.insert(std::make_pair(5, BackgroundF));
		BackgroundActor.insert(std::make_pair(6, BackgroundG));
		BackgroundActor.insert(std::make_pair(7, BackgroundH));
		BackgroundActor.insert(std::make_pair(8, BackgroundI));
		BackgroundActor.insert(std::make_pair(9, BackgroundJ));
		BackgroundActor.insert(std::make_pair(10, BackgroundK));
		BackgroundActor.insert(std::make_pair(11, BackgroundL));

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

		BreakObject* TornadoA = CreateActor<BreakObject>(GameObjectGroup::UI); // 작은거
		TornadoA->SetStartPos({ 500.0f, 30.0f, (int)ZOrder::UI });
		TornadoA->GetTransform().SetWorldPosition(TornadoA->GetStartPos());
		TornadoA->GetRenderer()->ChangeFrameAnimation("LittleTornadoA");
		TornadoA->SetAnimationName("LittleTornadoA");
		TornadoA->Off();


		BreakObject* TornadoB = CreateActor<BreakObject>(GameObjectGroup::UI); // 큰거
		TornadoB->SetStartPos({ 800.0f, -500.0f, (int)ZOrder::UI });
		TornadoB->GetTransform().SetWorldPosition(TornadoB->GetStartPos());
		TornadoB->GetRenderer()->ChangeFrameAnimation("LittleTornadoB");
		TornadoB->SetAnimationName("LittleTornadoB");
		TornadoB->Off();

		BreakObject* TornadoC = CreateActor<BreakObject>(GameObjectGroup::UI); // 작은거
		TornadoC->SetStartPos({ 1100.0f,-500.0f, (int)ZOrder::UI });
		TornadoC->GetTransform().SetWorldPosition(TornadoC->GetStartPos());
		TornadoC->GetRenderer()->ChangeFrameAnimation("LittleTornadoA");
		TornadoC->SetAnimationName("LittleTornadoA");
		TornadoC->Off();

		BreakObject* TornadoD = CreateActor<BreakObject>(GameObjectGroup::UI); // 큰거
		TornadoD->SetStartPos({ 200.0f,-500.0f, (int)ZOrder::UI });
		TornadoD->GetTransform().SetWorldPosition(TornadoD->GetStartPos());
		TornadoD->GetRenderer()->ChangeFrameAnimation("LittleTornadoB");
		TornadoD->SetAnimationName("LittleTornadoB");
		TornadoD->Off();

		BreakObject* SaltMan = CreateActor<BreakObject>(GameObjectGroup::UI); // 안
		SaltMan->SetStartPos({ 750.0f, -400.0f, (int)ZOrder::Background - 0.05});
		SaltMan->GetTransform().SetWorldPosition(SaltMan->GetStartPos());
		SaltMan->GetRenderer()->ChangeFrameAnimation("SaltManIntro");
		SaltMan->SetAnimationName("SaltManIntro");
		SaltMan->Off();

		BreakObject* TornadoE = CreateActor<BreakObject>(GameObjectGroup::UI); // 작은거
		TornadoE->SetStartPos({ 640.0f, -500.0f, (int)ZOrder::UI });
		TornadoE->GetTransform().SetWorldPosition(TornadoE->GetStartPos());
		TornadoE->GetRenderer()->ChangeFrameAnimation("LittleTornadoA");
		TornadoE->SetAnimationName("LittleTornadoA");
		TornadoE->Off();

		BreakObjectActor.insert(std::make_pair(0, ObjectA));
		BreakObjectActor.insert(std::make_pair(1, ObjectK));
		BreakObjectActor.insert(std::make_pair(2, ObjectB));
		BreakObjectActor.insert(std::make_pair(3, ObjectJ));
		BreakObjectActor.insert(std::make_pair(4, ObjectC));
		BreakObjectActor.insert(std::make_pair(5, ObjectI));
		BreakObjectActor.insert(std::make_pair(6, ObjectD));
		BreakObjectActor.insert(std::make_pair(7, ObjectH));
		BreakObjectActor.insert(std::make_pair(8, ObjectE));
		BreakObjectActor.insert(std::make_pair(9, ObjectG));
		BreakObjectActor.insert(std::make_pair(10, ObjectF));
		BreakObjectActor.insert(std::make_pair(11, SaltMan));

		LittleTornadoActor.insert(std::make_pair(0, TornadoA));
		LittleTornadoActor.insert(std::make_pair(1, TornadoB));
		LittleTornadoActor.insert(std::make_pair(2, TornadoC));
		LittleTornadoActor.insert(std::make_pair(3, TornadoD));
		LittleTornadoActor.insert(std::make_pair(4, TornadoE));
		LittleTornadoActor.insert(std::make_pair(5, TornadoE));

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
	TornadoElapsedTime += _DeltaTime;
	PlayElapsedTime += _DeltaTime;

	if (TornadoCheck == true)
	{
		if (ActorNum < 7 && TornadoElapsedTime > 0.5)
		{
			if (nullptr != LittleTornadoActor[ActorNum])
			{
				LittleTornadoActor[ActorNum]->On();
			}
			++ActorNum;
			TornadoElapsedTime = 0.0f;
		}
		else if(ActorNum == 7)
		{
			TornadoCheck = false;
		}
	}

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

		if (OldFilmOnceCheck == true && OldFilmElapsedTime > 0.5 && OldFilmTimeCountOn == true)
		{
			for (int i = 0; i < 9; i++)
			{
				if (true == Kitchen->IsUpdate())
				{
					Kitchen->Death();
					KitchenTopper->Death();
				}

				if (nullptr != BackgroundActor[i])
				{
					BackgroundActor[i]->On();
				}
			}

			if (GetPhase() != Phase::Phase4)
			{
				SetPhase(Phase::Phase3);
				OldFilmRenderer->Off();
				OldFilmTimeCountOn = false;
			}
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

			Cuphead = CreateActor<InGameCuphead>(GameObjectGroup::Player);
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
			Cuphead->SetColMapImage(ColMapRenderer);
			CogWheel* Ph3Monster1 = CreateActor<CogWheel>();
			Ph3Monster1->GetTransform().SetWorldPosition({ 300.0f, -650.0f });
		}

		else if (CurrentPhase == Phase::Phase4)
		{
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

void SaltBakerLevel::OnPh4WarningSkyAnimationFrameChanged(const FrameAnimation_DESC& _Info)
{
	if (_Info.CurFrame ==3)
	{
		TornadoCheck = true;
	}

	if (_Info.CurFrame == 7)
	{
		if (Background* Actor = dynamic_cast<Background*>(BackgroundActor[1]))
		{
			Actor->GetRenderer()->ChangeFrameAnimation("Ph3Sky");
		}
	}
}

void SaltBakerLevel::OnSaltManBustCrackAnimationFrameChanged(const FrameAnimation_DESC& _Info)
{
	if (_Info.CurFrame == 12)
	{
		BackgroundActor[10]->On();
		BackgroundActor[11]->On();
		BreakObjectActor[11]->On();
		BackgroundActor[7]->Death();
		BackgroundActor[8]->Death();
		BackgroundActor[9]->Death();
	}
}

void SaltBakerLevel::OnSaltManBustRightFrameChanged(const FrameAnimation_DESC& _Info)
{
	if (_Info.CurFrame < 8)
	{
		if (Background* Actor = dynamic_cast<Background*>(BackgroundActor[11]))
		{
			Actor->GetTransform().SetLocalMove(float4::RIGHT * GameEngineTime::GetDeltaTime() * 3000);
		}
	}
}
