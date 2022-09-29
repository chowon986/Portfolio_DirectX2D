#include "PreCompile.h"
#include "DogFightLevel.h"
#include "Background.h"
#include "InGameCuphead.h"
#include "BackgroundHills.h"
#include "BackgroundObject.h"
#include "Bulldog.h"
#include "BulldogPlane.h"
#include "Ph2Dog.h"
#include "CanteenPlane.h"
#include "DogCopter.h"
#include "WorldMapCuphead.h"
#include "CharacterState.h"
#include "CharacterScore.h"
#include <GameEngineCore/GameEngineBlur.h>
#include "PlayerHP.h"

DogFightLevel::DogFightLevel()
	: ColMapRenderer(nullptr)
	, Hills(nullptr)
	, BackgroundSkyRenderer(nullptr)
	, CloudA1(nullptr)
	, CloudA2(nullptr)
	, CloudB2(nullptr)
	, CloudC1(nullptr)
	, CloudC2(nullptr)
	, CloudD1(nullptr)
	, CloudD2(nullptr)
	, PlanePuffRight(nullptr)
	, PlanePuffLeft(nullptr)
	, PatchLeftA(nullptr)
	, PH1BullDog(nullptr)
	, PH1BulldogPlane(nullptr)
	, Cuphead(nullptr)
	, CaptainCanteenPlane(nullptr)
	, LeaderCopter(nullptr)
	, OnceCheck(false)
	, BulldogIntroRenderer(nullptr)
	, DogCopterIntroRenderer(nullptr)
	, OldState(InGameMonsterState::Idle)
	, IsRotateCompleted(false)
	, RotateElapsedTime(0.0f)
	, RotateTime(10)
	, PlayElapsedTime(0.0f)
{
}

DogFightLevel::~DogFightLevel()
{
}

void DogFightLevel::ColMapOnOffSwitch()
{
	if (true == GameEngineInput::GetInst()->IsDown("ColMapOnOffSwitch"))
	{
		BackgroundSkyRenderer->OnOffSwitch();
		Hills->OnOffSwitch();
	}
}

void DogFightLevel::LevelStartEvent()
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

void DogFightLevel::LevelEndEvent()
{
	if (nullptr != Score)
	{
		Score->PlayTime = PlayElapsedTime;
		Score->HP = Player->GetHP();
	}
}

void DogFightLevel::Start()
{
	GetMainCamera()->GetCameraRenderTarget()->AddEffect<GameEngineBlur>();
	GetBackgroundCamera()->GetCameraRenderTarget()->AddEffect<GameEngineBlur>();
	GetRotateCamera()->GetCameraRenderTarget()->AddEffect<GameEngineBlur>();
	GetRotateCamera2()->GetCameraRenderTarget()->AddEffect<GameEngineBlur>();

	if (false == GameEngineInput::GetInst()->IsKey("PhaseChangeKey"))
	{
		GameEngineInput::GetInst()->CreateKey("PhaseChangeKey", 'L');
	}

	{
		Background* ScreenLight = CreateActor<Background>(GameObjectGroup::UI);
		ScreenLightRenderer = ScreenLight->CreateComponent <GameEngineTextureRenderer>();
		ScreenLightRenderer->CreateFrameAnimationFolder("LightOn", FrameAnimation_DESC("IrisA", 0.05f,false));
		ScreenLightRenderer->CreateFrameAnimationFolder("LightOff", FrameAnimation_DESC("IrisA", 16, 16, 0.1f));
		ScreenLightRenderer->ChangeFrameAnimation("LightOff");
		ScreenLightRenderer->GetTransform().SetLocalScale({ 1280.0f, 720.0f, 0 });
		ScreenLightRenderer->SetPivot(PIVOTMODE::LEFTTOP);
		ScreenLightRenderer->AnimationBindEnd("LightOn", std::bind(&DogFightLevel::LightOnAnimaitonFrameFinished, this, std::placeholders::_1));
		ScreenLightRenderer->ChangeCamera(CAMERAORDER::IRISCAMERA);
	}
	{
		Background* ColMapImage = CreateActor<Background>(GameObjectGroup::UI);
		ColMapRenderer = ColMapImage->CreateComponent<GameEngineTextureRenderer>();
		if (ColMapImage == nullptr)
		{
			return;
		}
		//ColMapRenderer->SetTexture("Loading_background.png");
		ColMapRenderer->SetTexture("TestColMap.png");
		ColMapRenderer->ScaleToTexture();
		ColMapRenderer->SetPivot(PIVOTMODE::LEFTTOP);
		ColMapRenderer->GetTransform().SetLocalPosition({ ColMapRenderer->GetTransform().GetLocalPosition().x, ColMapRenderer->GetTransform().GetLocalPosition().y, (int)ZOrder::Background + 1 });
		SetMainColMapImage(ColMapRenderer);
		//ColMapRenderer->ChangeCamera(CAMERAORDER::BACKGROUND);
	}

	{
		Background* BackgroundSky = CreateActor<Background>(GameObjectGroup::UI);
		BackgroundSkyRenderer = BackgroundSky->CreateComponent<GameEngineTextureRenderer>();
		BackgroundSkyRenderer->SetTexture("background_sky_0001.png");
		BackgroundSkyRenderer->ScaleToTexture();
		BackgroundSkyRenderer->SetPivot(PIVOTMODE::LEFTTOP);
		BackgroundSkyRenderer->GetTransform().SetLocalPosition({ BackgroundSkyRenderer->GetTransform().GetLocalPosition().x, BackgroundSkyRenderer->GetTransform().GetLocalPosition().y + 250, (int)ZOrder::Background });
	}

	{
		Hills = CreateActor<BackgroundHills>(GameObjectGroup::UI);
		if (Hills == nullptr)
		{
			return;
		}
		Hills->GetTransform().SetLocalPosition({ -50, -420, (int)ZOrder::Background - 2 });

	}

	//Cloud
	{
		{
			CloudA1 = CreateActor<BackgroundObject>(GameObjectGroup::UI);
			if (CloudA1 == nullptr)
			{
				return;
			}
			GameEngineTextureRenderer* Renderer = CloudA1->GetRenderer();
			if (Renderer == nullptr)
			{
				return;
			}
			Renderer->CreateFrameAnimationFolder("CloudA1", FrameAnimation_DESC("CloudA1", 0.06f, true));
			Renderer->AnimationBindEnd("CloudA1", std::bind(&DogFightLevel::ResetPositionCloudLeftA, this, std::placeholders::_1));
			Renderer->ChangeFrameAnimation("CloudA1");
			Renderer->SetPivot(PIVOTMODE::LEFT);
			CloudA1->GetTransform().SetLocalPosition({ -150, -250, (int)ZOrder::Background - 1 });
			CloudA1->SetDirection((float4::RIGHT * 2) + (float4::DOWN * 0.5));
			CloudA1->SetMoveSpeed(250.0f);
		}

		{
			CloudA2 = CreateActor<BackgroundObject>(GameObjectGroup::UI);
			if (CloudA2 == nullptr)
			{
				return;
			}
			GameEngineTextureRenderer* Renderer = CloudA2->GetRenderer();
			if (Renderer == nullptr)
			{
				return;
			}
			Renderer->CreateFrameAnimationFolder("CloudA1", FrameAnimation_DESC("CloudA1", 0.06f, true));
			Renderer->AnimationBindEnd("CloudA1", std::bind(&DogFightLevel::ResetPositionCloudLeftA2, this, std::placeholders::_1));
			Renderer->ChangeFrameAnimation("CloudA1");
			Renderer->SetPivot(PIVOTMODE::RIGHT);
			Renderer->GetTransform().PixLocalNegativeX();
			CloudA2->GetTransform().SetLocalPosition({ 1430, -250, (int)ZOrder::Background - 1 });
			CloudA2->SetDirection((float4::LEFT * 2) + (float4::DOWN * 0.5));
			CloudA2->SetMoveSpeed(250.0f);
		}

		{
			CloudB2 = CreateActor<BackgroundObject>(GameObjectGroup::UI);
			if (CloudB2 == nullptr)
			{
				return;
			}
			GameEngineTextureRenderer* Renderer = CloudB2->GetRenderer();
			if (Renderer == nullptr)
			{
				return;
			}
			Renderer->CreateFrameAnimationFolder("CloudB2", FrameAnimation_DESC("CloudB2", 0.06f, true));
			Renderer->AnimationBindEnd("CloudB2", std::bind(&DogFightLevel::ResetPositionCloudLeftB, this, std::placeholders::_1));
			Renderer->ChangeFrameAnimation("CloudB2");
			Renderer->SetPivot(PIVOTMODE::LEFT);
			CloudB2->GetTransform().SetLocalPosition({ -150, -20, (int)ZOrder::Background - 1 });
			CloudB2->SetDirection((float4::RIGHT * 2) + float4::DOWN);
			CloudB2->SetMoveSpeed(250.0f);
		}

		{
			CloudC1 = CreateActor<BackgroundObject>(GameObjectGroup::UI);
			if (CloudC1 == nullptr)
			{
				return;
			}
			GameEngineTextureRenderer* Renderer = CloudC1->GetRenderer();
			if (Renderer == nullptr)
			{
				return;
			}
			Renderer->CreateFrameAnimationFolder("CloudC1", FrameAnimation_DESC("CloudC1", 0.05f, true));
			Renderer->AnimationBindEnd("CloudC1", std::bind(&DogFightLevel::ResetPositionCloudLeftC, this, std::placeholders::_1));
			Renderer->ChangeFrameAnimation("CloudC1");
			Renderer->GetTransform().PixLocalNegativeX();
			Renderer->SetPivot(PIVOTMODE::RIGHT);
			CloudC1->GetTransform().SetLocalPosition({ 1200, -20, (int)ZOrder::Background - 1 });
			CloudC1->SetDirection((float4::LEFT * 2) + (float4::DOWN * 1.5));
			CloudC1->SetMoveSpeed(250.0f);
		}

		{
			CloudC2 = CreateActor<BackgroundObject>(GameObjectGroup::UI);
			if (CloudC2 == nullptr)
			{
				return;
			}
			GameEngineTextureRenderer* Renderer = CloudC2->GetRenderer();
			if (Renderer == nullptr)
			{
				return;
			}
			Renderer->CreateFrameAnimationFolder("CloudC2", FrameAnimation_DESC("CloudC2", 0.05f, true));
			Renderer->AnimationBindEnd("CloudC2", std::bind(&DogFightLevel::ResetPositionCloudLeftC2, this, std::placeholders::_1));
			Renderer->ChangeFrameAnimation("CloudC2");
			Renderer->SetPivot(PIVOTMODE::LEFT);
			CloudC2->GetTransform().SetLocalPosition({ 150, -20, (int)ZOrder::Background - 1 });
			CloudC2->SetDirection((float4::RIGHT * 1.5) + (float4::DOWN * 1.5));
			CloudC2->SetMoveSpeed(250.0f);
		}

		{
			CloudD1 = CreateActor<BackgroundObject>(GameObjectGroup::UI);
			if (CloudD1 == nullptr)
			{
				return;
			}
			GameEngineTextureRenderer* Renderer = CloudD1->GetRenderer();
			if (Renderer == nullptr)
			{
				return;
			}
			Renderer->CreateFrameAnimationFolder("CloudD1", FrameAnimation_DESC("CloudD1", 0.05f, true));
			Renderer->AnimationBindEnd("CloudD1", std::bind(&DogFightLevel::ResetPositionCloudLeftD, this, std::placeholders::_1));
			Renderer->ChangeFrameAnimation("CloudD1");
			Renderer->SetPivot(PIVOTMODE::CENTER);
			CloudD1->GetTransform().SetLocalPosition({ 640, -20, (int)ZOrder::Background - 1 });
			CloudD1->SetDirection(float4::DOWN * 1.8);
			CloudD1->SetMoveSpeed(250.0f);
		}

		{
			CloudD2 = CreateActor<BackgroundObject>(GameObjectGroup::UI);
			if (CloudD2 == nullptr)
			{
				return;
			}
			GameEngineTextureRenderer* Renderer = CloudD2->GetRenderer();
			if (Renderer == nullptr)
			{
				return;
			}
			Renderer->CreateFrameAnimationFolder("CloudD2", FrameAnimation_DESC("CloudD2", 0.05f, true));
			Renderer->AnimationBindEnd("CloudD2", std::bind(&DogFightLevel::ResetPositionCloudLeftD2, this, std::placeholders::_1));
			Renderer->ChangeFrameAnimation("CloudD2");
			Renderer->SetPivot(PIVOTMODE::CENTER);
			CloudD2->GetTransform().SetLocalPosition({ 1130, -20, (int)ZOrder::Background - 1 });
			CloudD2->SetDirection((float4::LEFT * 1.5) + (float4::DOWN * 1.5));
			CloudD2->SetMoveSpeed(250.0f);
		}

		{
			PlanePuffRight = CreateActor<BackgroundObject>(GameObjectGroup::Monster);
			if (PlanePuffRight == nullptr)
			{
				return;
			}
			GameEngineTextureRenderer* Renderer = PlanePuffRight->GetRenderer();
			Renderer->CreateFrameAnimationFolder("BulldogPlanePuffA", FrameAnimation_DESC("BulldogPlanePuffA", 0.03f, true));
			Renderer->AnimationBindEnd("BulldogPlanePuffA", std::bind(&DogFightLevel::ResetPositionPlanePuffRight, this, std::placeholders::_1));
			Renderer->ChangeFrameAnimation("BulldogPlanePuffA");
			Renderer->ScaleToTexture();
			Renderer->SetPivot(PIVOTMODE::CENTER);
			PlanePuffRight->GetTransform().SetLocalPosition({ 900, -200, (int)ZOrder::NPC + 4 });
			PlanePuffRight->SetDirection((float4::LEFT * 1.5) + (float4::UP));
			PlanePuffRight->SetMoveSpeed(200.0f);
		}

		{
			PlanePuffLeft = CreateActor<BackgroundObject>(GameObjectGroup::Monster);
			if (PlanePuffLeft == nullptr)
			{
				return;
			}
			GameEngineTextureRenderer* Renderer = PlanePuffLeft->GetRenderer();
			Renderer->CreateFrameAnimationFolder("BulldogPlanePuffB", FrameAnimation_DESC("BulldogPlanePuffB", 0.03f, true));
			Renderer->AnimationBindEnd("BulldogPlanePuffB", std::bind(&DogFightLevel::ResetPositionPlanePuffLeft, this, std::placeholders::_1));
			Renderer->ChangeFrameAnimation("BulldogPlanePuffB");
			Renderer->ScaleToTexture();
			Renderer->SetPivot(PIVOTMODE::CENTER);
			PlanePuffLeft->GetTransform().SetLocalPosition({ 380, -200, (int)ZOrder::NPC + 4 });
			PlanePuffLeft->SetDirection((float4::RIGHT * 1.5) + (float4::UP));
			PlanePuffLeft->SetMoveSpeed(200.0f);
		}
	}


	{
		{
			PatchLeftA = CreateActor<BackgroundObject>(GameObjectGroup::UI);
			if (PatchLeftA == nullptr)
			{
				return;
			}
			GameEngineTextureRenderer* Renderer = PatchLeftA->GetRenderer();
			if (Renderer == nullptr)
			{
				return;
			}
			Renderer->CreateFrameAnimationFolder("PatchMiddleA", FrameAnimation_DESC("PatchMiddleA", 0.04f, true));
			Renderer->AnimationBindEnd("PatchMiddleA", std::bind(&DogFightLevel::ResetPositionPatchMiddleA, this, std::placeholders::_1));
			Renderer->ChangeFrameAnimation("PatchMiddleA");
			Renderer->SetPivot(PIVOTMODE::CENTER);
			Renderer->ScaleToTexture();
			PatchLeftA->GetTransform().SetLocalPosition({ 640, -770, (int)ZOrder::Background - 3 });
			PatchLeftA->SetDirection(float4::UP);
			PatchLeftA->SetMoveSpeed(200.0f);
		}
	}

	SetPhase(Phase::Ready);
	//카메라 내 오브젝트 크기 조정 
	GetMainCamera()->SetProjectionSize({ 1280.0f, 720.0f });
	GetRotateCamera()->SetProjectionSize({ 1536.0f,864.0f });
	GetRotateCamera2()->SetProjectionSize({ 1408.0f,792.0f });
	GetIrisCamera()->SetProjectionSize({ 1280.0f, 720.0f });
	GetBackgroundCamera()->SetProjectionSize({ 1408.0f,792.0f });

	GetMainCameraActorTransform().SetLocalPosition({ 640, -360 });
	GetBackgroundCameraActorTransform().SetLocalPosition({ 640, -360 });
	GetRotateCameraActorTransform().SetLocalPosition({ 640, -360 });
	GetRotateCamera2ActorTransform().SetLocalPosition({ 640, -360 });
	GetIrisCameraActorTransform().SetLocalPosition({ 640.0f, -360.0f });
}
void DogFightLevel::ResetPositionCloudLeftA(const FrameAnimation_DESC& _Info)
{
	CloudA1->GetTransform().SetLocalPosition({ -150, -250, (int)ZOrder::Background - 1 });
}

void DogFightLevel::ResetPositionCloudLeftA2(const FrameAnimation_DESC& _Info)
{
	CloudA2->GetTransform().SetLocalPosition({ 1430, -250, (int)ZOrder::Background - 1 });
}

void DogFightLevel::ResetPositionCloudLeftB(const FrameAnimation_DESC& _Info)
{
	CloudB2->GetTransform().SetLocalPosition({ -150, -20, (int)ZOrder::Background - 1 });
}

void DogFightLevel::ResetPositionCloudLeftC(const FrameAnimation_DESC& _Info)
{
	CloudC1->GetTransform().SetLocalPosition({ 1200, -20, (int)ZOrder::Background - 1 });
}

void DogFightLevel::ResetPositionCloudLeftC2(const FrameAnimation_DESC& _Info)
{
	CloudC2->GetTransform().SetLocalPosition({ 150, -20, (int)ZOrder::Background - 1 });
}

void DogFightLevel::ResetPositionCloudLeftD(const FrameAnimation_DESC& _Info)
{
	CloudD1->GetTransform().SetLocalPosition({ 640, -20, (int)ZOrder::Background - 1 });
}

void DogFightLevel::ResetPositionCloudLeftD2(const FrameAnimation_DESC& _Info)
{
	CloudD2->GetTransform().SetLocalPosition({ 1130, -20, (int)ZOrder::Background - 1 });
}

void DogFightLevel::ResetPositionPatchMiddleA(const FrameAnimation_DESC& _Info)
{
	PatchLeftA->GetTransform().SetLocalPosition({ 640, -1000, (int)ZOrder::Background - 3 });
}

void DogFightLevel::ResetPositionPlanePuffRight(const FrameAnimation_DESC& _Info)
{
	PlanePuffRight->GetTransform().SetLocalPosition({ 900, -200, (int)ZOrder::NPC + 4 });
}

void DogFightLevel::ResetPositionPlanePuffLeft(const FrameAnimation_DESC& _Info)
{
	PlanePuffLeft->GetTransform().SetLocalPosition({ 380, -200, (int)ZOrder::NPC + 4 });
}

void DogFightLevel::PushToRotateCamera(GameEngineUpdateObject* _Object)
{
	for (auto* Child : _Object->GetChilds())
	{
		if (GameEngineUpdateObject* Object = dynamic_cast<GameEngineUpdateObject*>(Child))
		{
			PushToRotateCamera(Object);
		}

		if (GameEngineRenderer* Renderer = dynamic_cast<GameEngineRenderer*>(Child))
		{
			PushRendererToRotateCamera(Renderer);
		}
	}
}

void DogFightLevel::PushToRotateCamera2(GameEngineUpdateObject* _Object)
{
	for (auto* Child : _Object->GetChilds())
	{
		if (GameEngineUpdateObject* Object = dynamic_cast<GameEngineUpdateObject*>(Child))
		{
			PushToRotateCamera2(Object);
		}

		if (GameEngineRenderer* Renderer = dynamic_cast<GameEngineRenderer*>(Child))
		{
			PushRendererToRotateCamera2(Renderer);
		}
	}
}

void DogFightLevel::PushToBackgroundCamera(GameEngineUpdateObject* _Object)
{
	for (auto* Child : _Object->GetChilds())
	{
		if (GameEngineUpdateObject* Object = dynamic_cast<GameEngineUpdateObject*>(Child))
		{
			PushToBackgroundCamera(Object);
		}

		if (GameEngineRenderer* Renderer = dynamic_cast<GameEngineRenderer*>(Child))
		{
			PushRendererToBackgroundCamera(Renderer);
		}
	}
}

void DogFightLevel::LightOnAnimaitonFrameFinished(const FrameAnimation_DESC& _Info)
{
	// 몬스터 시작 이미지 넣기
	{
		Background* Intro = CreateActor<Background>(GameObjectGroup::UI);
		BulldogIntroRenderer = Intro->CreateComponent<GameEngineTextureRenderer>();
		BulldogIntroRenderer->CreateFrameAnimationFolder("BulldogIntro", FrameAnimation_DESC("BulldogIntro", 0.05f, false));
		BulldogIntroRenderer->CreateFrameAnimationFolder("Nothing", FrameAnimation_DESC("Nothing", true));
		BulldogIntroRenderer->ChangeFrameAnimation("Nothing");
		BulldogIntroRenderer->AnimationBindEnd("BulldogIntro", std::bind(&DogFightLevel::BulldogIntroAnimationFrameFinished, this, std::placeholders::_1));
		BulldogIntroRenderer->SetScaleModeImage();
		BulldogIntroRenderer->ChangeCamera(CAMERAORDER::BACKGROUND);
		BulldogIntroRenderer->GetTransform().SetLocalPosition({ 640.0f, -360.0f, (int)ZOrder::Background - 2 });
	}

	{
		Background* Intro = CreateActor<Background>(GameObjectGroup::UI);
		DogCopterIntroRenderer = Intro->CreateComponent<GameEngineTextureRenderer>();
		DogCopterIntroRenderer->CreateFrameAnimationFolder("DogCopterIntroPhase1", FrameAnimation_DESC("DogCopterIntroPhase1", 0.05f, false));
		DogCopterIntroRenderer->CreateFrameAnimationFolder("Nothing", FrameAnimation_DESC("Nothing", true));
		DogCopterIntroRenderer->ChangeFrameAnimation("DogCopterIntroPhase1");
		DogCopterIntroRenderer->AnimationBindEnd("DogCopterIntroPhase1", std::bind(&DogFightLevel::DogCopterIntroPhase1IntroAnimationFrameFinished, this, std::placeholders::_1));
		DogCopterIntroRenderer->AnimationBindFrame("DogCopterIntroPhase1", std::bind(&DogFightLevel::DogCopterIntroPhase1IntroAnimationFrameChanged, this, std::placeholders::_1));
		DogCopterIntroRenderer->SetScaleModeImage();
		DogCopterIntroRenderer->GetTransform().SetLocalPosition({ 640.0f, -360.0f, (int)ZOrder::Background - 2 });
	}

}

void DogFightLevel::BulldogIntroAnimationFrameFinished(const FrameAnimation_DESC& _Info)
{
	BulldogIntroRenderer->ChangeFrameAnimation("Nothing");
	SetPhase(Phase::Phase1);
}

void DogFightLevel::DogCopterIntroPhase1IntroAnimationFrameFinished(const FrameAnimation_DESC& _Info)
{
		DogCopterIntroRenderer->ChangeFrameAnimation("Nothing");
}

void DogFightLevel::DogCopterIntroPhase1IntroAnimationFrameChanged(const FrameAnimation_DESC& _Info)
{
	if (_Info.CurFrame == 7)
	{
		BulldogIntroRenderer->ChangeFrameAnimation("BulldogIntro");
	}

	else if (_Info.CurFrame == 34)
	{
		GameEngineActor* ReadyWallop = CreateActor<GameEngineActor>(GameObjectGroup::UI);
		ReadyWallopRenderer = ReadyWallop->CreateComponent<GameEngineTextureRenderer>();
		ReadyWallopRenderer->CreateFrameAnimationFolder("Ready", FrameAnimation_DESC("06ReadyWallop", 0.05, false));
		ReadyWallopRenderer->CreateFrameAnimationFolder("KnockOut", FrameAnimation_DESC("07KnockOut", 0.05, false));
		ReadyWallopRenderer->AnimationBindEnd("Ready", std::bind(&DogFightLevel::ReadyWallopAnimationFrameFinished, this, std::placeholders::_1));
		ReadyWallopRenderer->AnimationBindEnd("KnockOut", std::bind(&DogFightLevel::KnockOutAnimationFrameFinished, this, std::placeholders::_1));
		ReadyWallopRenderer->GetTransform().SetWorldScale({ 1280.0f,720.0f,1.0f });
		ReadyWallopRenderer->ChangeFrameAnimation("Ready");
		PushRendererToUICamera(ReadyWallopRenderer);
	}
}

void DogFightLevel::KnockOutAnimationFrameFinished(const FrameAnimation_DESC& _Info)
{
	ReadyWallopRenderer->Off();
	LeaderCopter->SetState(InGameMonsterState::KnockOut);
}

void DogFightLevel::ReadyWallopAnimationFrameFinished(const FrameAnimation_DESC& _Info)
{
	ReadyWallopRenderer->Off();
}

void DogFightLevel::Update(float _DeltaTime)
{
	PlayElapsedTime += _DeltaTime;

	ColMapOnOffSwitch();
	if (GameEngineInput::GetInst()->IsDown("PhaseChangeKey"))
	{
		if (GetPhase() == Phase::Ready)
		{
			SetPhase(Phase::Phase1);
		}
		else if (GetPhase() == Phase::Phase1)
		{
			SetPhase(Phase::Phase2);
		}
		else if (GetPhase() == Phase::Phase2)
		{
			SetPhase(Phase::Phase3);
		}
	}

	if (GetPhase() == Phase::Ready && IrisOnceCheck == false)
	{
		ScreenLightRenderer->ChangeFrameAnimation("LightOn");

		if (CaptainCanteenPlane == nullptr)
		{
			CaptainCanteenPlane = CreateActor<CanteenPlane>(GameObjectGroup::Monster);
			CaptainCanteenPlane->GetTransform().SetWorldPosition({ 270, -650 });

			Cuphead = CreateActor<InGameCuphead>(GameObjectGroup::Player);
			Cuphead->SetParent(CaptainCanteenPlane);

			Cuphead->GetTransform().SetLocalPosition({ -120, 50, (int)ZOrder::Player });
			Cuphead->SetColMapImage(ColMapRenderer);

			if (nullptr != State)
			{
				Cuphead->SetHP(State->MaxHP);
				Cuphead->SetOnDashInvisible(State->OnDashInvisible);
			}

			PlayerHP* HPUI = CreateActor<PlayerHP>(GameObjectGroup::Monster);
			HPUI->SetPlayer(Cuphead);
			HPUI->GetTransform().SetLocalPosition({ 75.0f,-675.0f });

			CaptainCanteenPlane->SetPlayer(Cuphead);
			CaptainCanteenPlane->SetColMapImage(ColMapRenderer);
			PushToRotateCamera(CaptainCanteenPlane);

			Player = Cuphead;
		}		
		//PushToBackgroundCamera(CaptainCanteenPlane);
		//PushToBackgroundCamera(PH1BulldogPlane);

	}

	else if (GetPhase() == Phase::Phase1)
	{
		if (PH1BulldogPlane == nullptr)
		{
			PH1BulldogPlane = CreateActor<BulldogPlane>(GameObjectGroup::Monster);
			PH1BulldogPlane->GetTransform().SetWorldPosition({ 0, 100 });
			PH1BulldogPlane->SetPlayer(Cuphead);
			PushToBackgroundCamera(PH1BulldogPlane);
		}
	}

	else if (GetPhase() == Phase::Phase2)
	{
		ElapsedTime += _DeltaTime;
		ElapsedTime = ElapsedTime / 1.0f;

		if (PH1BulldogPlane != nullptr)
		{
			PH1BulldogPlane->Death();
			PH1BulldogPlane = nullptr;
		}

		if (CaptainCanteenPlane == nullptr)
		{
			CaptainCanteenPlane = CreateActor<CanteenPlane>(GameObjectGroup::Monster);
			CaptainCanteenPlane->GetTransform().SetWorldPosition({ 270, -650 });

			Cuphead = CreateActor<InGameCuphead>(GameObjectGroup::Player);
			Cuphead->SetParent(CaptainCanteenPlane);

			Cuphead->GetTransform().SetLocalPosition({ -120, 50, (int)ZOrder::Player });
			Cuphead->SetColMapImage(ColMapRenderer);

			CaptainCanteenPlane->SetPlayer(Cuphead);
			CaptainCanteenPlane->SetColMapImage(ColMapRenderer);
		}

		if (OnceCheck == false)
		{
			{
				DogFightPh2DogB = CreateActor<Ph2Dog>(GameObjectGroup::Monster);
				DogFightPh2DogD = CreateActor<Ph2Dog>(GameObjectGroup::Monster);
				DogFightPh2DogA = CreateActor<Ph2Dog>(GameObjectGroup::Monster);
				DogFightPh2DogC = CreateActor<Ph2Dog>(GameObjectGroup::Monster);

				DogFightPh2DogA->SetPlayer(Cuphead);
				DogFightPh2DogB->SetPlayer(Cuphead);
				DogFightPh2DogC->SetPlayer(Cuphead);
				DogFightPh2DogD->SetPlayer(Cuphead);

				DogFightPh2DogB->SetPh2DogState(InGamePh2DogState::Prepare2);
				DogFightPh2DogA->SetPh2DogState(InGamePh2DogState::Prepare1);
				DogFightPh2DogD->SetPh2DogState(InGamePh2DogState::Prepare4);
				DogFightPh2DogC->SetPh2DogState(InGamePh2DogState::Prepare3);
			}

			OnceCheck = true;
		}

		if ((nullptr == DogFightPh2DogA || 0 >= DogFightPh2DogA->GetHP()) &&
			(nullptr == DogFightPh2DogB || 0 >= DogFightPh2DogB->GetHP()) &&
			(nullptr == DogFightPh2DogC || 0 >= DogFightPh2DogC->GetHP()) &&
			(nullptr == DogFightPh2DogD || 0 >= DogFightPh2DogD->GetHP()))
		{
			SetPhase(Phase::Phase3);
		}

	}

	else if (GetPhase() == Phase::Phase3)
	{
		if (LeaderCopter == nullptr)
		{
			LeaderCopter = CreateActor<DogCopter>(GameObjectGroup::Monster);
			LeaderCopter->GetTransform().SetWorldPosition({ 0, 0 });
			//LeaderCopter->SetColMapImage(ColMapRenderer);
			//PushToBackgroundCamera(LeaderCopter);
			OldState = LeaderCopter->GetState();
		}

		if (CaptainCanteenPlane == nullptr)
		{
			CaptainCanteenPlane = CreateActor<CanteenPlane>(GameObjectGroup::Monster);
			CaptainCanteenPlane->GetTransform().SetWorldPosition({ 640, -600 });

			Cuphead = CreateActor<InGameCuphead>(GameObjectGroup::Player);
			Cuphead->GetTransform().SetLocalPosition({ 0, 300, -100 });
			Cuphead->SetParent(CaptainCanteenPlane);
			Cuphead->SetColMapImage(ColMapRenderer);

			CaptainCanteenPlane->SetPlayer(Cuphead);
			CaptainCanteenPlane->SetColMapImage(ColMapRenderer);
			PushToRotateCamera(CaptainCanteenPlane);
		}

		if (LeaderCopter != nullptr)
		{
			CaptainCanteenPlane->SetDogCopter(LeaderCopter);

			if (LeaderCopter->GetState() == InGameMonsterState::Die)
			{
				if (ReadyWallopRenderer != nullptr)
				{
				ReadyWallopRenderer->ChangeFrameAnimation("KnockOut");
				ReadyWallopRenderer->On();
				}
			}
		}

	}

	if (nullptr != LeaderCopter)
	{
		float4 CameraRotation = GetRotateCameraActorTransform().GetLocalRotation();
		
		if (OldState != LeaderCopter->GetState())
		{
			OldState = LeaderCopter->GetState();

			switch (LeaderCopter->GetState())
			{
			case InGameMonsterState::RotateCameraIn:
			case InGameMonsterState::RotateCameraOut:
			{
				ZAngle = CameraRotation.z - 90; 
				IsRotateCompleted = false;
				break;
			}
			}
		}

		if (IsRotateCompleted == false)
		{
			RotateElapsedTime += _DeltaTime;
			switch (LeaderCopter->GetState())
			{
			case InGameMonsterState::RotateCameraIn:
			{
				RotateTime = 10;
				break;
			}
			case InGameMonsterState::RotateCameraOut:
			{
				RotateTime = 4;
				break;
			}
			}

			float Time = RotateElapsedTime / RotateTime;
			if (abs(CameraRotation.z - ZAngle) <= 0.1)
			{
				IsRotateCompleted = true;
				RotateElapsedTime = 0.0f;
			}
			float NewZAngle = GameEngineMath::LerpLimit(CameraRotation.z, ZAngle, Time);
			GetRotateCameraActorTransform().SetLocalRotation(float4({ CameraRotation.x ,CameraRotation.y, NewZAngle }));
			GetRotateCamera2ActorTransform().SetLocalRotation(float4({ CameraRotation.x ,CameraRotation.y, NewZAngle }));

		}
	}
}
void DogFightLevel::End()
{
}

