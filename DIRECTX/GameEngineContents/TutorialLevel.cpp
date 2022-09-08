#include "PreCompile.h"
#include "Background.h"
#include "TutorialLevel.h"
#include "WorldMapCuphead.h"
#include "InGameCuphead.h"
#include <GameEngineCore/GameEngineBlur.h>

TutorialLevel::TutorialLevel()
	: BackgroundRenderer(nullptr)
	, ColMapRenderer(nullptr)
	, IsWheatAParriable(true)
	, IsWheatBParriable(false)
	, IsWheatCParriable(false)
	, CurPhase(TutorialPhase::Phase1)
{
}

TutorialLevel::~TutorialLevel()
{
}

void TutorialLevel::Start()
{
	GetMainCamera()->GetCameraRenderTarget()->AddEffect<GameEngineBlur>();

	{
		Background* ColMapImage = CreateActor<Background>(GameObjectGroup::UI);
		ColMapRenderer = ColMapImage->CreateComponent<GameEngineTextureRenderer>();
		ColMapRenderer->SetTexture("TestColMap.png");
		ColMapRenderer->ScaleToTexture();
		ColMapRenderer->GetTransform().SetLocalPosition({ 640.0f, -360.0f, (int)ZOrder::Background + 1 });
	}

	{
		GameEngineActor* TutorialBackground = CreateActor<GameEngineActor>(GameObjectGroup::UI);
		GameEngineTextureRenderer* TutorialRenderer = TutorialBackground->CreateComponent<GameEngineTextureRenderer>();
		TutorialRenderer->CreateFrameAnimationFolder("TutorialStartBackground", FrameAnimation_DESC("TutorialStartBackground", 0.05f, false));
		TutorialRenderer->CreateFrameAnimationFolder("TutorialBackground", FrameAnimation_DESC("TutorialBackground", 0.05f, false));
		TutorialRenderer->GetTransform().SetLocalScale({ 1577.0f,1045.0f,1.0f });
		TutorialRenderer->ChangeFrameAnimation("TutorialStartBackground");
		TutorialRenderer->GetTransform().SetLocalPosition({ 640.0f, -360.0f, (int)ZOrder::Background });
	}

	{
		Cuphead = CreateActor<InGameCuphead>(GameObjectGroup::Player);
		Cuphead->GetTransform().SetLocalPosition({ 640, -360, (int)ZOrder::Player});
		Cuphead->SetColMapImage(ColMapRenderer);
		PushToRotateCamera(Cuphead);

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
		RipRenderer->ChangeFrameAnimation("Nothing");
		Rip->GetTransform().SetLocalPosition({ 300.0f, -0.0f, (int)ZOrder::Foreground });
		RipRenderer->SetScaleModeImage();
		RipRenderer->SetPivot(PIVOTMODE::RIGHTTOP);
		RipCollision = Rip->CreateComponent<GameEngineCollision>();
		RipCollision->GetTransform().SetLocalScale({ 30.0f,400.0f,1.0f });
		RipCollision->GetTransform().SetLocalPosition({ 0.0f,-200.0f,(int)ZOrder::Foreground });
		RipCollision->ChangeOrder(ObjectOrder::ONLYPARRIABLEOBJECT);

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
	SetPhase(TutorialPhase::Phase3);
	return true;
}

bool TutorialLevel::OnWheatCCollision(GameEngineCollision* _This, GameEngineCollision* _Other)
{
	SetPhase(TutorialPhase::Phase1);
	return true;
}

bool TutorialLevel::OnRipCollision(GameEngineCollision* _This, GameEngineCollision* _Other)
{
	SetPhase(TutorialPhase::Phase1);
	return true;
}
