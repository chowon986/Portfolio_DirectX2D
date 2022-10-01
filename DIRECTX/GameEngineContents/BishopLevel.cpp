#include "PreCompile.h"
#include "BishopLevel.h"
#include <GameEngineCore/GameEngineTextureRenderer.h>
#include "Background.h"
#include "InGameCuphead.h"
#include "Pawn.h"
#include <GameEngineCore/GEngine.h>
#include <GameEngineContents/Enums.h>
#include <functional>
#include <GameEngineCore/GameEngineBlur.h>
#include <GameEngineContents/TextureLoadUtils.h>

BishopLevel::BishopLevel()
	: BackgroundRenderer(nullptr)
	, ColMapRenderer(nullptr)
{
}

BishopLevel::~BishopLevel()
{
}

void BishopLevel::LevelStartEvent()
{
	TextureLoadUtils::LoadTextures("15DogFightLevel");

	//Start
	Cuphead = CreateActor<InGameCuphead>(GameObjectGroup::Player);
	Cuphead->GetTransform().SetLocalPosition({ 640.0f, -360.0f, (int)ZOrder::Player });
	Cuphead->SetColMapImage(ColMapRenderer);
	PushToRotateCamera(Cuphead);

	{
		Background* BishopBackground = CreateActor<Background>(GameObjectGroup::UI);
		BackgroundRenderer = BishopBackground->CreateComponent<GameEngineTextureRenderer>();
		BackgroundRenderer->SetTexture("bg_main.png");
		BackgroundRenderer->GetTransform().SetLocalPosition({ 640.0f, -360.0f, (int)ZOrder::Background });
		BackgroundRenderer->ScaleToTexture();

		GameEngineCollision* GroundCollisionA = BishopBackground->CreateComponent<GameEngineCollision>();
		GroundCollisionA->GetTransform().SetLocalScale({ 50.0f, 800.0f, 1.0f });
		GroundCollisionA->GetTransform().SetLocalPosition({ 1305.0f,-400.0f });
		GroundCollisionA->ChangeOrder((int)ObjectOrder::RETURN);

		GameEngineCollision* GroundCollisionB = BishopBackground->CreateComponent<GameEngineCollision>();
		GroundCollisionB->GetTransform().SetLocalScale({ 50.0f, 800.0f, 1.0f });
		GroundCollisionB->GetTransform().SetLocalPosition({ -25.0f,-400.0f });
		GroundCollisionB->ChangeOrder((int)ObjectOrder::RETURN);

		IndexCollisionA = BishopBackground->CreateComponent<GameEngineCollision>();
		IndexCollisionA->GetTransform().SetLocalScale({ 50.0f, 200.0f, 1.0f });
		IndexCollisionA->GetTransform().SetLocalPosition({ 150.0f,-50.0f });
		IndexCollisionA->ChangeOrder((int)ObjectOrder::POSINDEX);

		IndexCollisionB = BishopBackground->CreateComponent<GameEngineCollision>();
		IndexCollisionB->GetTransform().SetLocalScale({ 50.0f, 200.0f, 1.0f });
		IndexCollisionB->GetTransform().SetLocalPosition({ 290.0f,-50.0f });
		IndexCollisionB->ChangeOrder((int)ObjectOrder::POSINDEX);


		IndexCollisionC = BishopBackground->CreateComponent<GameEngineCollision>();
		IndexCollisionC->GetTransform().SetLocalScale({ 50.0f, 200.0f, 1.0f });
		IndexCollisionC->GetTransform().SetLocalPosition({ 430.0,-50.0f });
		IndexCollisionC->ChangeOrder((int)ObjectOrder::POSINDEX);

		IndexCollisionD = BishopBackground->CreateComponent<GameEngineCollision>();
		IndexCollisionD->GetTransform().SetLocalScale({ 50.0f, 200.0f, 1.0f });
		IndexCollisionD->GetTransform().SetLocalPosition({ 570.0f,-50.0f });
		IndexCollisionD->ChangeOrder((int)ObjectOrder::POSINDEX);

		IndexCollisionE = BishopBackground->CreateComponent<GameEngineCollision>();
		IndexCollisionE->GetTransform().SetLocalScale({ 50.0f, 200.0f, 1.0f });
		IndexCollisionE->GetTransform().SetLocalPosition({ 710.0f,-50.0f });
		IndexCollisionE->ChangeOrder((int)ObjectOrder::POSINDEX);

		IndexCollisionF = BishopBackground->CreateComponent<GameEngineCollision>();
		IndexCollisionF->GetTransform().SetLocalScale({ 50.0f, 200.0f, 1.0f });
		IndexCollisionF->GetTransform().SetLocalPosition({ 850.0f,-50.0f });
		IndexCollisionF->ChangeOrder((int)ObjectOrder::POSINDEX);

		IndexCollisionG = BishopBackground->CreateComponent<GameEngineCollision>();
		IndexCollisionG->GetTransform().SetLocalScale({ 50.0f, 200.0f, 1.0f });
		IndexCollisionG->GetTransform().SetLocalPosition({ 990.0f,-50.0f });
		IndexCollisionG->ChangeOrder((int)ObjectOrder::POSINDEX);

		IndexCollisionH = BishopBackground->CreateComponent<GameEngineCollision>();
		IndexCollisionH->GetTransform().SetLocalScale({ 50.0f, 200.0f, 1.0f });
		IndexCollisionH->GetTransform().SetLocalPosition({ 1130.0f,-50.0f });
		IndexCollisionH->ChangeOrder((int)ObjectOrder::POSINDEX);

		Collisions.push_back(IndexCollisionA);
		Collisions.push_back(IndexCollisionB);
		Collisions.push_back(IndexCollisionC);
		Collisions.push_back(IndexCollisionD);
		Collisions.push_back(IndexCollisionE);
		Collisions.push_back(IndexCollisionF);
		Collisions.push_back(IndexCollisionG);
		Collisions.push_back(IndexCollisionH);
	}

	{
		//Background* BishopBackgroundTopper = CreateActor<Background>(GameObjectGroup::UI);
		//GameEngineTextureRenderer* Renderer = BishopBackgroundTopper->CreateComponent<GameEngineTextureRenderer>();
		//Renderer->SetTexture("bg_main_topper.png");
		//Renderer->ScaleToTexture();
		//Renderer->GetTransform().SetLocalPosition({ 500,-180,-100 });
	}

	{
		Background* ColMapImage = CreateActor<Background>(GameObjectGroup::UI);
		ColMapRenderer = ColMapImage->CreateComponent<GameEngineTextureRenderer>();
		ColMapRenderer->SetTexture("BishopColMap.png");
		ColMapRenderer->ScaleToTexture();
		ColMapRenderer->GetTransform().SetLocalPosition({ 640.0f, -360.0f, (int)ZOrder::Background + 1 });
	}

	{
		Background* ColMapImage = CreateActor<Background>(GameObjectGroup::UI);
		GameEngineTextureRenderer* PawnColMapRenderer = ColMapImage->CreateComponent<GameEngineTextureRenderer>();
		PawnColMapRenderer->SetTexture("PawnColMap.png");
		PawnColMapRenderer->ScaleToTexture();
		PawnColMapRenderer->GetTransform().SetLocalPosition({ 640.0f, -360.0f, (int)ZOrder::Background + 1 });
		SetMainColMapImage(PawnColMapRenderer);
	}

	{
		PawnPosX = { 150.0f, 290.0f, 430.0f, 570.0f, 710.0f, 850.0f, 990.0f, 1130.0f };
		AttackIntervalTimes = { 12.0f, 6, 10, 4.5, 9, 3.0f, 10.5, 7.5 };

		for (int i = 0; i < 8; i++)
		{
			Pawn* BossPawn = CreateActor<Pawn>(GameObjectGroup::Monster);
			BossPawn->SetPlayer(Cuphead);
			BossPawn->GetTransform().SetLocalPosition({ PawnPosX[i], 0.0f, (int)ZOrder::Player - 1 });
			if (i % 2 == 0)
			{
				BossPawn->SetIntroName("AStart");
			}
			else if (i % 2 == 1)
			{
				BossPawn->SetIntroName("BStart");
			}
			PushToRotateCamera(BossPawn);
			BossPawn->SetAttackIntervalTime(AttackIntervalTimes[i]);
			BossPawnActors.push_back(BossPawn);
		}
	}

	GetMainCamera()->SetProjectionSize({ 1280.0f, 720.0f });
	GetRotateCamera()->SetProjectionSize({ 1536.0f, 864.0f });
	GetIrisCamera()->SetProjectionSize({ 1280.0f, 720.0f });

	GetMainCameraActorTransform().SetLocalPosition({ 640, -360 });
	GetRotateCameraActorTransform().SetLocalPosition({ 640, -360 });
	GetIrisCameraActorTransform().SetLocalPosition({ 640.0f, -360.0f });
}

void BishopLevel::Update(float _DeltaTime)
{
	if (true == GameEngineInput::GetInst()->IsDown("ColMapOnOffSwitch"))
	{
		ColMapOnOffSwitch();
	}
	if (true == GameEngineInput::GetInst()->IsDown("LevelChange"))
	{
		GEngine::ChangeLevel("WorldMap");
	}

	for (int i = 0; i < 8; i++)
	{
		if (BossPawnActors[i]->GetState() != InGameMonsterState::Prepare) // 하나라도 준비 상태가 아니면 
		{
			for (int i = 0; i < 8; i++)
			{
				Collisions[i]->On(); // 켜진다.
			}
		}
	}

	IndexCollisionA->IsCollision(CollisionType::CT_AABB2D, (int)ObjectOrder::PARRIABLEOBJECT, CollisionType::CT_AABB2D, std::bind(&BishopLevel::OnIndexCollision, this, std::placeholders::_1, std::placeholders::_2));
	IndexCollisionB->IsCollision(CollisionType::CT_AABB2D, (int)ObjectOrder::PARRIABLEOBJECT, CollisionType::CT_AABB2D, std::bind(&BishopLevel::OnIndexCollision, this, std::placeholders::_1, std::placeholders::_2));
	IndexCollisionC->IsCollision(CollisionType::CT_AABB2D, (int)ObjectOrder::PARRIABLEOBJECT, CollisionType::CT_AABB2D, std::bind(&BishopLevel::OnIndexCollision, this, std::placeholders::_1, std::placeholders::_2));
	IndexCollisionD->IsCollision(CollisionType::CT_AABB2D, (int)ObjectOrder::PARRIABLEOBJECT, CollisionType::CT_AABB2D, std::bind(&BishopLevel::OnIndexCollision, this, std::placeholders::_1, std::placeholders::_2));
	IndexCollisionE->IsCollision(CollisionType::CT_AABB2D, (int)ObjectOrder::PARRIABLEOBJECT, CollisionType::CT_AABB2D, std::bind(&BishopLevel::OnIndexCollision, this, std::placeholders::_1, std::placeholders::_2));
	IndexCollisionF->IsCollision(CollisionType::CT_AABB2D, (int)ObjectOrder::PARRIABLEOBJECT, CollisionType::CT_AABB2D, std::bind(&BishopLevel::OnIndexCollision, this, std::placeholders::_1, std::placeholders::_2));
	IndexCollisionG->IsCollision(CollisionType::CT_AABB2D, (int)ObjectOrder::PARRIABLEOBJECT, CollisionType::CT_AABB2D, std::bind(&BishopLevel::OnIndexCollision, this, std::placeholders::_1, std::placeholders::_2));
	IndexCollisionH->IsCollision(CollisionType::CT_AABB2D, (int)ObjectOrder::PARRIABLEOBJECT, CollisionType::CT_AABB2D, std::bind(&BishopLevel::OnIndexCollision, this, std::placeholders::_1, std::placeholders::_2));
	
	IndexCollisionA->IsCollision(CollisionType::CT_AABB2D, (int)ObjectOrder::PARRIABLEOBJECT, CollisionType::CT_AABB2D, std::bind(&BishopLevel::IndexCollisionOn, this, std::placeholders::_1, std::placeholders::_2));
	IndexCollisionB->IsCollision(CollisionType::CT_AABB2D, (int)ObjectOrder::PARRIABLEOBJECT, CollisionType::CT_AABB2D, std::bind(&BishopLevel::IndexCollisionOn, this, std::placeholders::_1, std::placeholders::_2));
}

void BishopLevel::ColMapOnOffSwitch()
{
	BackgroundRenderer->OnOffSwitch();
}

CollisionReturn BishopLevel::OnIndexCollision(GameEngineCollision* _This, GameEngineCollision* _Other)
{
	if (Pawn* Monster = dynamic_cast<Pawn*>(_Other->GetParent()))
	{
		if (Monster->GetState() == InGameMonsterState::Prepare)
		{
			_This->Off();
		}
		else
		{
			_This->On();
		}
	}
	return CollisionReturn::ContinueCheck;
}

CollisionReturn BishopLevel::IndexCollisionOn(GameEngineCollision* _This, GameEngineCollision* _Other)
{
	for (int i = 0; i < 8; i++)
	{
		Collisions[i]->On(); // 켜진다.
	}
	return CollisionReturn::ContinueCheck;
}

void BishopLevel::End()
{
}
