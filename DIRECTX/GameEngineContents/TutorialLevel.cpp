#include "PreCompile.h"
#include "Background.h"
#include "TutorialLevel.h"
#include "WorldMapCuphead.h"
#include "InGameCuphead.h"
#include "CharacterState.h"
#include <GameEngineCore/GameEngineBlur.h>

TutorialLevel::TutorialLevel()
	: BackgroundRenderer(nullptr)
	, ColMapRenderer(nullptr)
	, IsWheatAParriable(true)
	, IsWheatBParriable(false)
	, IsWheatCParriable(false)
	, IsObjectOn(false)
	, CurPhase(TutorialPhase::Phase1)
{
}

TutorialLevel::~TutorialLevel()
{
}


void TutorialLevel::ColMapOnOffSwitch()
{
	if (true == GameEngineInput::GetInst()->IsDown("ColMapOnOffSwitch"))
	{
		TutorialRenderer->OnOffSwitch();
	}
}

void TutorialLevel::LevelStartEvent()
{
	std::list<GameEngineActor*> Actors = GetGroup(GameObjectGroup::CharacterState);
	for (GameEngineActor* Actor : Actors)
	{
		if (CharacterState* _State = dynamic_cast<CharacterState*>(Actor))
		{
			State = _State;
			CurCoin = State->Coin;
		}
	}

	Cuphead = CreateActor<InGameCuphead>(GameObjectGroup::Player);
	Cuphead->GetTransform().SetLocalPosition({ 640, -360, (int)ZOrder::Player });
	Cuphead->SetColMapImage(ColMapRenderer);
	Cuphead->SetHP(State->MaxHP);
	Cuphead->SetOnDashInvisible(State->OnDashInvisible);
	PushToRotateCamera(Cuphead);
}

void TutorialLevel::Start()
{
	GetMainCamera()->GetCameraRenderTarget()->AddEffect<GameEngineBlur>();

	{
		Background* ColMapImage = CreateActor<Background>(GameObjectGroup::UI);
		ColMapRenderer = ColMapImage->CreateComponent<GameEngineTextureRenderer>();
		ColMapRenderer->SetTexture("TutorialColMap.png");
		ColMapRenderer->ScaleToTexture();
		ColMapRenderer->GetTransform().SetLocalPosition({ 640.0f, -360.0f, (int)ZOrder::Background + 1 });
	}

	{
		GameEngineActor* TutorialBackground = CreateActor<GameEngineActor>(GameObjectGroup::UI);
		TutorialRenderer = TutorialBackground->CreateComponent<GameEngineTextureRenderer>();
		TutorialRenderer->CreateFrameAnimationFolder("TutorialStartBackground", FrameAnimation_DESC("TutorialStartBackground", 0.05f, false));
		TutorialRenderer->CreateFrameAnimationFolder("TutorialBackground", FrameAnimation_DESC("TutorialBackground", 0.05f, false));
		TutorialRenderer->AnimationBindEnd("TutorialStartBackground", std::bind(&TutorialLevel::OnTutorialStartBackgroundAnimationEnd, this, std::placeholders::_1));
		TutorialRenderer->AnimationBindEnd("TutorialBackground", std::bind(&TutorialLevel::OnTutorialBackgroundAnimationEnd, this, std::placeholders::_1));
		TutorialRenderer->GetTransform().SetLocalScale({ 1577.0f,1045.0f,1.0f });
		TutorialRenderer->ChangeFrameAnimation("TutorialStartBackground");
		TutorialRenderer->GetTransform().SetLocalPosition({ 640.0f, -360.0f, (int)ZOrder::Background });
	}

	{

		WheatA = CreateActor<GameEngineActor>(GameObjectGroup::UI);
		WheatARenderer = WheatA->CreateComponent<GameEngineTextureRenderer>();
		WheatARenderer->CreateFrameAnimationFolder("ParryWheatA", FrameAnimation_DESC("ParryWheatA", 0.05f, true));
		WheatARenderer->CreateFrameAnimationFolder("Nothing", FrameAnimation_DESC("Nothing", 0.05f, true));
		WheatARenderer->ChangeFrameAnimation("ParryWheatA");
		WheatARenderer->SetScaleModeImage();
		WheatA->GetTransform().SetLocalPosition({ 745.0f, -580.0f, (int)ZOrder::Foreground });
		WheatACollision = WheatA->CreateComponent<GameEngineCollision>();
		WheatACollision->GetTransform().SetLocalScale({ 50.0f,30.0f,1.0f });
		WheatACollision->GetTransform().SetLocalPosition({ 0.0f,0.0f,(int)ZOrder::Foreground });
		WheatACollision->ChangeOrder(ObjectOrder::ONLYPARRIABLEOBJECT);
		WheatA->Off();

		WheatB = CreateActor<GameEngineActor>(GameObjectGroup::UI);
		WheatBRenderer = WheatB->CreateComponent<GameEngineTextureRenderer>();
		WheatBRenderer->CreateFrameAnimationFolder("ParryWheatB", FrameAnimation_DESC("ParryWheatB", 0.05f, true));
		WheatBRenderer->CreateFrameAnimationFolder("Nothing", FrameAnimation_DESC("Nothing", 0.05f, true));
		WheatBRenderer->ChangeFrameAnimation("Nothing");
		WheatBRenderer->SetScaleModeImage();
		WheatB->GetTransform().SetLocalPosition({ 110.0f, -270.0f, (int)ZOrder::Foreground });
		WheatBCollision = WheatB->CreateComponent<GameEngineCollision>();
		WheatBCollision->GetTransform().SetLocalScale({ 30.0f,50.0f,1.0f });
		WheatBCollision->GetTransform().SetLocalPosition({ 0.0f,0.0f,(int)ZOrder::Foreground });
		WheatBCollision->ChangeOrder(ObjectOrder::ONLYPARRIABLEOBJECT);

		WheatC = CreateActor<GameEngineActor>(GameObjectGroup::UI);
		WheatCRenderer = WheatC->CreateComponent<GameEngineTextureRenderer>();
		WheatCRenderer->CreateFrameAnimationFolder("ParryWheatC", FrameAnimation_DESC("ParryWheatC", 0.05f, true));
		WheatCRenderer->CreateFrameAnimationFolder("Nothing", FrameAnimation_DESC("Nothing", 0.05f, true));
		WheatCRenderer->ChangeFrameAnimation("Nothing");
		WheatC->GetTransform().SetLocalPosition({ 950.0f, -150.0f, (int)ZOrder::Foreground });
		WheatCRenderer->SetScaleModeImage();
		WheatCCollision = WheatC->CreateComponent<GameEngineCollision>();
		WheatCCollision->GetTransform().SetLocalScale({ 50.0f,30.0f,1.0f });
		WheatCCollision->GetTransform().SetLocalPosition({ 0.0f,10.0f,(int)ZOrder::Foreground });
		WheatCCollision->ChangeOrder(ObjectOrder::ONLYPARRIABLEOBJECT);
	}

	{
		Rip = CreateActor<GameEngineActor>(GameObjectGroup::UI);
		RipRenderer = Rip->CreateComponent<GameEngineTextureRenderer>();
		RipRenderer->CreateFrameAnimationFolder("Rip", FrameAnimation_DESC("Rip", 0.05f, false));
		RipRenderer->CreateFrameAnimationFolder("Nothing", FrameAnimation_DESC("Nothing", 0.05f, false));
		RipRenderer->CreateFrameAnimationFolder("RipClose", FrameAnimation_DESC("RipClose", 0.05f, false));
		RipRenderer->ChangeFrameAnimation("Nothing");
		Rip->GetTransform().SetLocalPosition({ 300.0f, -0.0f, (int)ZOrder::Foreground });
		RipRenderer->SetScaleModeImage();
		RipRenderer->SetPivot(PIVOTMODE::RIGHTTOP);
		RipCollision = Rip->CreateComponent<GameEngineCollision>();
		RipCollision->GetTransform().SetLocalScale({ 30.0f,400.0f,1.0f });
		RipCollision->GetTransform().SetLocalPosition({ 0.0f,-200.0f,(int)ZOrder::Foreground });
		RipCollision->ChangeOrder(ObjectOrder::ONLYPARRIABLEOBJECT);
	}

	{
		Coin = CreateActor<GameEngineActor>(GameObjectGroup::UI);
		CoinRenderer = Coin->CreateComponent<GameEngineTextureRenderer>();
		CoinRenderer->CreateFrameAnimationFolder("TutorialCoin", FrameAnimation_DESC("TutorialCoin", 0.05f, true));
		CoinRenderer->CreateFrameAnimationFolder("TutorialCoinDeath", FrameAnimation_DESC("TutorialCoinDeath", 0.05f, false));
		CoinRenderer->CreateFrameAnimationFolder("Nothing", FrameAnimation_DESC("Nothing", 0.05f, false));
		CoinRenderer->ChangeFrameAnimation("TutorialCoin");
		CoinRenderer->SetScaleModeImage();
		Coin->GetTransform().SetLocalPosition({ 1200, -100.0f, (int)ZOrder::Foreground });
		CoinRenderer->AnimationBindEnd("TutorialCoinDeath", std::bind(&TutorialLevel::OnTutorialCoinDeathAnimationFinished, this, std::placeholders::_1));
		CoinCollision = Coin->CreateComponent<GameEngineCollision>();
		CoinCollision->GetTransform().SetLocalScale({ 30.0f,50.0f,1.0f });
		CoinCollision->GetTransform().SetLocalPosition({ 0.0f,0.0f, (int)ZOrder::Foreground });
		CoinCollision->ChangeOrder(ObjectOrder::ITEM);
		Coin->Off();
	}
	{
		GameEngineActor* Enter = CreateActor<GameEngineActor>(GameObjectGroup::UI);
		EnterRenderer = Enter->CreateComponent<GameEngineTextureRenderer>();
		EnterRenderer->SetTexture("BBox.png");
		EnterRenderer->ScaleToTexture();
		Enter->GetTransform().SetLocalPosition({ 1100.0f, -450.0f,  (int)ZOrder::Foreground });
		EnterCollision = Enter->CreateComponent<GameEngineCollision>();
		EnterCollision->GetTransform().SetLocalScale({ 200.0f,200.0f,1.0f });
		EnterCollision->GetTransform().SetLocalPosition({ 0.0f, -100.0f,(int)ZOrder::Foreground });
		EnterCollision->ChangeOrder(ObjectOrder::NPC);
	}
	GetMainCamera()->SetProjectionSize({ 1280.0f, 720.0f });
	GetRotateCamera()->SetProjectionSize({ 1536.0f, 864.0f });
	GetIrisCamera()->SetProjectionSize({ 1280.0f, 720.0f });

	GetMainCameraActorTransform().SetLocalPosition({ 640, -360 });
	GetRotateCameraActorTransform().SetLocalPosition({ 640, -360 });
	GetIrisCameraActorTransform().SetLocalPosition({ 640.0f, -360.0f });
}

void TutorialLevel::Update(float _DeltaTime)
{
	ColMapOnOffSwitch();
	EnterRenderer->ScaleToTexture();

	if (false == EnterCollision->IsCollision(CollisionType::CT_AABB2D, ObjectOrder::PC, CollisionType::CT_AABB2D,
		std::bind(&TutorialLevel::OnPortalCollision, this, std::placeholders::_1, std::placeholders::_2)))
	{
		EnterRenderer->Off();
	}
	else
	{
		EnterRenderer->On();
	}

	if (IsObjectOn == true)
	{
		Coin->On();
		WheatA->On();
	}

	if (Cuphead->GetState() == InGameCharacterState::Parry)
	{
		WheatACollision->IsCollision(CollisionType::CT_AABB2D, ObjectOrder::PC, CollisionType::CT_AABB2D, std::bind(&TutorialLevel::OnWheatACollision, this, std::placeholders::_1, std::placeholders::_2));
		WheatBCollision->IsCollision(CollisionType::CT_AABB2D, ObjectOrder::PC, CollisionType::CT_AABB2D, std::bind(&TutorialLevel::OnWheatBCollision, this, std::placeholders::_1, std::placeholders::_2));
		WheatCCollision->IsCollision(CollisionType::CT_AABB2D, ObjectOrder::PC, CollisionType::CT_AABB2D, std::bind(&TutorialLevel::OnWheatCCollision, this, std::placeholders::_1, std::placeholders::_2));
	}
	
	if (Cuphead->GetState() != InGameCharacterState::Evade)
	{
		RipCollision->IsCollision(CollisionType::CT_AABB2D, ObjectOrder::PC, CollisionType::CT_AABB2D, std::bind(&TutorialLevel::OnRipCollision, this, std::placeholders::_1, std::placeholders::_2));
	}

	CoinCollision->IsCollision(CollisionType::CT_AABB2D, ObjectOrder::PC, CollisionType::CT_AABB2D, std::bind(&TutorialLevel::OnCoinCollision, this, std::placeholders::_1, std::placeholders::_2));

	if (GetPhase() == TutorialPhase::Phase1)
	{
		WheatARenderer->ChangeFrameAnimation("ParryWheatA");
		WheatBRenderer->ChangeFrameAnimation("Nothing");
		WheatCRenderer->ChangeFrameAnimation("Nothing");
		WheatACollision->On();
		WheatBCollision->Off();
		WheatCCollision->Off();
		RipCollision->Off();
	}

	else if (GetPhase() == TutorialPhase::Phase2)
	{
		WheatARenderer->ChangeFrameAnimation("Nothing");
		WheatBRenderer->ChangeFrameAnimation("ParryWheatB");
		WheatCRenderer->ChangeFrameAnimation("Nothing");
		RipRenderer->ChangeFrameAnimation("Rip");
		WheatACollision->Off();
		WheatBCollision->On();
		WheatCCollision->Off();
		RipCollision->On();
	}

	else if (GetPhase() == TutorialPhase::Phase3)
	{
		WheatARenderer->ChangeFrameAnimation("Nothing");
		WheatBRenderer->ChangeFrameAnimation("Nothing");
		WheatCRenderer->ChangeFrameAnimation("ParryWheatC");
		WheatACollision->Off();
		WheatBCollision->Off();
		WheatCCollision->On();
		RipCollision->Off();
	}
}

void TutorialLevel::End()
{
}

bool TutorialLevel::OnWheatACollision(GameEngineCollision* _This, GameEngineCollision* _Other)
{
	SetPhase(TutorialPhase::Phase2);
	return true;
}

bool TutorialLevel::OnWheatBCollision(GameEngineCollision* _This, GameEngineCollision* _Other)
{
	RipRenderer->ChangeFrameAnimation("RipClose");
	SetPhase(TutorialPhase::Phase3);
	return true;
}

bool TutorialLevel::OnWheatCCollision(GameEngineCollision* _This, GameEngineCollision* _Other)
{
	SetPhase(TutorialPhase::Phase1);
	Coin->On();
	WheatA->On();
	return true;
}

bool TutorialLevel::OnRipCollision(GameEngineCollision* _This, GameEngineCollision* _Other)
{
	RipRenderer->ChangeFrameAnimation("RipClose");
	SetPhase(TutorialPhase::Phase1);
	return true;
}

bool TutorialLevel::OnCoinCollision(GameEngineCollision* _This, GameEngineCollision* _Other)
{
	CoinRenderer->ChangeFrameAnimation("TutorialCoinDeath");
	if (CurCoin < 25)
	{
		++CurCoin;
	}
	return true;
}

bool TutorialLevel::OnPortalCollision(GameEngineCollision* _This, GameEngineCollision* _Other)
{
	return true;
}

void TutorialLevel::OnTutorialCoinDeathAnimationFinished(const FrameAnimation_DESC& _Info)
{
	CoinRenderer->ChangeFrameAnimation("Nothing");
}

void TutorialLevel::OnTutorialStartBackgroundAnimationEnd(const FrameAnimation_DESC& _Info)
{
	TutorialRenderer->ChangeFrameAnimation("TutorialBackground");
}

void TutorialLevel::OnTutorialBackgroundAnimationEnd(const FrameAnimation_DESC& _Info)
{
	IsObjectOn = true;
}
